#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}
PmergeMe::~PmergeMe()
{}

PmergeMe::PmergeMe(PmergeMe const& src)
{
	(void)src;
}

PmergeMe& PmergeMe::operator=(PmergeMe const& src)
{
	(void)src;
	return *this;
}

int PmergeMe::checkArgs(char **av)
{
	size_t i = 1;
	size_t j = 0;
	std::string nb = "";
	size_t count = 0;
	while (av[i])
	{
		if (av[i][0] == '\0')
			return 0;
		while (av[i][j])
		{
			if (isspace(av[i][j]))
			{	
				j++;
				continue;
			}
			if (!isdigit(av[i][j]))
			{
				if (!(av[i][j] == '+' && av[i][j + 1] != '\0' && isdigit(av[i][j + 1])))
					return 0;
				j++;
			}
			while (isdigit(av[i][j]))
			{
				nb += av[i][j];
				j++;
			}
			if (!nb.empty())
			{
				errno = 0;
				char *endptr;
				long num = strtol(nb.c_str(), &endptr, 10);
				if (endptr == nb.c_str() || errno == ERANGE || *endptr != '\0')
					return 0;
				else if (num <= 0 || num > INT_MAX)
					return 0;
				vec.push_back(static_cast<int>(num));
				deq.push_back(static_cast<int>(num));
				nb = "";
				count++;
			}
		}
		i++;
		j = 0;
	}
	if (!count)
		return 0;
	return 1;
}

void PmergeMe::mergeVector()
{
	std::vector<int>::iterator it = vec.begin();

	while (it != vec.end())
	{
		if (it + 1 != vec.end())
		{
			if (*it > *(it + 1))
				_pairsVec.push_back(std::make_pair(*it, *(it + 1)));
			else
				_pairsVec.push_back(std::make_pair(*(it + 1), *it));
			it += 2;
		}
		else
		{
			_straggler = *it;
			it++;
		}
	}
}

std::vector<std::pair<int, int>> PmergeMe::sortVector(std::vector<std::pair<int, int>> vect)
{
	if (vect.size() <= 1)
		return vect;
	size_t numOfPairs = vect.size() / 2;

	std::vector<std::pair<int, int>> leftVec(vect.begin(), vect.begin() + numOfPairs);
	std::vector<std::pair<int, int>> rightVec(vect.begin() + numOfPairs, vect.end());
	leftVec = sortVector(leftVec);
	rightVec = sortVector(rightVec);

	std::vector<std::pair<int, int>> mergedVec;
	std::vector<std::pair<int, int>>::iterator it = leftVec.begin();
	std::vector<std::pair<int, int>>::iterator jt = rightVec.begin();
	while (it != leftVec.end() && jt != rightVec.end())
	{
		if (it->first < jt->first)
		{
			mergedVec.push_back(*it);
			it++;
		}
		else
		{
			mergedVec.push_back(*jt);
			jt++;
		}
	}
	while (jt != rightVec.end())
	{
		mergedVec.push_back(*jt);
		jt++;
	}
	while (it != leftVec.end())
	{
		mergedVec.push_back(*it);
		it++;
	}
	return mergedVec;	
}

void PmergeMe::fordJohnson(std::vector<std::pair<int, int>> mergedVec)
{
	if (mergedVec.empty())
		return ;
	std::vector<int> mainChain;
	std::vector<int> pendings;
	std::vector<std::pair<int, int>>::iterator it = mergedVec.begin();
	
	mainChain.push_back(it->second);
	mainChain.push_back(it->first);
	it++;
	while (it != mergedVec.end())
	{
		mainChain.push_back(it->first);
		pendings.push_back(it->second);
		it++;
	}
	
}