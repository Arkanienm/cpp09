#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <stdexcept>
#include <iostream>


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

void setMap();
void parsingInputFile(char **av);

#endif