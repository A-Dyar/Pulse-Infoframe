// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	ISOApp.cpp
// Purpose: Start the program and navigate to ISOApp run method

#include "ISOApp.hpp"
#include <iostream>

#pragma region ISOApp_utility

int main(int argc, char* argv[]) try {
	return ISOApp::main(argc, argv);
}

catch (std::exception& e) {
	std::cerr << "Error: std::exception caught\n\t" << e.what() << "\n";
	return EXIT_FAILURE;
}

catch (...) {
	std::cerr << "Error: unknown exception caught.\n";
	return EXIT_FAILURE;
}

#pragma endregion

#pragma region ISOApp_class

ISOApp* ISOApp::singletonPtr_ = nullptr;

ISOApp::ISOApp() {
	assert(!singletonPtr_  && "ISOApp::singletonPtr_ has already been initialized.");
	singletonPtr_ = this;
}

int ISOApp::main(int argc, char* argv[]) {
	assert(singletonPtr_ && "ISOApp::singletonPtr_ not initialized.");
	singletonPtr_->args_.clear();
	for (int i = 0; i < argc; ++i)
		singletonPtr_->args_.push_back(argv[i]);

	return singletonPtr_->run();
}

#pragma endregion