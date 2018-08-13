// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	RealList.hpp
// Purpose: Create a list for holding, shuffling, and printing real numbers

#ifndef RealList_HG_
#define RealList_HG_

#include "DataList.hpp"
#include <boost\multiprecision\cpp_int.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

class RealList : public DataList {
private:
	std::vector<long double> _realList;
public:
	RealList(std::vector<long double> input)
	{
		for (auto it : input) {
			_realList.push_back(it);
		}
	}

	~RealList()
	{
		_realList.clear();
	}


	void write() override {
		for (auto x : _realList) {
			std::cout << std::fixed << std::setprecision(5) << x << "\n";
		}
		std::cout << std::endl;
	}

	void shuffle() override {
		std::random_shuffle(_realList.begin(), _realList.end());
		write();
	}

};

#endif // RealList_HG_
