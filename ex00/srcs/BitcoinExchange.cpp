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

void setMap()
{
	std::ifstream dataCsv("data.csv");
	if (!dataCsv.is_open())
		throw NoInputFileException();
	std::string line;
	std::string date;
	std::string price;
	float fprice;
	std::map <std::string, float> myMap;
	// std::map <std::string, float>::iterator it = myMap.begin();
	while (getline(dataCsv, line))
	{
		int i = 0;
		i = line.find(',');
		date = line.substr(0, i - 1);
		price = line.substr(i + 1, line.size());
		fprice = atof(price.c_str());
		myMap.insert(std::make_pair(date, fprice));
	}
	// it = myMap.begin();
	// while (it != myMap.end())
	// {
	// 	std::cout << "map date = " << it->first << " , " << "map price = " << it->second << std::endl;
	// 	it++;
	// }
	// it = myMap.begin();
	// std::cout << "map date = " << it->first << " , " << "map price = " << it->second << std::endl;
}

static void checkDate(std::string line)
{
	for (int i = 0; i < 4; i++)
	{
		if (!isdigit(line.at(i)))
			throw WrongInputFile();
	}
	for (int i = 5; i < 7; i++)
	{
		if (!isdigit(line.at(i)))
			throw WrongInputFile();
	}
	for (int i = 8; i < 10; i++)
	{
		if (!isdigit(line.at(i)))
			throw WrongInputFile();
	}
	int month = atoi(line.substr(5, 2).c_str());
	int day = atoi(line.substr(8, 2).c_str());
	int year = atoi(line.substr(0, 4).c_str());
	if (month > 12 || month <= 0 || day > 32 || day <= 0)
		throw WrongInputFile();
	if (month == 2)
	{
		if ((year % 4 == 0 && year %100 != 0) || (year % 400 == 0))
		{
			if (day > 29)
				throw WrongInputFile();
		}
		else
		{
			if (day > 28)
				throw WrongInputFile();
		}
	}
	else if ((month % 2 != 0 && month <= 7) || (month % 2 == 0 && month >= 8))
	{
		if (day > 31)
			throw WrongInputFile();
	}
	else
	{
		if (day > 30)
		{
			throw WrongInputFile();
		}
	}
}

static void checkValue(std::string line)
{
	size_t index = line.find('|') + 1;
	size_t size = line.size() - index - 1;
	if (size <= 0 || size > 4)
		throw WrongInputFile();
	for (size_t i = 13; i < line.size(); i++)
	{
		if (!isdigit(line.at(i)))
			throw WrongInputFile();
	}
	int value = atoi(line.substr(13, size).c_str());
	if (value > 1000 || value < 0)
		throw WrongInputFile();
	std::cout << "index = " << index << " size = " << size << " line size = " << line.size() << " value = " << value << std::endl;
}

void parsingInputFile(char **av)
{
	std::ifstream inputFile(av[1]);
	if (!inputFile.is_open())
		throw NoInputFileException();
	std::string line;
	int i = 0;
	while (getline(inputFile, line))
	{
		std::cout << line << std::endl;

		if (i == 0)
		{
			if (line != "date | value")
			{
				throw WrongInputFile();
			}
		}
		else
		{
			if (line.find("|") == std::string::npos || line.size() < 10 || line.at(11) != '|')
				throw WrongInputFile();
			if (line.at(4) != '-' || line.at(7) != '-' || line.at(10) != ' ' || line.at(12) != ' ')
				throw WrongInputFile();
			checkDate(line);
			checkValue(line);
		}
		i++;
	}
}