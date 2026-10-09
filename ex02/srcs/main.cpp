#include "../includes/PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error" << std::endl;
		return 0;
	}
	PmergeMe merger;
	if (!merger.checkArgs(av))
	{
		std::cerr << "ERROR WRONG INPUTS" << std::endl;
		return 0;
	}
	else
		std::cout << "GOOD" << std::endl;
}