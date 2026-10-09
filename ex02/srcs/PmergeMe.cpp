#include "../includes/PmergeMe.hpp"

int checkArgs(char **av, std::vector<int>& vec, std::deque<int>& deq)
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

// void PmergeMe(char **av)
// {

// }