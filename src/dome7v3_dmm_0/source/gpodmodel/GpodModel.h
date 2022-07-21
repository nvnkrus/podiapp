#pragma once
#define MAXNC 30 	// max number of clusters
#define MAXLM 10 	// max number of local model

#include <string>
#include <Eigen/Dense>
#include "RbfModel.h"

// // for json parser
// #include <rapidjson/document.h>
// #include <rapidjson/istreamwrapper.h>
// #include <rapidjson/writer.h>
// #include <rapidjson/stringbuffer.h>
// #include <rapidjson/ostreamwrapper.h>
// #include <rapidjson/pointer.h> 	// pointer to access nested json

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
	int update_clustid();
	int update_rbfmodel();
    int update_podrbf();
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
	int dLag;

	// ============= Clusters
	int ncluster, clustid;
	int ndctrain;
	Eigen::VectorXd dctrain;
    MatrixXd centers;

	// ============= RBF Model
	double rbfpara;
	RbfModel rbfm;

	// ============= Input parameter
    MatrixXd paras;	
    MatrixXd xc; 
    double dc;

	// ============= Online/Offline ROM Data
	MatrixXd xcclusts[MAXNC];
	MatrixXd pdispall[MAXNC][MAXLM];
	MatrixXd pmisesall[MAXNC][MAXLM];
	MatrixXd bdispall[MAXNC][MAXLM];
	MatrixXd bmisesall[MAXNC][MAXLM];
	MatrixXd paratrain;
  	MatrixXd pbase_disp, pbase_mises;
	MatrixXd bmat_disp, bmat_mises;
	VectorXd gvec;  	

	// Result
    VectorXd runtime;	
    VectorXd drom;		// displacement solution
    VectorXd mrom;		// stress solution
};

/* =================================================
                    Other Functions
   =================================================*/
std::string subdirfnc(int i);
std::string subfarhatdirfnc(int i,int j,std::string anatype);	
