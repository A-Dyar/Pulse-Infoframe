// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	LinearGenerator.hpp
// Purpose: Linear generator

#ifndef LinearGenerator_HG_
#define LinearGenerator_HG_

#include "Generator.hpp"
#include "IntegerList.hpp"
#include <regex>

class LinearGenerator : public Generator{
public:
	std::unique_ptr<DataList> generate(std::vector<std::string> const& args) override
	{
		int firstimportantArg = 1;
		if (args[firstimportantArg] == "-s" || args[firstimportantArg] == "--shuffle") {
			++firstimportantArg;
		}
		++firstimportantArg;

		std::vector<int> returnVector;
		switch (args.size()) {
		case 2:
			return std::make_unique<IntegerList>(std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
		case 3:
			if (firstimportantArg == 3) {
				return std::make_unique<IntegerList>(std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			}
			else {
				for (int num = 1, iterations = 1; iterations <= stoi(args[firstimportantArg]); ++num, ++iterations) {
					returnVector.push_back(num);
				}
				return std::make_unique<IntegerList>(returnVector);
			}
		case 4:
			if (firstimportantArg == 3) {
				for (int num = 1, iterations = 1; iterations <= stoi(args[firstimportantArg]); ++num, ++iterations) {
					returnVector.push_back(num);
				}
				return std::make_unique<IntegerList>(returnVector);
			}
			else {
				for (int num = stoi(args[firstimportantArg + 1]), iterations = 1; iterations <= stoi(args[firstimportantArg]); ++num, ++iterations) {
					returnVector.push_back(num);
				}
				return std::make_unique<IntegerList>(returnVector);
			}
		case 5:
			if (firstimportantArg == 3) {
				for (int num = stoi(args[firstimportantArg + 1]), iterations = 1; iterations <= stoi(args[firstimportantArg]); ++num, ++iterations) {
					returnVector.push_back(num);
				}
				return std::make_unique<IntegerList>(returnVector);
			}
			else {
				for (int num = stoi(args[firstimportantArg + 1]), iterations = 1; iterations <= stoi(args[firstimportantArg]); num+=stoi(args[firstimportantArg+2]), ++iterations) {
					returnVector.push_back(num);
				}
				return std::make_unique<IntegerList>(returnVector);
			}
		case 6:
			for (int num = stoi(args[firstimportantArg + 1]), iterations = 1; iterations <= stoi(args[firstimportantArg]); num += stoi(args[firstimportantArg + 2]), ++iterations) {
				returnVector.push_back(num);
			}
			return std::make_unique<IntegerList>(returnVector);
		}

		throw "Incorrect arguements for linear generator";
	}

	std::string help() override
	{
		return std::string("\tlin(ear)? [num=10] [start=1] [increment=1]");
	}

	bool matches(std::string input) override
	{
		if (std::regex_match(input, std::regex("lin(ear)?", std::regex::ECMAScript | std::regex::icase))) {
			return true;	
		}
		return false;
	}
};

#endif // LinearGenerator_HG_
