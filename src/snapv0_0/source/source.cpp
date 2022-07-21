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
    std::cout << "Problem: Snap Connectors.\n";
    std::cout << "Target: approximate the displacement and von-Mises stress fields of \n";
    std::cout << "a elastic female connector during contact with a rigid male connector.\n";
    std::cout << "In the file `parameter.csv`, users can vary\n";
    std::cout << "\t- the movement distance `d` in [-3.2,0] mm of the male connector.\n";
    std::cout << "The approximated solutions by PODI-RBF method are obtained in online\n";
    std::cout << "stage and stored in `result` folder.\n";
    std::cout << "                           -----------------\n";
    std::cout << "For evaluation, Abaqus solutions of 30 cases are provided.\n";
	std::cout << "\tCase\td\tCase\td\tCase\td\n";
	std::cout << "\t1\t-3.12\t11\t-2.08\t21\t-1.04\n";
	std::cout << "\t2\t-3.04\t12\t-2\t22\t-0.88\n";
	std::cout << "\t3\t-2.96\t13\t-1.84\t23\t-0.8\n";
	std::cout << "\t4\t-2.8\t14\t-1.76\t24\t-0.72\n";
	std::cout << "\t5\t-2.72\t15\t-1.68\t25\t-0.56\n";
	std::cout << "\t6\t-2.64\t16\t-1.52\t26\t-0.48\n";
	std::cout << "\t7\t-2.48\t17\t-1.44\t27\t-0.4\n";
	std::cout << "\t8\t-2.4\t18\t-1.36\t28\t-0.24\n";
	std::cout << "\t9\t-2.32\t19\t-1.2\t29\t-0.16\n";
	std::cout << "\t10\t-2.16\t20\t-1.12\t30\t-0.08\n";
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>-<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
	std::cout << "\n\n\n";
	
	std::cout << "======================================\n";
	std::cout << "         MAIN PROGRAM STARTED         \n";
	std::cout << "\n";
	std::cout << "Load PODI-RBF data: ";
	
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
