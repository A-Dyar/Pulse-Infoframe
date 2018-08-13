// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	ISOApp.hpp
// Purpose: The purpose of the project

#ifndef ISOApp_HG_
#define ISOApp_HG_

#include <cassert>
#include <string>
#include <vector>

class ISOApp {

private:
	// Attributes
	std::vector<std::string> args_;
	static ISOApp* singletonPtr_;

private:
	// Operations
	friend int main(int argc, char* argv[]);
	static int main(int argc, char* argv[]);


protected:
	ISOApp();
	virtual ~ISOApp() {}
	std::vector<std::string> const& args() { return args_; }
	virtual int run() = 0;
};

#endif // ISOApp_HG_