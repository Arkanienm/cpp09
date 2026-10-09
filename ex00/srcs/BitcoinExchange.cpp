#include "../includes/BitcoinExchange.hpp"
#include <map>
#include <fstream>
#include <string>
#include <stdlib.h>

const char* NoFileCsvException::what() const throw()
{
	return "Unable to open the file data.csv .";
}

const char* NoInputFileException::what() const throw()
{
	return "Error: could not open file.";
}

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::~BitcoinExchange()
{}
BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const& src)
{
	(void)src;
	return *this;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& src)
{
	*this = src;
}

void BitcoinExchange::setMap(char **av)
{
	std::ifstream dataCsv("data.csv");
	if (!dataCsv.is_open())
		throw NoFileCsvException();
	std::string line;
	std::string date;
	std::string price;
	float fprice;
	;
	while (getline(dataCsv, line))
	{
		int i = 0;
		i = line.find(',');
		date = line.substr(0, i);
		price = line.substr(i + 1, line.size());
		fprice = atof(price.c_str());
		myMap.insert(std::make_pair(date, fprice));
	}
	parsingInputFile(av);
}

int BitcoinExchange::checkValue(std::string line)
{
	size_t index = line.find('|') + 1;
	size_t size = line.size() - index - 1;
	char* endptr;
	int dot = 0;
	if (line.at(13) == '-')
	{
		std::cout << "Error: not a positive number." << std::endl;
		return(0);
	}
	for (size_t i = 13; i < line.size(); i++)
	{
		if (line.at(i) == '.')
			dot++;
		if ((!isdigit(line.at(i)) && line.at(i) != '.' )|| dot > 1)
		{
			std::cout << "Invalid number input." << std::endl;
			return (0);
		}
	}
	float value = strtof(line.substr(index + 1, size).c_str(), &endptr);
	if (value > 1000 || value < 0)
	{
		std::cout << "Error: too large a number." << std::endl;
		return (0);
	}
	return (1);
}

int BitcoinExchange::checkDate(std::string line)
{
	for (int i = 0; i < 4; i++)
	{
		if (!isdigit(line.at(i)))
		{
			std::cout << "Error: bad input => " << line.substr(0, 10) << std::endl;
			return (0);
		}
	}
	for (int i = 5; i < 7; i++)
	{
		if (!isdigit(line.at(i)))
		{
			std::cout << "Error: bad input => " << line.substr(0, 10) << std::endl;
			return (0);
		}
	}
	for (int i = 8; i < 10; i++)
	{
		if (!isdigit(line.at(i)))
		{
			std::cout << "Error: bad input => " << line.substr(0, 10) << std::endl;
			return (0);
		}
	}
	int month = atoi(line.substr(5, 2).c_str());
	int day = atoi(line.substr(8, 2).c_str());
	int year = atoi(line.substr(0, 4).c_str());
	if (month > 12 || month <= 0 || day > 32 || day <= 0)
	{
		std::cout << "Error: bad input => " << line.substr(0, 10) << std::endl;
		return (0);
	}
	if (month == 2)
	{
		if ((year % 4 == 0 && year %100 != 0) || (year % 400 == 0))
		{
			if (day > 29)
			{
				std::cout << "Error: bad input => " << line.substr(0, 10) << std::endl;
				return (0);
			}
		}
		else
		{
			if (day > 28)
			{
				std::cout << "Error: bad input => " << line.substr(0, 10) << std::endl;
				return (0);
			}
		}
	}
	else if ((month % 2 != 0 && month <= 7) || (month % 2 == 0 && month >= 8))
	{
		if (day > 31)
		{
			std::cout << "Error: bad input => " << line.substr(0, 10) << std::endl;
			return (0);
		}
	}
	else
	{
		if (day > 30)
		{
			std::cout << "Error: bad input => " << line.substr(0, 10) << std::endl;
			return (0);
		}
	}
	return (1);
}

void BitcoinExchange::calcul(std::string line)
{
	std::string date;
	std::map <std::string, float>::iterator it;
	int i = 0;
	bool dateFound = 0;
	float result = 0;
	date = line.substr(0, 10);
	it = myMap.begin();
	while (it != myMap.end() && dateFound == false)
	{
		if (it->first == date)
			dateFound = true;
		else
			it++;
	}
	if (!dateFound)
	{
		it = myMap.lower_bound(date);
		if (it != myMap.begin())
			it--;
	}
	size_t index = line.find('|') + 1;
	size_t size = line.size() - index - 1;
	float value = atof(line.substr(13, size).c_str());
	result = it->second * value;
	std::cout << date << " => " << value  << " = " << result << std::endl;
	i++;
}

int BitcoinExchange::checkFile(std::string line, bool i)
{
	if (i == 0)
	{
		if (line != "date | value")
			std::cout << "First line is invalid" << std::endl;
		return (0);
	}
	if (!checkDate(line))
		return (0);
	if (!checkValue(line))
		return (0);
	else
	{
		if (line.find("|") == std::string::npos || line.size() < 10 || line.at(11) != '|')
		{
			std::cout << "Line synthaxe is invalid" << std::endl;
			return (0);
		}
		else if (line.at(4) != '-' || line.at(7) != '-' || line.at(10) != ' ' || line.at(12) != ' ')
		{
			std::cout << "Line synthaxe is invalid" << std::endl;
			return (0);
		}
	}
	return (1);
}

void BitcoinExchange::parsingInputFile(char **av)
{
	std::ifstream inputFile(av[1]);
	if (!inputFile.is_open())
		throw NoInputFileException();
	std::string line;
	int i = 0;
	while (getline(inputFile, line))
	{
		if (checkFile(line, i))
			calcul(line);
		i++;
	}
}
