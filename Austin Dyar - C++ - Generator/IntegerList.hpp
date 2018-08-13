// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	IntegerList.hpp
// Purpose: Create a list for holding, shuffling, and printing integers

#ifndef IntegerList_HG_
#define IntegerList_HG_

#include "DataList.hpp"
#include <algorithm>
#include <vector>
#include <iostream>

class IntegerList : public DataList {
private:
	std::vector<int> _integerList;
public:
	IntegerList(std::vector<int> input)
	{
		for (auto it : input) {
			_integerList.push_back(it);
		}
	}

	~IntegerList()
	{
		_integerList.clear();
	}

	
	void write() override {
		for (auto x : _integerList) {
			std::cout << x << "\n";
		}
		std::cout << std::endl;
	}

	void shuffle() override {
		std::random_shuffle(_integerList.begin(), _integerList.end());
		write();
	}
	
};

#endif // IntegerList_HG_
