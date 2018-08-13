// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	GenerateApp.cpp
// Purpose: Do all major logic inside of the program

#include "ISOApp.hpp"
#include "GeneratorManager.hpp"
#include <iostream>

#ifndef GenerateApp_HG_
#define GenerateApp_HG_

class GenerateApp : public ISOApp {
	int run() override
	{
		// Checking initial arguments
		int firstImportantArg = 1;
		bool help = false;
		std::string helpMsg = "";
		std::string fullArgs = "";
		for (auto x : args()) {
			fullArgs.append(x + " ");
		}
		if ((std::regex_search(fullArgs, std::regex("-h", std::regex::ECMAScript | std::regex::icase))) 
			|| (std::regex_search(fullArgs, std::regex("--help", std::regex::ECMAScript | std::regex::icase)))){
			help = true;
			helpMsg.append(
				"generate 1.0 (c) 2018, Austin Dyar\n"
				"==================================\n\n"

				"useage:\n\n"

				"generate\t\t\t{displays help}\n"
				"generate -h | --help\t\t{displays help}\n"
				"generate -s | --shuffle\t\t{shuffle the data set}\n"
				"generate gen [Args...]\t\t{runs the generate 'gen' with 'options'}\n\n"


				"Generators:\n"
				"------------------------------------------------------------\n");
		}
		if (args()[firstImportantArg] == "-s" || args()[firstImportantArg] == "--shuffle") {
			firstImportantArg++;
		}


		bool successful = false;
		bool failedToFind = false;
		GeneratorManager temp = GeneratorManager::createManager();
		for (int index = 0;	index != temp.generators().size();	++index) {
			if (help) {
				helpMsg.append(temp.get(index)->help() + "\n");
			}

			// Find which generator matches the arguments provided in cmd
			else if (temp.get(index)->matches(args()[firstImportantArg])) {
				if (firstImportantArg > 1) {
					temp.get(index)->generate(args())->shuffle();
					failedToFind = true;
					successful = true;
					break;
				}
				else {
					temp.get(index)->generate(args())->write();
					failedToFind = true;
					successful = true;
					break;
				}
			}
		}

		if (help) {
			std::cout << helpMsg << std::endl;
		}
		else if (failedToFind) {
			assert(failedToFind && "Failed to find a generator matching the arguements provided.");
		}
		else if (firstImportantArg > 1 && !successful)
		{
			assert(successful && "Failed to shuffle.");
		}
		else if (!successful) {
			assert(successful && "Failed to write.");
		}

		return 1;
	}
} generateApp;

#endif // GenerateApp_HG_