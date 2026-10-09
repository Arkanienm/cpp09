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
		void merge(char **av);
		int checkArgs(char **av);

	private:
		std::vector<int> vec;
		std::deque<int> deq;
};


#endif