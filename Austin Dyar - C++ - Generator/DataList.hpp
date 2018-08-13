// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	DataList.hpp
// Purpose: Base class DataList, used for polymorphism in Lists

#ifndef DataList_HG_
#define DataList_HG_

class DataList {
public:
	virtual void write() = 0;
	virtual void shuffle() = 0;
};

#endif // DataList_HG_
