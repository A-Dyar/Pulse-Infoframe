// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	DieGenerator.hpp
// Purpose: Die Generator

#ifndef DieGenerator_HG_
#define DieGenerator_HG_

#include "Generator.hpp"
#include "IntegerList.hpp"
#include <regex>

class DieGenerator : public Generator {
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
			for (int iterations = 1; iterations <= 10; ++iterations) {
				returnVector.push_back((1 + rand() % 6) + (1 + rand() % 6));
			}
			return std::make_unique<IntegerList>(returnVector);
		case 3:
			if (firstimportantArg == 3) {
				for (int iterations = 1; iterations <= 10; ++iterations) {
					returnVector.push_back((1 + rand() % 6) + (1 + rand() % 6));
				}
				return std::make_unique<IntegerList>(returnVector);
			}
			else {
				for (int iterations = 1; iterations <= stoi(args[firstimportantArg]); ++iterations) {
					returnVector.push_back((1 + rand() % 6) + (1 + rand() % 6));
				}
				return std::make_unique<IntegerList>(returnVector);
			}
		case 4:
			if (firstimportantArg == 3) {
				for (int iterations = 1; iterations <= stoi(args[firstimportantArg]); ++iterations) {
					returnVector.push_back((1 + rand() % 6) + (1 + rand() % 6));
				}
				return std::make_unique<IntegerList>(returnVector);
			}
			else {
				std::string tempd;
				std::string tempf;
				bool nextVar = false;
				for (auto car : args[firstimportantArg + 1]) {
					if (isdigit(car) && !nextVar) {
						tempd.push_back(car);
					}
					else if (isdigit(car) && nextVar) {
						tempf.push_back(car);
					}
					else {
						nextVar = true;
					}
				}

				int dice(stoi(tempd));
				int face(stoi(tempf));

				for (int iterations = 1; iterations <= stoi(args[firstimportantArg]); ++iterations) {
					int total = 0;
					for (int whichDie = 1; whichDie <= dice; ++whichDie) {
						total += (1 + rand() % (face));
					}
					returnVector.push_back(total);
				}
				return std::make_unique<IntegerList>(returnVector);
			}
		case 5:
			std::string tempd;
			std::string tempf;
			bool nextVar = false;
			for (auto car : args[firstimportantArg]) {
				if (isdigit(car) && !nextVar) {
					tempd.push_back(car);
				}
				else if (isdigit(car) && nextVar) {
					tempf.push_back(car);
				}
				else {
					nextVar = true;
				}
			}


			int dice(stoi(tempd));
			int face(stoi(tempf));


			for (int iterations = 1; iterations <= stoi(args[firstimportantArg]); ++iterations) {
				int total = 0;
				for (int whichDie = 1; whichDie <= dice; ++whichDie) {
					total += (1 + rand() % (face));
				}
				returnVector.push_back(total);
			}
			return std::make_unique<IntegerList>(returnVector);
		}

		throw "Incorrect arguements for die generator";
	}

	std::string help() override
	{
		return std::string("\tdie(rolls?)? [nRolls=10] [dice=2d6]");
	}

	bool matches(std::string input) override
	{
		if (std::regex_match(input, std::regex("die(rolls?)?", std::regex::ECMAScript | std::regex::icase))) {
			return true;
		}
		return false;
	}
};

#endif // DieGenerator_HG_
