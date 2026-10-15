#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe() : _straggler(-1)
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

std::vector<int> PmergeMe::getVec()
{
	return _vec;
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
				_vec.push_back(static_cast<int>(num));
				_deq.push_back(static_cast<int>(num));
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
	_straggler = -1;
	std::vector<int>::iterator it = _vec.begin();

	while (it != _vec.end())
	{
		if (it + 1 != _vec.end())
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
	vecFordJohnson(sortVector(_pairsVec));
}

std::vector<std::pair<int, int> > PmergeMe::sortVector(std::vector<std::pair<int, int> > vect)
{
	if (vect.size() <= 1)
		return vect;
	size_t numOfPairs = vect.size() / 2;

	std::vector<std::pair<int, int> > leftVec(vect.begin(), vect.begin() + numOfPairs);
	std::vector<std::pair<int, int> > rightVec(vect.begin() + numOfPairs, vect.end());
	leftVec = sortVector(leftVec);
	rightVec = sortVector(rightVec);

	std::vector<std::pair<int, int> > mergedVec;
	std::vector<std::pair<int, int> >::iterator it = leftVec.begin();
	std::vector<std::pair<int, int> >::iterator jt = rightVec.begin();
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

std::vector<int> PmergeMe::vecJac(int size)
{
	std::vector<int> vect;
	if (size <= 0)
		return vect;
	
	vect.push_back(0);
	if (size > 1)
		vect.push_back(1);
	int j_prev = 1;
	int j_curr = 3;

	while (j_curr < size)
	{
		vect.push_back(j_curr);
		int next = j_curr + (2 * j_prev);
		j_prev = j_curr;
		j_curr = next;
	}
	for (size_t i = size - 1; i >= 1; --i)
	{
		if (std::find(vect.begin(), vect.end(), i) == vect.end())
			vect.push_back(i);
	}
	return vect;
}

void PmergeMe::vecFordJohnson(std::vector<std::pair<int, int> > mergedVec)
{
	if (mergedVec.empty())
		return ;
	std::vector<int> mainChain;
	std::vector<int> pendings;
	std::vector<std::pair<int, int> >::iterator it = mergedVec.begin();
	
	mainChain.push_back(it->second);
	mainChain.push_back(it->first);
	it++;
	while (it != mergedVec.end())
	{
		mainChain.push_back(it->first);
		pendings.push_back(it->second);
		it++;
	}
	std::vector<int> indJac = vecJac(pendings.size());
	if (!pendings.empty())
	{
		std::vector<int>::iterator jt = indJac.begin();
		int i = *indJac.begin();
		int prevJac = i;
		int currJack = i;
		while (jt != indJac.end())
		{
			std::vector<int>::iterator t = std::lower_bound(mainChain.begin(), mainChain.end(), pendings.at(*jt));
			mainChain.insert(t, pendings.at(*jt));
			currJack = *jt;
			while (currJack > prevJac)
			{
				std::vector<int>::iterator t = std::lower_bound(mainChain.begin(), mainChain.end(), pendings.at(currJack));
				mainChain.insert(t, pendings.at(currJack));
				currJack--;
			}
			prevJac = *jt;
			jt++;
			if (jt != indJac.end())
				i = *jt;
		}
	}
	if (_straggler != -1)
	{
		std::vector<int>::iterator t = std::lower_bound(mainChain.begin(), mainChain.end(), _straggler);
		mainChain.insert(t, _straggler);
	}
	_vec = mainChain;
}

void PmergeMe::mergeDeque()
{
	_straggler = -1;
	std::deque<int>::iterator it = _deq.begin();

	while (it != _deq.end())
	{
		if (it + 1 != _deq.end())
		{
			if (*it > *(it + 1))
				_pairsDeq.push_back(std::make_pair(*it, *(it + 1)));
			else
				_pairsDeq.push_back(std::make_pair(*(it + 1), *it));
			it += 2;
		}
		else
		{
			_straggler = *it;
			it++;
		}
	}
	deqFordJohnson(sortDeque(_pairsDeq));
}

std::deque<std::pair<int, int> > PmergeMe::sortDeque(std::deque<std::pair<int, int> > dequ)
{
	if (dequ.size() <= 1)
		return dequ;
	size_t numOfPairs = dequ.size() / 2;

	std::deque<std::pair<int, int> > leftDeq(dequ.begin(), dequ.begin() + numOfPairs);
	std::deque<std::pair<int, int> > rightDeq(dequ.begin() + numOfPairs, dequ.end());
	leftDeq = sortDeque(leftDeq);
	rightDeq = sortDeque(rightDeq);

	std::deque<std::pair<int, int> > mergedDeq;
	std::deque<std::pair<int, int> >::iterator it = leftDeq.begin();
	std::deque<std::pair<int, int> >::iterator jt = rightDeq.begin();
	while (it != leftDeq.end() && jt != rightDeq.end())
	{
		if (it->first < jt->first)
		{
			mergedDeq.push_back(*it);
			it++;
		}
		else
		{
			mergedDeq.push_back(*jt);
			jt++;
		}
	}
	while (jt != rightDeq.end())
	{
		mergedDeq.push_back(*jt);
		jt++;
	}
	while (it != leftDeq.end())
	{
		mergedDeq.push_back(*it);
		it++;
	}
	return mergedDeq;
}

std::deque<int> PmergeMe::deqJac(int size)
{
	std::deque<int> dequ;
	if (size <= 0)
		return dequ;
	
	dequ.push_back(0);
	if (size > 1)
		dequ.push_back(1);
	int j_prev = 1;
	int j_curr = 3;

	while (j_curr < size)
	{
		dequ.push_back(j_curr);
		int next = j_curr + (2 * j_prev);
		j_prev = j_curr;
		j_curr = next;
	}
	for (size_t i = size - 1; i >= 1; --i)
	{
		if (std::find(dequ.begin(), dequ.end(), i) == dequ.end())
			dequ.push_back(i);
	}
	return dequ;
}


void PmergeMe::deqFordJohnson(std::deque<std::pair<int, int> > mergedDeq)
{
	if (mergedDeq.empty())
		return ;
	std::deque<int> mainChain;
	std::deque<int> pendings;
	std::deque<std::pair<int, int> >::iterator it = mergedDeq.begin();
	
	mainChain.push_back(it->second);
	mainChain.push_back(it->first);
	it++;
	while (it != mergedDeq.end())
	{
		mainChain.push_back(it->first);
		pendings.push_back(it->second);
		it++;
	}
	std::deque<int> indJac = deqJac(pendings.size());
	if (!pendings.empty())
	{
		std::deque<int>::iterator jt = indJac.begin();
		int i = *indJac.begin();
		int prevJac = i;
		int currJack = i;
		while (jt != indJac.end())
		{
			std::deque<int>::iterator t = std::lower_bound(mainChain.begin(), mainChain.end(), pendings.at(*jt));
			mainChain.insert(t, pendings.at(*jt));
			currJack = *jt;
			while (currJack > prevJac)
			{
				std::deque<int>::iterator t = std::lower_bound(mainChain.begin(), mainChain.end(), pendings.at(currJack));
				mainChain.insert(t, pendings.at(currJack));
				currJack--;
			}
			prevJac = *jt;
			jt++;
			if (jt != indJac.end())
				i = *jt;
		}
	}
	if (_straggler != -1)
	{
		std::deque<int>::iterator t = std::lower_bound(mainChain.begin(), mainChain.end(), _straggler);
		mainChain.insert(t, _straggler);
	}
	_deq = mainChain;
}