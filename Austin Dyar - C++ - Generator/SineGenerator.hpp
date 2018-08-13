// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	SineGenerator.hpp
// Purpose: Sine wave generator

#ifndef SineGenerator_HG_
#define SineGenerator_HG_

#include "Generator.hpp"
#include "RealList.hpp"
#include <boost\math\constants\constants.hpp>
#include <boost\math\special_functions.hpp>
#include <regex>

class SineGenerator : public Generator {
public:
	std::unique_ptr<DataList> generate(std::vector<std::string> const& args) override
	{
		int firstimportantArg = 1;
		if (args[firstimportantArg] == "-s" || args[firstimportantArg] == "--shuffle") {
			++firstimportantArg;
		}
		++firstimportantArg;

		long double cycles = 10;
		long double samples = 30;

		long double total = std::ceil(cycles * samples);
		std::vector<long double> returnVector;
		switch (args.size()) {
		case 2:
			for (long double index = 0.0; index <= total; ++index) {
				long double theta = boost::math::constants::two_pi<long double>() * (index / samples);
				long double result = std::sin(theta);
				returnVector.push_back(result);
			}

			return std::make_unique<RealList>(returnVector);
		case 3:
			if (firstimportantArg == 3) {
				for (long double index = 0.0; index <= total; ++index) {
					long double theta = boost::math::constants::two_pi<long double>() * (index / samples);
					long double result = std::sin(theta);
					returnVector.push_back(result);
				}

				return std::make_unique<RealList>(returnVector);
			}
			else {
				cycles = stold(args[firstimportantArg]);
				total = std::ceil(cycles * samples);
				for (long double index = 0.0; index <= total; ++index) {
					long double theta = boost::math::constants::two_pi<long double>() * (index / samples);
					long double result = std::sin(theta);
					returnVector.push_back(result);
				}

				return std::make_unique<RealList>(returnVector);
			}
		case 4:
			if (firstimportantArg == 3) {
				cycles = stold(args[firstimportantArg]);
				total = std::ceil(cycles * samples);
				for (long double index = 0.0; index <= total; ++index) {
					long double theta = boost::math::constants::two_pi<long double>() * (index / samples);
					long double result = std::sin(theta);
					returnVector.push_back(result);
				}

				return std::make_unique<RealList>(returnVector);
			}
			else {
				cycles = stold(args[firstimportantArg]);
				samples = stold(args[firstimportantArg + 1]);
				total = std::ceil(cycles * samples);
				for (long double index = 0.0; index <= total; ++index) {
					long double theta = boost::math::constants::two_pi<long double>() * (index / samples);
					long double result = std::sin(theta);
					returnVector.push_back(result);
				}
				
				return std::make_unique<RealList>(returnVector);
			}
		case 5:
			cycles = stold(args[firstimportantArg]);
			samples = stold(args[firstimportantArg + 1]);
			total = std::ceil(cycles * samples);
			for (long double index = 0.0; index <= total; ++index) {
				long double theta = boost::math::constants::two_pi<long double>() * (index / samples);
				long double result = std::sin(theta);
				returnVector.push_back(result);
			}

			return std::make_unique<RealList>(returnVector);
		}
		throw "Incorrect arguements for permutation generator";
	}

	std::string help() override
	{
		return std::string("\tsine? [nCycles=10.0] [nSamplesPerCycle=30]");
	}

	bool matches(std::string input) override
	{
		if (std::regex_match(input, std::regex("sine?", std::regex::ECMAScript | std::regex::icase))) {
			return true;
		}
		return false;
	}
};

#endif // SineGenerator_HG_
