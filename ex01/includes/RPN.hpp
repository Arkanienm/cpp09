#ifndef RPN_HPP
#define RPN_HPP
#include <stdexcept>
#include <iostream>
#include <stack>
#include <string>
#include <stdlib.h>
#include <limits.h>

class RPN
{
	public:
		RPN();
		RPN(RPN const& src);
		RPN& operator=(RPN const& src);	
		~RPN();
		void rpn(char **av);
	private:
		std::stack<int> stk;
};


#endif