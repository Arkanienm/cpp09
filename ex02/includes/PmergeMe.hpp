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
#include <algorithm>
#include <sys/time.h>
#include <iomanip>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe const& src);
		PmergeMe& operator=(PmergeMe const& src);
		~PmergeMe();
		void mergeVector();
		void vecFordJohnson(std::vector<std::pair<int, int> > mergedVec);
		std::vector<std::pair<int, int> > sortVector(std::vector<std::pair<int, int> > vect);
		std::vector<int> vecJac(int size);
		void mergeDeque();
		void deqFordJohnson(std::deque<std::pair<int, int> > mergedDeq);
		std::deque<std::pair<int, int> > sortDeque(std::deque<std::pair<int, int> > vect);
		std::deque<int> deqJac(int size);
		int checkArgs(char **av);
		std::vector<int> getVec();

	private:
		std::vector<int> _vec;
		std::deque<int> _deq;
		std::vector< std::pair<int, int> > _pairsVec;
		std::deque< std::pair<int, int> > _pairsDeq;
		int _straggler;
};


#endif