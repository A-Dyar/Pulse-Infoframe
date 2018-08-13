// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	FactorialGenerator.hpp
// Purpose: Factorial Generator

#ifndef FactorialGenerator_HG_
#define FactorialGenerator_HG_

#include "Generator.hpp"
#include "RealList.hpp"
#include <regex>

class FactorialGenerator : public Generator {
public:
	std::unique_ptr<DataList> generate(std::vector<std::string> const& args) override
	{
		int firstimportantArg = 1;
		if (args[firstimportantArg] == "-s" || args[firstimportantArg] == "--shuffle") {
			++firstimportantArg;
		}
		++firstimportantArg;

		std::vector<long double> returnVector;
		switch (args.size()) {
		case 2:
			return std::make_unique<RealList>(std::vector<long double>{ 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800 });
		case 3:
			if (firstimportantArg == 3) {
				return std::make_unique<RealList>(std::vector<long double>{ 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800 });
			}
			else {
				for (long double num = 1, iterations = 1; iterations <= stoi(args[firstimportantArg]);  ++iterations, num *=iterations) {
					returnVector.push_back(num);
				}
				return std::make_unique<RealList>(returnVector);
			}
		case 4:
			if (firstimportantArg == 3) {
				for (long double num = 1, iterations = 1; iterations <= stoi(args[firstimportantArg]); ++iterations, num *= iterations) {
					returnVector.push_back(num);
				}
				return std::make_unique<RealList>(returnVector);
			}
			else {
				long double factorial = 1;
				for (long double iterations = 1; iterations <= stoi(args[firstimportantArg + 1]); ++iterations) {
					factorial *= iterations;
				}
				for (long double iterations = 1, nextInLine = stoi(args[firstimportantArg +1]); iterations <= stold(args[firstimportantArg]); ++iterations, ++nextInLine,factorial *= nextInLine) {
					returnVector.push_back(factorial);
				}
				return std::make_unique<RealList>(returnVector);
			}
		case 5:
			long double factorial = 1;
			for (long double iterations = 1; iterations <= stoi(args[firstimportantArg + 1]); ++iterations) {
				factorial *= iterations;
			}
			for (long double iterations = 1, nextInLine = stoi(args[firstimportantArg + 1]); iterations <= stold(args[firstimportantArg]); ++iterations, ++nextInLine, factorial *= nextInLine) {
				returnVector.push_back(factorial);
			}
			return std::make_unique<RealList>(returnVector);
		}
		throw "Incorrect arguements for factorial generator";
	}

	std::string help() override
	{
		return std::string("\tfac(t(orials?)?)? [num=10] [start=1]");
	}

	bool matches(std::string input) override
	{
		if (std::regex_match(input, std::regex("fac(t(orials?)?)?", std::regex::ECMAScript | std::regex::icase))) {
			return true;
		}
		return false;
	}
};

#endif // FactorialGenerator_HG_
