// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	PrimeGenerator.hpp
// Purpose: Prime generator

#ifndef PrimeGenerator_HG_
#define PrimeGenerator_HG_

#include "Generator.hpp"
#include "RealList.hpp"
#include <regex>

class PrimeGenerator : public Generator {
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
			returnVector = { 2, 3, 5, 7 };
			return std::make_unique<RealList>(returnVector);
		case 3:
			if (firstimportantArg == 3) {
				returnVector = { 2, 3, 5, 7 };
				return std::make_unique<RealList>(returnVector);
			}
			else {

				// create a vector of all numbers
				for (long double iterations = 2; iterations <= stold(args[firstimportantArg]); ++iterations) {
					returnVector.push_back(iterations);
				}
				 
				// Sieve of Eratosthenes
				long double const MARKED = 0;
				for (std::vector<long double>::reverse_iterator iterations = returnVector.rbegin(); iterations != returnVector.rend(); ++iterations) {
					long double primeValue = *iterations;
					if (primeValue == MARKED) {
						continue;
					}
					for (long double iMultiple = primeValue + primeValue; iMultiple < returnVector.size()/**(returnVector.end() - 1)*/;
						iMultiple += primeValue) {
						std::vector<long double>::iterator found = std::find(returnVector.begin(), returnVector.end(), iMultiple);
						if (found != returnVector.end()) {
							*found = MARKED;
						}
						if ((*(returnVector.end() - 1) - iMultiple) * std::floor((double)*(returnVector.end() - 1)/ (double)iMultiple) == 0) {
							*(returnVector.end() - 1) = MARKED;
						}
					}
				}

				// remove all the now Zero'd numbers which were not primes
				for (auto loc = returnVector.begin(); loc != returnVector.end();) {
					if (*loc == MARKED) {
						loc = returnVector.erase(loc);
					}
					else {
						++loc;
					}
				}

				return std::make_unique<RealList>(returnVector);
			}
		case 4:
			// create a vector of all numbers
			for (long double iterations = 2; iterations <= stold(args[firstimportantArg]); ++iterations) {
				returnVector.push_back(iterations);
			}

			// Sieve of Eratosthenes
			long double const MARKED = 0;
			for (std::vector<long double>::reverse_iterator iterations = returnVector.rbegin(); iterations != returnVector.rend(); ++iterations) {
				long double primeValue = *iterations;
				if (primeValue == MARKED) {
					continue;
				}
				for (long double iMultiple = primeValue + primeValue; iMultiple < returnVector.size()/**(returnVector.end() - 1)*/;
					iMultiple += primeValue) {
					std::vector<long double>::iterator found = std::find(returnVector.begin(), returnVector.end(), iMultiple);
					if (found != returnVector.end()) {
						*found = MARKED;
					}
					if ((*(returnVector.end() - 1) - iMultiple) * std::floor((double)*(returnVector.end() - 1) / (double)iMultiple) == 0) {
						*(returnVector.end() - 1) = MARKED;
					}
				}
			}

			// remove all the now Zero'd numbers which were not primes
			for (auto loc = returnVector.begin(); loc != returnVector.end();) {
				if (*loc == MARKED) {
					loc = returnVector.erase(loc);
				}
				else {
					++loc;
				}
			}

			return std::make_unique<RealList>(returnVector);
		}

		throw "Incorrect arguements for prime generator";
	}

	std::string help() override
	{
		return std::string("\tpri(mes?)? [limit=10]");
	}

	bool matches(std::string input) override
	{
		if (std::regex_match(input, std::regex("pri(mes?)?", std::regex::ECMAScript | std::regex::icase))) {
			return true;
		}
		return false;
	}
};

#endif // PrimeGenerator_HG_
