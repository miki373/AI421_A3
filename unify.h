#ifndef __UNIFY_H__
#define __UNIFY_G__
#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <cmath>
#include "storage.h"
using namespace std;


class Unify{
public:
	Unify();
	void getInput();
	bool checkBrackets(string);
	void stripOutsideBrackets(string&);
	void printError();
	bool isError();
	string printcommand();

	int findMiddle(string);
	void makeTree();
	void makeTreeHelper(side *);
	bool isFunction(string);
	string getFuctionName(string&);
	bool isConst(string);
	bool isVar(string);
	void removeSpaces(string&);

	vector<string> splitIndideFunction(string);
	side * search(string, side *);
	side * search2(string, side *);
	void unify();
	side * rootNode;

private:
	string command;
	
	int error;

};


#endif