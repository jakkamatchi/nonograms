#ifndef __SOLUTION_H_INCLUDED__
#define __SOLUTION_H_INCLUDED__

#include <vector>

class Solution {
	public:
		Solution(int, int);
		~Solution();

		std::vector<std::vector<int> > solutionData;
	private:
		void PrintDiagnostic();
		void GenerateSolution(int, int);
};

#endif
