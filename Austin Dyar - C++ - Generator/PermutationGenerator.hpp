// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	PermutationGenerator.hpp
// Purpose: Permutation generator

#ifndef PermutationGenerator_HG_
#define PermutationGenerator_HG_

#include "Generator.hpp"
#include "StringList.hpp"
#include <regex>

class PermutationGenerator : public Generator {
public:
	std::unique_ptr<DataList> generate(std::vector<std::string> const& args) override
	{
		int firstimportantArg = 1;
		if (args[firstimportantArg] == "-s" || args[firstimportantArg] == "--shuffle") {
			++firstimportantArg;
		}
		++firstimportantArg;

		std::vector<std::string> returnVector;
		switch (args.size()) {
		case 2:
			returnVector = { "abc","acb","bac","bca","cab","cba" };

			return std::make_unique<StringList>(returnVector);
		case 3:
			if (firstimportantArg == 3) {
				returnVector = { "abc","acb","bac","bca","cab","cba" };

				return std::make_unique<StringList>(returnVector);
			}
			else {
				std::string input = args[firstimportantArg];
				std::sort(input.begin(), input.end());
				do {
					returnVector.push_back(input);
				} while (std::next_permutation(input.begin(), input.end()));
				
				return std::make_unique<StringList>(returnVector);
			}
		case 4:
			std::string input = args[firstimportantArg];

			std::sort(input.begin(), input.end());
			do {
				returnVector.push_back(input);
			} while (std::next_permutation(input.begin(), input.end()));

			return std::make_unique<StringList>(returnVector);
		}

		throw "Incorrect arguements for permutation generator";
	}

	std::string help() override
	{
		return std::string("\tperm(utations?)? [str=\"abc\"]");
	}

	bool matches(std::string input) override
	{
		if (std::regex_match(input, std::regex("perm(utations?)?", std::regex::ECMAScript | std::regex::icase))) {
			return true;
		}
		return false;
	}
};

#endif // PermutationGenerator_HG_
