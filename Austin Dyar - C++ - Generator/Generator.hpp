// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	Generator.hpp
// Purpose: Base class generator, used in polymorphism in Generators

#ifndef Generator_HG_
#define Generator_HG_

#include "DataList.hpp"
#include <vector>
#include <string>

class Generator {
public: 
	virtual std::unique_ptr<DataList> generate(std::vector<std::string> const& args) = 0;
	virtual std::string help() = 0;
	virtual bool matches(std::string input) = 0;
};
#endif // Generator_HG_
