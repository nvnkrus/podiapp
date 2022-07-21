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
    MatrixXd tmpmat;
    
    std::string path_para = "database/para";
    fname = path_para + filesep + "ndctrain.bin";
    Eigen::read_binary(fname, tmpmat);
    this->ndctrain = (int)tmpmat(0,0);
    fname = path_para + filesep + "dctrain.bin";
    Eigen::read_binary(fname, tmpmat);
    this->dctrain = VectorXd(Map<VectorXd>(tmpmat.data(),tmpmat.cols()*tmpmat.rows()));

    std::string path_podi = "database/podi";
    fname = path_podi + filesep + "centers.bin";
    Eigen::read_binary(fname, this->centers);
    this->ncluster = this->centers.rows();
    fname = path_podi + filesep + "dLag.bin";
    Eigen::read_binary(fname, tmpmat);
    this->dLag = (int)tmpmat(0,0);
    fname = path_podi + filesep + "rbfpara.bin";
    Eigen::read_binary(fname, tmpmat);
    this->rbfpara = (double)tmpmat(0,0);    
    
    int i, j;
    for (i=0; i<ncluster; i++) {
        fname = path_podi + filesep + subdirfnc(i+1) + filesep + "xctrain.bin";
        Eigen::read_binary(fname, xcclusts[i]);
        // cout << "file loadlocseries: " << fname << endl;
        
        for (j=0; j<this->ndctrain; j++) {
            // displacement
            fname = path_podi + filesep + subfarhatdirfnc(i+1, j+1, "disp") + filesep + "phi.bin";
            Eigen::read_binary(fname, pdispall[i][j]);
            fname = path_podi + filesep + subfarhatdirfnc(i+1, j+1, "disp") + filesep + "bmat.bin";
            Eigen::read_binary(fname, bdispall[i][j]);
            // mises
            fname = path_podi + filesep + subfarhatdirfnc(i+1, j+1, "mises") + filesep + "phi.bin";
            Eigen::read_binary(fname, pmisesall[i][j]);
            fname = path_podi + filesep + subfarhatdirfnc(i+1, j+1, "mises") + filesep + "bmat.bin";
            Eigen::read_binary(fname, bmisesall[i][j]);
        }
    }

    rbfm = RbfModel();
    rbfm.set_style("INVMULQUAD","invmulquad","rowwise",this->rbfpara);

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
        // std::cout << this->paras << std::endl;
        this->check_parameter();
        return 0;
    }
    int GpodModel::update_loadcond(MatrixXd paras) {
        this->paras = paras;
        
        if (this->paras.rows() != 1)
            this->paras = this->paras.transpose().eval();
        // std::cout << this->paras << std::endl;
        this->check_parameter();
        return 0;
    }
    int GpodModel::check_parameter() {
        if (this->paras.rows()==0) {
            std::cerr << "Error: update parameter.csv and run the program again!\n";
            this->status = "error";
            return EXIT_FAILURE;
        }
        if (this->paras.cols()!=4) {
            std::cerr << "Error: `parameter.csv` should contain only 4 inputs!\n";
            this->status = "error";
            return EXIT_FAILURE;
        }
        else {
            this->xc = this->paras(0,seq(0,2));
            this->dc = this->paras(0,3);

            if (this->dc<-20 | this->dc>-5 | (this->xc.norm()-55)>1e-3 \
                | this->xc(1) < 40) {
                std::cerr << "Error: there is at least one input out of domain!\n";
                this->status = "error";
                return EXIT_FAILURE;
            }
        }
        return EXIT_SUCCESS;
    }

// ------------------------------------------------------ ROM SOLUTION
int GpodModel::update_clustid() {    
    MatrixXd temp1 = this->xc.replicate(this->ncluster,1) - this->centers;
    VectorXd temp2 = temp1.rowwise().squaredNorm();
    temp2.minCoeff(&clustid);
    return 0;
}
int GpodModel::update_rbfmodel() {    
    rbfm.set_sample(this->xcclusts[clustid]);
    rbfm.get_gvec(this->xc, this->gvec);
    return 0;
}
int GpodModel::update_podrbf() {
    // ===== Derive new PODRBF model =====
    VectorXd xx;
    double x;
    int i, N = this->dLag + 1;
    xx = this->dctrain;
    x = this->dc;

    xx.array() -= x;
    xx.array() = xx.array().abs();
    // sorted xx and index b
    VectorXi b = sortvectorxd(xx);
    // take out n closest cases
    VectorXi c = b.head(N);
    sortvectorxi(c);
    
    // corresponding xx
    VectorXd subxx = subvectorxd(this->dctrain,c);
    VectorXd weis = lagrangeweight(subxx, x);
    
    // task 2
    if (N==2) {
        // displacement
        this->pbase_disp = weis(0) * this->pdispall[clustid][c(0)] +\
            weis(1) * this->pdispall[clustid][c(1)];
        this->bmat_disp = weis(0) * this->bdispall[clustid][c(0)] +\
            weis(1) * this->bdispall[clustid][c(1)];
        // mises
        this->pbase_mises = weis(0) * this->pmisesall[clustid][c(0)] +\
            weis(1) * this->pmisesall[clustid][c(1)];
        this->bmat_mises = weis(0) * this->bmisesall[clustid][c(0)] +\
            weis(1) * this->bmisesall[clustid][c(1)];
    }
    else {
        i=0;
        // displacement
        this->pbase_disp = weis(i) * this->pdispall[clustid][c(i)];
        this->bmat_disp = weis(i) * this->bdispall[clustid][c(i)];
        for (i=1; i<N; i++) {
            this->pbase_disp += weis(i) * this->pdispall[clustid][c(i)];
            this->bmat_disp += weis(i) * this->bdispall[clustid][c(i)];
        }
        // mises
        this->pbase_mises = weis(i) * this->pmisesall[clustid][c(i)];
        this->bmat_mises = weis(i) * this->bmisesall[clustid][c(i)];
        for (i=1; i<N; i++) {
            this->pbase_mises += weis(i) * this->pmisesall[clustid][c(i)];
            this->bmat_mises += weis(i) * this->bmisesall[clustid][c(i)];
        }
    }
    return 0;
}
int GpodModel::solverom_avgtime() {
    using Clock = std::chrono::steady_clock;
    using Time = std::chrono::steady_clock::time_point;
    Time start, end;

    // time_point start, end;
    this->nRun = 500;
    MatrixXd runtimeall(nRun+1,5);
    runtimeall.array() = 0.0;
    VectorXd runtimes;

    MatrixXd temp;
    for (int i=0; i<nRun+1; i++) {
        // task 1 - update subdomain
        start = Clock::now();
        this->update_clustid();
        end = Clock::now();
        runtimeall(i,0) += chrono::duration_cast<chrono::microseconds>(end - start).count();

        // task 2 - update rbf model
        start = Clock::now();
        this->update_rbfmodel();
        end = Clock::now();
        runtimeall(i,1) += chrono::duration_cast<chrono::microseconds>(end - start).count();

        // task 3 - update pod
        start = Clock::now();
        this->update_podrbf();
        end = Clock::now();
        runtimeall(i,2) += chrono::duration_cast<chrono::microseconds>(end - start).count();
        
        // task 4 - podrbf approx.
        start = Clock::now();
        temp = (this->bmat_disp * this->gvec);
        this->drom = this->pbase_disp * temp;
        temp = (this->bmat_mises * this->gvec);
        this->mrom = this->pbase_mises * temp;
        end = Clock::now();
        
        runtimeall(i,3) += chrono::duration_cast<chrono::microseconds>(end - start).count();

        // total time
        runtimeall(i,4) = runtimeall(i,seq(0,3)).sum();
    }

    // mean runtime (milliseconds) - ignore the first one
    runtimes = runtimeall(seq(1,last),all).colwise().mean()/1.0e3;
    // std::cout << runtimeall << std::endl;
    // std::cout << "Average running time (ms): " << std::endl
    //           << runtimes << std::endl;

    this->runtime.resize(1);
    this->runtime(0) = runtimes(4);

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
    MatrixXd temp;

    // task 1 - update subdomain
    start = Clock::now();
    this->update_clustid();
    end = Clock::now();
    runtimeall += chrono::duration_cast<chrono::microseconds>(end - start).count();

    // task 2 - update rbf model
    start = Clock::now();
    this->update_rbfmodel();
    end = Clock::now();
    runtimeall += chrono::duration_cast<chrono::microseconds>(end - start).count();

    // task 3 - update pod
    start = Clock::now();
    this->update_podrbf();
    end = Clock::now();
    runtimeall += chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    // task 4 - podrbf approx.
    start = Clock::now();
    temp = (this->bmat_disp * this->gvec);
    this->drom = this->pbase_disp * temp;
    temp = (this->bmat_mises * this->gvec);
    this->mrom = this->pbase_mises * temp;
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
    std::cout << "\tContact location: xc = (" << this->xc << ") mm\n";
    std::cout << "\tIndent. depth dc = " << this->dc << " mm\n";
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
// /*====================================================================
//                             OTHER FUNCTIONS
//   ====================================================================*/
std::string subdirfnc(int i) {
    std::string tmpstr="";
    return tmpstr + filesep + "submodel_" + std::to_string(i);
}
std::string subfarhatdirfnc(int i,int j,std::string anatype) {
    return subdirfnc(i) + filesep + "loadval_" + \
        std::to_string(j) + filesep + anatype;
}