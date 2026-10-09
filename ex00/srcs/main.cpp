#include "../includes/BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2 || !av[0])
	{
		std::cout << "Error: could not open file." << std::endl;
		return 0;
	}
	try
	{
		BitcoinExchange bitcoin;
		bitcoin.setMap(av);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

