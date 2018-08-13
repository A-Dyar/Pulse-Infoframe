// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	FibonacciGenerator.hpp
// Purpose: Fibonacci Generator

#ifndef FibonacciGenerator_HG_
#define FibonacciGenerator_HG_

#include "Generator.hpp"
#include "RealList.hpp"
#include <regex>

class FibonacciGenerator : public Generator {
public:
	std::unique_ptr<DataList> generate(std::vector<std::string> const& args) override
	{
		int firstimportantArg = 1;
		if (args[firstimportantArg] == "-s" || args[firstimportantArg] == "--shuffle") {
			++firstimportantArg;
		}
		++firstimportantArg;

		std::vector<long double> returnVector;
		long double a = 0;
		long double b = 1;
		switch (args.size()) {
		case 2:
			returnVector.push_back(b);
			for (long double iterations = 1; iterations <= 9; ++iterations) {
				long double c = a + b;
				returnVector.push_back(c);
				a = b;
				b = c;
			}
			return std::make_unique<RealList>(returnVector);
		case 3:
			if (firstimportantArg == 3) {
				returnVector.push_back(b);
				for (long double iterations = 1; iterations <= 9; ++iterations) {
					long double c = a + b;
					returnVector.push_back(c);
					a = b;
					b = c;
				}
				return std::make_unique<RealList>(returnVector);
			}
			else {
				returnVector.push_back(b);
				for (long double iterations = 1; iterations < stold(args[firstimportantArg]); ++iterations) {
					long double c = a + b;
					returnVector.push_back(c);
					a = b;
					b = c;
				}
				return std::make_unique<RealList>(returnVector);
			}
		case 4:
			if (firstimportantArg == 3) {
				returnVector.push_back(b);
				for (long double iterations = 1; iterations < stold(args[firstimportantArg]); ++iterations) {
					long double c = a + b;
					returnVector.push_back(c);
					a = b;
					b = c;
				}
				return std::make_unique<RealList>(returnVector);
			}
			else {
				for (long double iterations = 1; iterations < stold(args[firstimportantArg + 1]); ++iterations) {
					long double c = a + b;
					a = b;
					b = c;
				}

				returnVector.push_back(b);
				for (long double iterations = 1; iterations < stold(args[firstimportantArg]); ++iterations) {
					long double c = a + b;
					returnVector.push_back(c);
					a = b;
					b = c;
				}
				
				return std::make_unique<RealList>(returnVector);
			}
		case 5:
			for (long double iterations = 1; iterations < stold(args[firstimportantArg + 1]); ++iterations) {
				long double c = a + b;
				a = b;
				b = c;
			}

			returnVector.push_back(b);
			for (long double iterations = 1; iterations < stold(args[firstimportantArg]); ++iterations) {
				long double c = a + b;
				returnVector.push_back(c);
				a = b;
				b = c;
			}

			return std::make_unique<RealList>(returnVector);
		}

		throw "Incorrect arguements for fibonacci generator";
	}

	std::string help() override
	{
		return std::string("\tfib(onacci)? [num=10] [start=1]");
	}

	bool matches(std::string input) override
	{
		if (std::regex_match(input, std::regex("fib(onacci)?", std::regex::ECMAScript | std::regex::icase))) {
			return true;
		}
		return false;
	}
};

#endif // FibonacciGenerator_HG_
