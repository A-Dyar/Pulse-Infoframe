// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	PowerGenerator.hpp
// Purpose: Power generator

#ifndef PowerGenerator_HG_
#define PowerGenerator_HG_

#include "Generator.hpp"
#include "RealList.hpp"
#include <regex>

class PowerGenerator : public Generator {
public:
	std::unique_ptr<DataList> generate(std::vector<std::string> const& args) override
	{
		int firstimportantArg = 1;
		if (args[firstimportantArg] == "-s" || args[firstimportantArg] == "--shuffle") {
			++firstimportantArg;
		}
		++firstimportantArg;

		std::vector<long double> returnVector;
		long double base = 1;
		switch (args.size()) {
		case 2:
			returnVector = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
			return std::make_unique<RealList>(returnVector);
		case 3:
			if (firstimportantArg == 3) {
				returnVector = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
				return std::make_unique<RealList>(returnVector);
			}
			else {
				returnVector.push_back(base);
				for (long double iterations = 1; iterations < stold(args[firstimportantArg]); ++iterations) {
					returnVector.push_back(base *= 2);
				}
				return std::make_unique<RealList>(returnVector);
			}
		case 4:
			if (firstimportantArg == 3) {
				returnVector.push_back(base);
				for (long double iterations = 1; iterations < stold(args[firstimportantArg]); ++iterations) {
					returnVector.push_back(base *= 2);
				}
				return std::make_unique<RealList>(returnVector);
			}
			else {
				returnVector.push_back(base);
				for (long double iterations = 1; iterations < stold(args[firstimportantArg]); ++iterations) {
					returnVector.push_back(base *= stold(args[firstimportantArg + 1]));
				}
				return std::make_unique<RealList>(returnVector);
			}
		case 5:
			if (firstimportantArg == 3) {
				returnVector.push_back(base);
				for (long double iterations = 1; iterations < stold(args[firstimportantArg]); ++iterations) {
					returnVector.push_back(base *= stold(args[firstimportantArg + 1]));
				}
				return std::make_unique<RealList>(returnVector);
			}
			else {
				for (long double iterations = 1; iterations <= stold(args[firstimportantArg + 2]); ++iterations) {
					base *= stold(args[firstimportantArg + 1]);
				}
				returnVector.push_back(base);
				for (long double iterations = 1; iterations < stold(args[firstimportantArg]); ++iterations) {
					returnVector.push_back(base *= stold(args[firstimportantArg + 1]));
				}
				return std::make_unique<RealList>(returnVector);
			}
		case 6:
			for (long double iterations = 1; iterations <= stold(args[firstimportantArg + 2]); ++iterations) {
				base *= stold(args[firstimportantArg + 1]);
			}
			returnVector.push_back(base);
			for (long double iterations = 1; iterations < stold(args[firstimportantArg]); ++iterations) {
				returnVector.push_back(base *= stold(args[firstimportantArg + 1]));
			}
			return std::make_unique<RealList>(returnVector);

		}
		throw "Incorrect arguements for power generator";
	}

	std::string help() override
	{
		return std::string("\tpow(ers ? ) ? [num = 10][base = 2][starting - exponent = 0]");
	}

	bool matches(std::string input) override
	{
		if (std::regex_match(input, std::regex("pow(ers?)?", std::regex::ECMAScript | std::regex::icase))) {
			return true;
		}
		return false;
	}
};

#endif // PowerGenerator_HG_
