#include "../includes/PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error" << std::endl;
		return 0;
	}
	std::vector<int> vec;
	std::deque<int> deq;
	if (!checkArgs(av, vec, deq))
	{
		std::cerr << "ERROR WRONG INPUTS" << std::endl;
		return 0;
	}
	else
		std::cout << "GOOD" << std::endl;
}