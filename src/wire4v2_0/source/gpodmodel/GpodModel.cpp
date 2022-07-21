#include <iostream>
#include <fstream>
#include <chrono>
#include <exception>

#include <Eigen/Dense>
#include <Eigen/Core>

#include "GpodModel.h"

#include "../osloader/OSLoader.h"
#include "../matrixloader/MatrixLoader.h"

using namespace Eigen;
using Eigen::last;
using Eigen::seq;
using namespace std;
/*====================================================================
                    OFFLINE STAGE
  ====================================================================*/

// ------------------------------------------------------ CONSTRUCTORS 
GpodModel::GpodModel() {
    this->status = "started";
    this->load_romdata();
}

int GpodModel::load_romdata() {
    std::string fname;
    
    std::string path_mesh = "database/mesh";
    std::string path_disp = "database/podi/disp";
    std::string path_mises = "database/podi/mises";
    std::string path_para = "database/para";

    fname = path_disp + filesep + "phi.bin";
    Eigen::read_binary(fname, this->pbase_disp); 
    fname = path_disp + filesep + "bmat.bin";
    Eigen::read_binary(fname, this->bmat_disp); 
    fname = path_mises + filesep + "phi.bin";
    Eigen::read_binary(fname, this->pbase_mises);
    fname = path_mises + filesep + "bmat.bin";
    Eigen::read_binary(fname, this->bmat_mises); 
    fname = path_para + filesep + "paratrain.bin";
    Eigen::read_binary(fname, this->paratrain); 
    fname = path_para + filesep + "paramean.bin";
    Eigen::read_binary(fname, this->paramean); 
    fname = path_para + filesep + "parastd.bin";
    Eigen::read_binary(fname, this->parastd); 

    std::string code = "CUBIC";
    double para = 0;
    std::string name = "cubicsplines";
    std::string style = "rowwise";
    rbfm = RbfModel();
    rbfm.set_style(code,name,style,para);
    rbfm.set_sample(this->paratrain);

    this->store = "result";
    return 0;
}

// /*====================================================================
//                         ONLINE STAGE - PROCESSING
//   ====================================================================*/
// // --------------------------------------------------- UPDATE LOADCOND
    int GpodModel::update_loadcond() {
        // std::string tmpstr="";
        std::string fname = "parameter.csv";
        this->paras = readcsv(fname, 0, 0, 0);

        if (this->paras.rows() != 1)
            this->paras = this->paras.transpose().eval();
        std::cout << this->paras << std::endl;
        this->check_parameter();
        this->print_loadcond();
        // std::cout << this->paras << std::endl;
        this->paras = this->paras - this->paramean;
        this->paras = this->paras.cwiseProduct(this->parastd.cwiseInverse());
        // std::cout << this->paras << std::endl;
        return 0;
    }
    int GpodModel::update_loadcond(MatrixXd paras) {
        this->paras = paras;
        
        if (this->paras.rows() != 1)
            this->paras = this->paras.transpose().eval();
        // std::cout << this->paras << std::endl;
        this->check_parameter();
        this->print_loadcond();
        // std::cout << this->paras << std::endl;
        this->paras = this->paras - this->paramean;
        this->paras = this->paras.cwiseProduct(this->parastd.cwiseInverse());
        // std::cout << this->paras << std::endl;
        return 0;
    }
    int GpodModel::check_parameter() {
        if (this->paras.rows()==0) {
            std::cerr << "Error: update parameter.csv and run the program again!\n";
            this->status = "error";
            return EXIT_FAILURE;
        }
        if (this->paras.cols()!=3) {
            std::cerr << "Error: `parameter.csv` should contain only 3 inputs!\n";
            this->status = "error";
            return EXIT_FAILURE;
        }
        else {
            double E = this->paras(0);
            double R = this->paras(1);
            double P = this->paras(2);

            if (E<5e4 | E>25e4 | R<1 | R>3 | P<1 | P>3) {
                std::cerr << "Error: there is at least one input out of domain!\n";
                this->status = "error";
                return EXIT_FAILURE;
            }
        }
        return EXIT_SUCCESS;
    }

// ------------------------------------------------------ ROM SOLUTION
int GpodModel::solverom_avgtime() {
    using Clock = std::chrono::steady_clock;
    using Time = std::chrono::steady_clock::time_point;
    Time start, end;

    // time_point start, end;
    this->nRun = 500;
    MatrixXd runtimeall(nRun+1,3);
    runtimeall.array() = 0.0;
    VectorXd runtimes;

    MatrixXd temp;
    for (int i=0; i<nRun+1; i++) {
        // task 1 - update rbf model
        start = Clock::now();
        this->rbfm.get_gvec(this->paras, this->gvec);
        end = Clock::now();
        runtimeall(i,0) += chrono::duration_cast<chrono::microseconds>(end - start).count();
        
        // task 2 - interp approx.
        start = Clock::now();
        this->drom = this->pbase_disp *(this->bmat_disp * this->gvec);
        this->mrom = this->pbase_mises *(this->bmat_mises * this->gvec);
        end = Clock::now();
        runtimeall(i,1) += chrono::duration_cast<chrono::microseconds>(end - start).count();

        // total time
        runtimeall(i,2) = runtimeall(i,seq(0,1)).sum();
    }

    // mean runtime (milliseconds) - ignore the first one
    runtimes = runtimeall(seq(1,last),all).colwise().mean()/1.0e3;
    // std::cout << runtimeall << std::endl;
    // std::cout << "Average running time (ms): " << std::endl
    //           << runtimes << std::endl;

    this->runtime.resize(1);
    this->runtime(0) = runtimes(2);

    // save the result
    write_podisol();
    this->status = "done";
    return 0;
}
int GpodModel::solverom() {
    using Clock = std::chrono::steady_clock;
    using Time = std::chrono::steady_clock::time_point;
    Time start, end;

    double runtimeall = 0.0;

    // task 1 - update rbf model
    start = Clock::now();
    this->rbfm.get_gvec(this->paras, this->gvec);
    end = Clock::now();
    runtimeall += chrono::duration_cast<chrono::microseconds>(end - start).count();
        
    // task 2 - interp approx.
    start = Clock::now();
    this->drom = this->pbase_disp *(this->bmat_disp * this->gvec);
    this->mrom = this->pbase_mises *(this->bmat_mises * this->gvec);
    end = Clock::now();
    runtimeall += chrono::duration_cast<chrono::microseconds>(end - start).count();

    this->runtime.resize(1);
    this->runtime(0) = runtimeall/1000;

    // save the result
    write_podisol();
    this->status = "done";
    return 0;
}
// /*====================================================================
//                             DISPLAY INFORMATION
//   ====================================================================*/
// int GpodModel::print_config() {
//     int sdof = this->pbase_disp.rows();
//     int nnode = this->pbase_mises.rows();
//     int poddim_disp = this->pbase_disp.cols();
//     int poddim_mises = this->pbase_mises.cols();
//     int nparatrain = this->paratrain.rows();
//     std::cout << "This PODI-RBF approximates the displacement and von-Mises stress\n";
//     std::cout << "of a soft gripper. Bellow is some information of the programe.\n";
//     std::cout << "Total FEM nodes: " << nnode << std::endl;
//     std::cout << "Total training snapshot: " << nparatrain << std::endl;
//     std::cout << "Number of POD vectors for displacement: " << poddim_disp << std::endl;
//     std::cout << "Number of POD vectors for von-Mises: " << poddim_mises << std::endl;
//     return 0;
// }
int GpodModel::print_config() {
    int nnode = this->pbase_mises.rows();
    int poddim_disp = this->pbase_disp.cols();
    int poddim_mises = this->pbase_mises.cols();
    std::cout << "Some information of the PODI-RBF model.\n";
    std::cout << "\tTotal FEM nodes: " << nnode << std::endl;
    std::cout << "\tNumber of POD vectors for displacement: " << poddim_disp << std::endl;
    std::cout << "\tNumber of POD vectors for von-Mises: " << poddim_mises << std::endl;
    return 0;
}
int GpodModel::print_loadcond() {
    std::cout << "Input parameter:" << std::endl;
    std::cout << "\tE = " << this->paras(0) << " MPa\n";
    std::cout << "\tR = " << this->paras(1) << "\n";
    std::cout << "\tP = " << this->paras(2) << " MPa\n";
    return 0;
}
int GpodModel::print_runtime() {
    std::cout << "\ttime: " << this->runtime << " ms\n";
    std::cout << "\tspeed: " << 1000/this->runtime(0) << " Hz\n";
    return 0;
}
int GpodModel::write_podisol() {
    std::string fname;
    fname = this->store + filesep + "drom.bin";
    Eigen::write_binary(fname, this->drom);
    fname = this->store + filesep + "mrom.bin";
    Eigen::write_binary(fname, this->mrom);
    fname = this->store + filesep + "runTime.bin";
    Eigen::write_binary(fname, this->runtime);
    return 0;
}

// int GpodModel::print_info4debug(std::string infoname) {
//     // configure - result folder
//     if (!infoname.compare("configure")) {
//         std::cout << "sdof: " << ptrCnfg->sdof << std::endl;
//         std::cout << "nnode: " << ptrCnfg->nnode << std::endl;
//         std::cout << "nloadval: " << ptrCnfg->nloadval << std::endl;
//         std::cout << "nloadloc: " << ptrCnfg->nloadloc << std::endl;

//         std::cout << "centers:" << std::endl;
//         std::cout << centers<< std::endl;
//         std::cout << "RBF Model: " << rbfm.code 
//                   << ", " << rbfm.name 
//                   << ", para: " << rbfm.para << std::endl;
//     }

//     // update_storedir - result folder
//     if (!infoname.compare("store")) {
//         std::cout << "store = " << store << std::endl;
//     }

//     // update_clustid
//     if (!infoname.compare("clustid")) {
//         std::cout << "ClustID is " << clustid << std::endl;
//     }
//     // update_rbfmodel
//     if (!infoname.compare("rbfmodel")) {
//         std::cout << "nsample: " << rbfm.nsample << "\n";
//         std::cout << "gvec: " << gvec << "\n";
//     }
//     // update_interp - some info of new PODI
//     if (!infoname.compare("podirbf")) {
//         std::cout << "Bmat size: "<<bmat.rows()<<"x"<<bmat.cols()<< std::endl;
//         std::cout << "B, col 1: "<<bmat.col(0)<< std::endl;
//         std::cout << "gvec size: "<<gvec.rows()<<"x"<<gvec.cols()<< std::endl;
//         std::cout << "gvec: "<<gvec<<gvec.cols()<< std::endl;
//     }
//     return 0;
// }