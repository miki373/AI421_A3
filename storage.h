#ifndef __STORAGE_H__
#define __STORAGE_H__
#include <string>
#include <vector>

struct side
{
	bool isFunction;
	bool isVar;
	bool isConst;
	std::string rawString;
	std::string functioName;
	std::string term;
	side * unifiedWith;
	side * left;
	side * right;
	std::vector<side*> children;
	int arity;
	
};


#endif