#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <stdexcept>
#include <iostream>
#include <map>


class NoFileCsvException : public std::exception
{
	public:
		NoFileCsvException(){}
		virtual const char* what() const throw();
};

class NoInputFileException : public std::exception
{
	public:
		NoInputFileException(){}
		virtual const char* what() const throw();
};

class WrongInputFile : public std::exception
{
	public:
		WrongInputFile(){}
		virtual const char* what() const throw();
};

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange& src);
		BitcoinExchange& operator=(BitcoinExchange& src);
		~BitcoinExchange();
		void setMap(char **av);
		int checkValue(std::string line);
		int checkDate(std::string line);
		void calcul(std::string line);
		int checkFile(std::string line, bool i);
		void parsingInputFile(char **av);
		
	private:
		std::map <std::string, float> myMap;
};
#endif