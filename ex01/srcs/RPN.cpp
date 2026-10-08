#include "../includes/RPN.hpp"

void rpn(char **av)
{
	std::stack<int> stk;
	int result = 0;
	size_t i = 0;
	int a;
	int b;
	while (av[1][i])
	{
		if (isspace(av[1][i]))
		{
			i++;
			continue;
		}
		if (isdigit(av[1][i]))
		{
			if (!(isspace(av[1][i + 1]) || av[1][i + 1] == '\0')) 
			{
				std::cerr << "Error" << std::endl;
				return;
			}
			stk.push(av[1][i] - '0');
		}
		else if (av[1][i] == '+' || av[1][i] == '-' || av[1][i] == '*' || av[1][i] == '/')
		{
			if (!(isspace(av[1][i + 1]) || av[1][i + 1] == '\0')) 
			{
				std::cerr << "Error" << std::endl;
				return;
			}
			if (stk.size() < 2)
			{
				std::cerr << stk.size() << "Error" << std::endl;
				return;
			}
			b = stk.top();
			stk.pop();
			a = stk.top();
			stk.pop();
			if (av[1][i] == '+')
				result = a + b;
			else if (av[1][i] == '-')
				result = a - b;
			else if (av[1][i] == '*')
				result = a * b;
			else if (av[1][i] == '/')
			{
				if(b == 0)
				{
					std::cerr << "Error" << std::endl;
					return;
				}
				result = a / b;
			}
			stk.push(result);
		}
		else
		{	
			std::cerr << "Error" << std::endl;
			return;
		}
		i++;
	}
	if (stk.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		return;
	}
	std::cout << stk.top() << std::endl;
}