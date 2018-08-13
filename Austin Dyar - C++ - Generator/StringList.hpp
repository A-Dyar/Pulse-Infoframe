// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	StringList.hpp
// Purpose: Create a list for holding, shuffling, and printing strings

#ifndef StringList_HG_
#define StringList_HG_

#include "DataList.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

class StringList : public DataList {
private:
	std::vector<std::string> _stringList;
public:
	StringList(std::vector<std::string> input)
	{
		for (auto it : input) {
			_stringList.push_back(it);
		}
	}

	~StringList()
	{
		_stringList.clear();
	}


	void write() override {
		for (auto x : _stringList) {
			std::cout << x.c_str() << "\n";
		}
		std::cout << std::endl;
	}

	void shuffle() override {
		std::random_shuffle(_stringList.begin(), _stringList.end());
		write();
	}

};

#endif // StringList_HG_
