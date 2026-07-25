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
	return "Unable to open the input file .";
}

const char* WrongInputFile::what() const throw()
{
	return "The file has wrong input in .";
}

static int checkValue(std::string line)
{
	size_t index = line.find('|') + 1;
	size_t size = line.size() - index - 1;
	if (size <= 0 || size > 4)
		return (0);
	for (size_t i = 13; i < line.size(); i++)
	{
		if (!isdigit(line.at(i)))
			return (0);
	}
	int value = atoi(line.substr(13, size).c_str());
	if (value > 1000 || value < 0)
		return (0);
	return (1);
}

static int checkDate(std::string line)
{
	for (int i = 0; i < 4; i++)
	{
		if (!isdigit(line.at(i)))
		{
			std::cout << "Date is invalid ." << std::endl;
			return (0);
		}
	}
	for (int i = 5; i < 7; i++)
	{
		if (!isdigit(line.at(i)))
		{
			std::cout << "Date is invalid ." << std::endl;
			return (0);
		}
	}
	for (int i = 8; i < 10; i++)
	{
		if (!isdigit(line.at(i)))
		{
			std::cout << "Date is invalid ." << std::endl;
			return (0);
		}
	}
	int month = atoi(line.substr(5, 2).c_str());
	int day = atoi(line.substr(8, 2).c_str());
	int year = atoi(line.substr(0, 4).c_str());
	if (month > 12 || month <= 0 || day > 32 || day <= 0)
	{
		std::cout << "Date is invalid ." << std::endl;
		return (0);
	}
	if (month == 2)
	{
		if ((year % 4 == 0 && year %100 != 0) || (year % 400 == 0))
		{
			if (day > 29)
			{
				std::cout << "Date is invalid ." << std::endl;
				return (0);
			}
		}
		else
		{
			if (day > 28)
			{
				std::cout << "Date is invalid ." << std::endl;
				return (0);
			}
		}
	}
	else if ((month % 2 != 0 && month <= 7) || (month % 2 == 0 && month >= 8))
	{
		if (day > 31)
		{
			std::cout << "Date is invalid ." << std::endl;
			return (0);
		}
	}
	else
	{
		if (day > 30)
		{
			std::cout << "Date is invalid ." << std::endl;
			return (0);
		}
	}
	
	return (1);
}

static void calcul(std::string line, std::map<std::string, float> &myMap)
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
	float value = atoi(line.substr(13, size).c_str());
	result = it->second * value;
	std::cout << date << " => " << value  << " = " << result << std::endl;
	i++;
}

int checkFile(std::string line, bool i)
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
	{
		std::cout << "Value is invalid" << std::endl;
		return (0);
	}
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

void parsingInputFile(char **av, std::map <std::string, float> myMap)
{
	std::ifstream inputFile(av[1]);
	if (!inputFile.is_open())
		throw NoInputFileException();
	std::string line;
	int i = 0;
	while (getline(inputFile, line))
	{
		if (checkFile(line, i))
			calcul(line, myMap);
		i++;
	}
}

void setMap(char **av)
{
	std::ifstream dataCsv("data.csv");
	if (!dataCsv.is_open())
		throw NoInputFileException();
	std::string line;
	std::string date;
	std::string price;
	float fprice;
	std::map <std::string, float> myMap;
	while (getline(dataCsv, line))
	{
		int i = 0;
		i = line.find(',');
		date = line.substr(0, i);
		price = line.substr(i + 1, line.size());
		fprice = atof(price.c_str());
		myMap.insert(std::make_pair(date, fprice));
	}
	parsingInputFile(av, myMap);
}
