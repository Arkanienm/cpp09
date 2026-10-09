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

void PmergeMe(char **av);
int checkArgs(char **av, std::vector<int>& vec, std::deque<int>& deq);

#endif