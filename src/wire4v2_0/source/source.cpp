// Measure the performance of the direct inteprolation method
#include <iostream>
#include <string>
// #define EIGEN_VECTORIZE_SSE4_2
// #define EIGEN_DONT_PARAparasELIZE
#include <Eigen/Dense>
// for json parser
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>

#include "OSLoader.h"
#include "MatrixLoader.h"
// #include "Configure.h"
#include "GpodModel.h"

int main()
{
	int n = 1;
	Eigen::setNbThreads(n);
	std::cout << "=======================================================================\n";
    std::cout << " REAL-TIME FINITE ELEMENT SIMULATION PROGRAM FOR ROBOT SIMULATOR V1.0\n";
    std::cout << "\n";
    std::cout << "Problem: Wire Winding.\n";
    std::cout << "Target: approximate the displacement and von-Mises\n";
    std::cout << "stress fields of the deformable wire during the winding\n";
    std::cout << "process. The wire is winded around a rigid cylinder of \n";
    std::cout << "radius 15 mm by simultaneously rotate and translate the cylinder.\n";
    std::cout << "In the file `parameter.csv`, users can vary\n";
    std::cout << "\t- the Young's modulus `E` in [5e4,25e4] MPa\n";
    std::cout << "\t- the ratio of translation/rotation speed `R` in [1,3]\n";
    std::cout << "\t- the pressure at one end of the wire `P` in [1,3] MPa.\n";
    std::cout << "The approximated solutions by PODI-RBF method are obtained\n";
    std::cout << "in online stage and stored in `result` folder.\n";
    std::cout << "            -----------------         \n";
    std::cout << "For evaluation, Abaqus solutions of 30 cases are provided.\n";
	std::cout << "\tCase\tE\tR\tP\n";
	std::cout << "\t1\t75000\t1.3\t1.75\n";
	std::cout << "\t2\t75000\t1.3\t2.25\n";
	std::cout << "\t3\t75000\t1.3\t2.75\n";
	std::cout << "\t4\t75000\t1.7\t1.75\n";
	std::cout << "\t5\t75000\t1.7\t2.25\n";
	std::cout << "\t6\t75000\t1.7\t2.75\n";
	std::cout << "\t7\t75000\t2.1\t1.75\n";
	std::cout << "\t8\t75000\t2.1\t2.25\n";
	std::cout << "\t9\t75000\t2.1\t2.75\n";
	std::cout << "\t10\t75000\t2.5\t1.75\n";
	std::cout << "\t11\t75000\t2.5\t2.25\n";
	std::cout << "\t12\t75000\t2.5\t2.75\n";
	std::cout << "\t13\t75000\t2.9\t1.75\n";
	std::cout << "\t14\t75000\t2.9\t2.25\n";
	std::cout << "\t15\t75000\t2.9\t2.75\n";
	std::cout << "\t16\t225000\t1.3\t1.75\n";
	std::cout << "\t17\t225000\t1.3\t2.25\n";
	std::cout << "\t18\t225000\t1.3\t2.75\n";
	std::cout << "\t19\t225000\t1.7\t1.75\n";
	std::cout << "\t20\t225000\t1.7\t2.25\n";
	std::cout << "\t21\t225000\t1.7\t2.75\n";
	std::cout << "\t22\t225000\t2.1\t1.75\n";
	std::cout << "\t23\t225000\t2.1\t2.25\n";
	std::cout << "\t24\t225000\t2.1\t2.75\n";
	std::cout << "\t25\t225000\t2.5\t1.75\n";
	std::cout << "\t26\t225000\t2.5\t2.25\n";
	std::cout << "\t27\t225000\t2.5\t2.75\n";
	std::cout << "\t28\t225000\t2.9\t1.75\n";
	std::cout << "\t29\t225000\t2.9\t2.25\n";
	std::cout << "\t30\t225000\t2.9\t2.75\n";
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>-<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
	std::cout << "\n\n\n";
	
	std::cout << "======================================\n";
	std::cout << "         MAIN PROGRAM STARTED         \n";
	std::cout << "\n";
	std::cout << "Load PODI-RBF data: ";
	
	Eigen::MatrixXd paras(1,3);
	GpodModel gpodi;
	std::cout << "Done.\n";

	std::cout << "Read and check input from `parameter.csv`: \n"; 
	gpodi.update_loadcond();
	std::cout << "Done.\n";
	if (gpodi.status.compare("error")==0){
		std::cout << "\n";
		std::cout << " MAIN PROGRAM TERMINATED DUE TO ERROR \n";
		std::cout << "======================================\n";
		return 0;
	}

	std::cout << "Estimate displacement and stress solution: \n"; 
	gpodi.solverom();
	std::cout << "Done.\n";
	std::cout << "Running time of a single call:\n";
	gpodi.print_runtime();
	// std::cout << "Average running time of 500 calls:\n";
	// gpodi.solverom_avgtime();
	// gpodi.print_runtime();

	gpodi.print_config();
	
	std::cout << "\n";
	std::cout << "        MAIN PROGRAM COMPLETED        \n";
	std::cout << "======================================\n";
	return 0;
}

// ===================================== DEBUG
// print loadcond
// gpod1.print_loadcond();
// gpod2.print_loadcond();

// gpod1.update_clustid();
// gpod1.update_rbfmodel();
// gpod1.update_podrbf();

// gpod1.print_info4debug("configure");

// std::cout << "Number of threads: " << n << std::endl;

// paras << 55,15,15;
	// std::cout << "input parameter\n";
	// std::cout << paras <<std::endl;




























// // Test parse setting from JSON file
// #include <iostream>
// #include <string>
// // #define EIGEN_VECTORIZE_SSE4_2
// #define EIGEN_DONT_PARAparasELIZE
// #include <Eigen/Dense>
// // for json parser
// #include <rapidjson/document.h>
// #include <rapidjson/istreamwrapper.h>
// #include <rapidjson/writer.h>
// #include <rapidjson/stringbuffer.h>
// #include <rapidjson/ostreamwrapper.h>

// #include "OSLoader.h"
// #include "MatrixLoader.h"
// #include "Configure.h"
// #include "PodiModel.h"
// #include "NaiveModel.h"

// int main()
// {
// 	std::cout << "Configure using JSON files" << std::endl;
// 	std::string fjson = "setup.json";

// 	Configure cfgobj(fjson);
// 	cfgobj.read_mesh();
// 	cfgobj.read_para();

// 	// Podi model - displacement
// 	fjson = "interpcfg_disp.json";
// 	PodiModel adaprom1(&cfgobj, fjson);
// 	adaprom1.load_romdata();
// 	NaiveModel naiverom1(&cfgobj, fjson);
// 	naiverom1.load_romdata();
// 	// Podi model - stress
// 	fjson = "interpcfg_mises.json";
// 	PodiModel adaprom2(&cfgobj, fjson);
// 	adaprom2.load_romdata();
// 	NaiveModel naiverom2(&cfgobj, fjson);
// 	naiverom2.load_romdata();

	/* ----- P1-P2 -----
	// update loading condition
	// indenter depth
	int nlv = 16;
	double lv_min=-20, lv_max=-5;
	VectorXd lvtest;
	lvtest.setLinSpaced(nlv,lv_min,lv_max);
	// contact location: P1-P2
	int nparas = 2;
	MatrixXd paraval(nparas,3);
	paraval << -29.065, 41.485, 21.429, 9.7533, 53.479, -8.3564;
	*/

	/* ----- P3 ----- */
	// int nlv = 1;
	// VectorXd lvtest(1);
	// lvtest << -17;
	// int nparas = 1;
	// MatrixXd paraval(nparas,3);
	// paraval << 11.6204, 52.1478, -13.0590;

// 	std::cout << "loadloc for test:\n";
// 	std::cout << paraval <<std::endl;
// 	std::cout << "loadval for test:\n";
// 	std::cout << lvtest <<std::endl;


// 	// solve test cases
// 	int i,j,caseid = 0;
// 	double lv;
// 	Eigen::MatrixXd paras(1,3);

// 	caseid = 0;
// 	for (int i=0;i<nparas;i++) {
// 		paras = paraval.row(i);
// 		for (int j=0;j<nlv;j++) {
// 			caseid += 1; 
// 			printf("case: %d",caseid);
// 			lv = lvtest(j);
// 			// update bcond
// 			adaprom1.update_loadcond(lv, paras);
// 			adaprom2.update_loadcond(lv, paras);
// 			naiverom1.update_loadcond(lv, paras);
// 			naiverom2.update_loadcond(lv, paras);
// 			// solution
// 			adaprom1.solverom_avgtime();
// 			adaprom2.solverom_avgtime();
// 			naiverom1.solverom_avgtime();
// 			naiverom2.solverom_avgtime();
// 			printf(". Done.\n");
// 		}
// 	}
// 	return 0;
// }

// // ===================================== DEBUG
// // print loadcond
// // adaprom1.print_loadcond();
// // adaprom2.print_loadcond();

// // adaprom1.update_clustid();
// // adaprom1.update_rbfmodel();
// // adaprom1.update_podrbf();

// // adaprom1.print_info4debug("configure");