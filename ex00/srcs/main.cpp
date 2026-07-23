#include "../includes/BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2 || !av[0])
		return 0;
	try
	{
		setMap();
		parsingInputFile(av);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

