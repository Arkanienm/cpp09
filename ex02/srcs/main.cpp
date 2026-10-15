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
		std::cerr << "Error" << std::endl;
		return 0;
	}
	std::vector<int> vect = merger.getVec();
	std::vector<int>::iterator it = vect.begin();
	std::cout << "Before: ";
	while (it != vect.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;

	clock_t start = clock();
	merger.mergeVector();
	clock_t end = clock();
	vect = merger.getVec();
	it = vect.begin();
	std::cout << "After: ";
	while (it != vect.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;

	double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
	std::cout << "Time to process a range of " << vect.size() << " with std::vector : " << duration << " us" << std::endl;;
	
	clock_t start2 = clock();
	merger.mergeDeque();
	clock_t end2 = clock();
	double duration2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1000000.0;

	std::cout << "Time to process a range of " << vect.size() << " with std::deque : " << duration2 << " us" << std::endl;
}