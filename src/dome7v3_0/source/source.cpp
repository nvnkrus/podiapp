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
    std::cout << "Problem: Hyperelastic Hemisphere Dome.\n";
    std::cout << "Target: approximate the displacement and von-Mises\n";
    std::cout << "stress fields of the hyperelastic dome during the\n";
    std::cout << "indentation process. The indenter object is rigid.\n";
    std::cout << "In the file `parameter.csv`, users can vary\n";
    std::cout << "\t- the contact location `x_c` (first 3 numbers)\n";
    std::cout << "\t- indentation depth (last numbers) `d_c` in [-20,-5] mm.\n";
    std::cout << "The approximated solutions by PODI-RBF method are obtained\n";
    std::cout << "in online stage and stored in `result` folder.\n";
    std::cout << "            -----------------         \n";
    std::cout << "For evaluation, Abaqus solutions of 30 cases are provided.\n";
    std::cout << "These cases are related to 10 new contact locations and 3 new indentation depths\n";
	std::cout << "1\t-2.7437   54.9315   -0.0051  -17.5\n";
	std::cout << "2\t-2.7437   54.9315   -0.0051  -12.5\n";
	std::cout << "3\t-2.7437   54.9315   -0.0051   -7.5\n";
	std::cout << "4\t36.3873   41.1143   -3.2523  -17.5\n";
	std::cout << "5\t36.3873   41.1143   -3.2523  -12.5\n";
	std::cout << "6\t36.3873   41.1143   -3.2523   -7.5\n";
	std::cout << "7\t15.8607   40.7905   33.3103  -17.5\n";
	std::cout << "8\t15.8607   40.7905   33.3103  -12.5\n";
	std::cout << "9\t15.8607   40.7905   33.3103   -7.5\n";
	std::cout << "10\t9.7251   40.9166  -35.4437  -17.5\n";
	std::cout << "11\t9.7251   40.9166  -35.4437  -12.5\n";
	std::cout << "12\t9.7251   40.9166  -35.4437   -7.5\n";
	std::cout << "13\t-25.9497   41.2262   25.5347  -17.5\n";
	std::cout << "14\t-25.9497   41.2262   25.5347  -12.5\n";
	std::cout << "15\t-25.9497   41.2262   25.5347   -7.5\n";
	std::cout << "16\t-25.9477   41.2216  -25.5440  -17.5\n";
	std::cout << "17\t-25.9477   41.2216  -25.5440  -12.5\n";
	std::cout << "18\t-25.9477   41.2216  -25.5440   -7.5\n";
	std::cout << "19\t-35.4103   42.0845   -0.0007  -17.5\n";
	std::cout << "20\t-35.4103   42.0845   -0.0007  -12.5\n";
	std::cout << "21\t-35.4103   42.0845   -0.0007   -7.5\n";
	std::cout << "22\t17.8560   50.4220  -12.7979  -17.5\n";
	std::cout << "23\t17.8560   50.4220  -12.7979  -12.5\n";
	std::cout << "24\t17.8560   50.4220  -12.7979   -7.5\n";
	std::cout << "25\t20.2040   49.5113   12.8619  -17.5\n";
	std::cout << "26\t20.2040   49.5113   12.8619  -12.5\n";
	std::cout << "27\t20.2040   49.5113   12.8619   -7.5\n";
	std::cout << "28\t-4.6512   48.1864   26.1043  -17.5\n";
	std::cout << "29\t-4.6512   48.1864   26.1043  -12.5\n";
	std::cout << "30\t-4.6512   48.1864   26.1043   -7.5\n";
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>-<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
	std::cout << "\n\n\n";
	
	std::cout << "======================================\n";
	std::cout << "         MAIN PROGRAM STARTED         \n";
	std::cout << "\n";
	std::cout << "Load PODI-RBF data: ";
	
	Eigen::MatrixXd paras(1,4);
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