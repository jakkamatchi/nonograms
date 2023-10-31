#include <iostream>
#include <vector>

#include "solution.h"

Solution::Solution(int x_t, int y_t) {
	GenerateSolution(x_t, y_t);

	//PrintDiagnostic();	
}

Solution::~Solution() {

}

void Solution::PrintDiagnostic() {
	for (int i = 0; i < solutionData.size(); i++) {
		for (int j = 0; j < solutionData[0].size(); j++) {
			std::cout << solutionData[i][j] << " ";
		}

		std::cout << std::endl;
	}

	return;
}

void Solution::GenerateSolution(int x_t, int y_t) {
	std::vector<int> temp;
	srand(time(0));

	//the vector stores solution data horizontally, i.e.
	//-----------
	//as opposed to
	//	|
	//	|
	//	|
	//	|
	//	|

	for(int i = 0; i < y_t; i++) {
		for(int j = 0; j < x_t; j++) {
			temp.push_back(rand() % 2);
		}
		
		solutionData.push_back(temp);

		temp.resize(0);
	}
}
