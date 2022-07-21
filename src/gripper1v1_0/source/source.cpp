// Measure the performance of the direct inteprolation method
#include <iostream>
#include <string>
#include <Eigen/Dense>

#include "OSLoader.h"
#include "MatrixLoader.h"
#include "GpodModel.h"

int main()
{
	int n = 1;
	Eigen::setNbThreads(n);
	std::cout << "=======================================================================\n";
    std::cout << " REAL-TIME FINITE ELEMENT SIMULATION PROGRAM FOR ROBOT SIMULATOR V1.0\n";
    std::cout << "\n";
    std::cout << "Problem: Soft gripper.\n";
    std::cout << "Target: approximate the displacement and von-Mises\n";
    std::cout << "stress fields of the soft gripper during the gripping\n";
    std::cout << "process. The gripped object is a rigid cylinder of \n";
    std::cout << "radius 15 mm. In the file `parameter.csv`, users can vary\n";
    std::cout << "\t- the cylinder position `h` in [40,100] mm\n";
    std::cout << "\t- the cylinder incline angle `theta_x` in [-30,30] degree\n";
    std::cout << "\t- the gripping distance `d_x` in [0,15] mm.\n";
    std::cout << "The approximated solutions by PODI-RBF method are obtained\n";
    std::cout << "in online stage and stored in `result` folder.\n";
    std::cout << "            -----------------         \n";
    std::cout << "For evaluation, Abaqus solutions of 30 cases are provided.\n";
	std::cout << "\tCase\th\ttheta_x\td_x\n";
	std::cout << "\t1\t55\t15\t2.5\n";
	std::cout << "\t2\t55\t15 \t7.5\n";
	std::cout << "\t3\t55\t15 \t10\n";
	std::cout << "\t4\t55\t15 \t15\n";
	std::cout << "\t5\t95\t15 \t2.5\n";
	std::cout << "\t6\t95\t15 \t7.5\n";
	std::cout << "\t7\t95\t15 \t10\n";
	std::cout << "\t8\t95\t15 \t15\n";
	std::cout << "\t9\t65\t15 \t5\n";
	std::cout << "\t10\t65\t15 \t7.5\n";
	std::cout << "\t11\t65\t15 \t10\n";
	std::cout << "\t12\t65\t15 \t12.5\n";
	std::cout << "\t13\t62.5\t0\t5\n";
	std::cout << "\t14\t62.5\t0\t7.5\n";
	std::cout << "\t15\t62.5\t0\t12.5\n";
	std::cout << "\t16\t62.5\t15\t2.5\n";
	std::cout << "\t17\t62.5\t15\t5\n";
	std::cout << "\t18\t62.5\t15\t7.5\n";
	std::cout << "\t19\t62.5\t15\t10\n";
	std::cout << "\t20\t62.5\t15\t12.5\n";
	std::cout << "\t21\t62.5\t15\t15\n";
	std::cout << "\t22\t77.5\t0\t2.5\n";
	std::cout << "\t23\t77.5\t0\t10\n";
	std::cout << "\t24\t77.5\t0\t15\n";
	std::cout << "\t25\t77.5\t15\t2.5\n";
	std::cout << "\t26\t77.5\t15\t5\n";
	std::cout << "\t27\t77.5\t15\t7.5\n";
	std::cout << "\t28\t77.5\t15\t10\n";
	std::cout << "\t29\t77.5\t15\t12.5\n";
	std::cout << "\t30\t77.5\t15\t15\n";
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>-<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
	std::cout << "\n\n\n";
	
	std::cout << "======================================\n";
	std::cout << "         MAIN PROGRAM STARTED         \n";
	std::cout << "\n";
	std::cout << "Load PODI-RBF data: ";
	
	Eigen::MatrixXd paras(1,3);
	GpodModel gpodi;
	std::cout << "Done.\n";

	std::cout << "Read and check input from `parameter.csv`: "; 
	gpodi.update_loadcond();
	std::cout << "Done.\n";
	gpodi.print_loadcond();
	if (gpodi.status.compare("error")==0){
		std::cout << "\n";
		std::cout << " MAIN PROGRAM TERMINATED DUE TO ERROR \n";
		std::cout << "======================================\n";
		return 0;
	}

	std::cout << "Estimate displacement and stress solution: "; 
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
