#pragma once
#define MAXNC 30 	// max number of clusters
#define MAXLM 10 	// max number of local model

#include <string>
#include <Eigen/Dense>
#include "RbfModel.h"

// for json parser
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/pointer.h> 	// pointer to access nested json

using namespace Eigen;
using namespace std;

/* =================================================
                    CLASS GpodModel
   =================================================*/
class GpodModel {
public:
	std::string status;
	// ================ CONSTRUCTORS 
    GpodModel();
	int load_romdata();

	// // ================ UPDATE LOADCOND    
    int update_loadcond();
    int update_loadcond(MatrixXd paras);
    int check_parameter();
	
	// ================ SOLUTION 
	int solverom_avgtime();
	int solverom();

	// ================ DISPLAY INFORMATION 
	int print_config();
	int print_loadcond();
	int print_runtime();
	int write_podisol();
	// int print_info4debug(std::string infoname);

protected:
	// ============= Configuration
	std::string store;
	int nRun;

	// ============= RBF Model
	RbfModel rbfm;

	// ============= Input parameter
    MatrixXd paras;	

	// ============= Online/Offline ROM Data
	MatrixXd paratrain, paramean, parastd;
  	MatrixXd pbase_disp, pbase_mises;
	MatrixXd bmat_disp, bmat_mises;
	VectorXd gvec;  	

	// Result
    VectorXd runtime;	
    VectorXd drom;		// displacement solution
    VectorXd mrom;		// stress solution
};
