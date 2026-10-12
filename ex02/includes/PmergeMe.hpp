#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <stdexcept>
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <stdlib.h>
#include <limits.h>
#include <cerrno>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe const& src);
		PmergeMe& operator=(PmergeMe const& src);
		~PmergeMe();
		void mergeVector();
		void fordJohnson(std::vector<std::pair<int, int>> mergedVec);
		std::vector<std::pair<int, int>> sortVector(std::vector<std::pair<int, int>> vect);
		int checkArgs(char **av);

	private:
		std::vector<int> vec;
		std::deque<int> deq;
		std::vector< std::pair<int, int> > _pairsVec;
		int _straggler;
};


#endif