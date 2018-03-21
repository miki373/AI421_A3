#include "unify.h"



int main()
{
	Unify command;
	

	
	command.getInput();
	string comm =  command.printcommand();
	cout << comm << endl;
	command.makeTree();
	side * root = command.rootNode;
	side * found = command.search("a", root);
	if (found == nullptr)
	{
		cout << "NO WORK";
	}
	else
	{
		cout << "WORK" << found->rawString << endl;
		
	}


	
}

