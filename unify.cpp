#include "unify.h"

Unify::Unify()
{
	command = "";
	error = -1;
	
	
}




// Takes care of user input.. Makes sure period is inserted at the end of the command //
void Unify::getInput()
{
	string userInput;
	string temp;
	string prologCommand = "unify_with_occurs_check";
	int choice;

	printf("Do you want program to enter '%s' for you?\nYes[1], No[0]: ", prologCommand.c_str());
	cin >> choice;

	if (choice > 0)
	{
		userInput = prologCommand;
		printf("| ?- %s", prologCommand.c_str());
		do{
			cin >> temp;
			userInput.append(temp);
		} while (userInput.back() != '.');
	}
	else
	{
		printf("| ?- ");
		do{
			cin >> temp;
			userInput.append(temp);
		} while (userInput.back() != '.');
	}

	if (userInput.compare(0, prologCommand.size(), prologCommand) != 0)
	{
		error = 3;
		printError();
	}

	userInput.pop_back(); // remove . (dot)

	removeSpaces(userInput); // remove spaces

	if (checkBrackets(userInput))
	{
		command = userInput;
	}
	else
	{
		error = 1;
		printError();
	}
}

bool Unify::checkBrackets(string input){

	stack<char> openBracket;

	for (unsigned int i = 0; i < input.size(); i++)
	{
		if (input[i] == '(')
		{
			openBracket.push(input[i]);
		}

		if (input[i] == ')')
		{
			if (openBracket.empty()){
				return false;
			}
			else{
				openBracket.pop();
			}
		}
	}

	if (!openBracket.empty()){
		return false;
	}
	else{
		return true;
	}

}





string Unify::printcommand()
{
	return command;
}




void Unify::printError()
{
	switch (error)
	{
	case 1: printf("Error: Check brackets.\n"); break;
	case 2: printf("Error: Check there is comma between terms.\n"); break;
	case 3: printf("Error: Unrecognized command, check spelling.\n"); break;
	case 4: printf("Error: Command contains at least one illegal character.\n"); break;
	default:
		break;
	}
}

bool Unify::isError()
{
	if (error != -1){
		return true;
	}
	else{
		return false;
	}
}

int Unify::findMiddle(string function)
{
	int openBracket = 0, closedBracket = 0, middle = 0;
	for (unsigned int i = 0; i < function.size(); i++){
		if (function[i] == '(')
		{
			openBracket++;
		}
		if (function[i] == ')')
		{
			closedBracket++;
		}
		if (function[i] == ',' && ((openBracket - closedBracket) == 0))
		{
			middle = i;
			break;
		}
	}
	if (middle == 0){
		error = 2;
		return -1;
	}
	
	return middle;
}



void Unify::makeTree()
{


	rootNode = new side;

	rootNode->rawString = command;
	rootNode->term = "";
	rootNode->isFunction = false;
	rootNode->right = nullptr;
	rootNode->left = nullptr;
	rootNode->unifiedWith = nullptr;
	makeTreeHelper(rootNode);


}

void Unify::makeTreeHelper(side * node)
{
	string temp = node->rawString;

	cout << node->rawString << endl;
	
	if (isFunction(temp))
	{
		
		// INIT SOTRAGE
		node->functioName = getFuctionName(temp);

		node->term = "";

		node->isFunction = true;

		node->isConst = false;

		node->isVar = false;

		vector<string> tokens;

		tokens = splitIndideFunction(temp);

		node->arity = tokens.size();
		// END INIT



		

		side * searchRes;

		for (unsigned int i = 0; i < tokens.size(); i++)
		{
			searchRes = search2(tokens[i], rootNode);
			if (searchRes == nullptr)
			{
				cout <<"\nParent: " << node->rawString << "Token: " << tokens[i] << endl;
				side * newChild = new side;
				newChild->rawString = tokens[i];
				node->children.push_back(newChild);
				makeTreeHelper(newChild);
			}
			else
			{
				cout << "FOUND BY SEARCH: " << searchRes->rawString;
				node->children.push_back(searchRes);
			}
		}




		// END PARSE

	}
	else if (isVar(temp))
	{
		node->isVar = true;

		node->isFunction = false;

		node->isConst = false;

		node->term = temp;

		node->left = nullptr;

		node->right = nullptr;

		return;
	}
	else if (isConst(temp))
	{
		node->isConst = true;

		node->isVar = false;

		node->isFunction = false;

		node->term = temp;

		node->left = nullptr;

		node->right = nullptr;

		return;
	}

}






bool Unify::isFunction(string test)
{
	bool moveOn = false;
	if (islower(test[0]))
	{
		for (unsigned int i = 1; i < test.size(); i++)
		{
			if (test[i] == ' ' || test[i] == ')' || test[i] == ','){
				return false;
			}

			if (test[i] == '('){
				return true;
			}
			
			
		}
	}
	return false;
}

string Unify::getFuctionName(string &function)
{
	int position = -1;
	for (unsigned int i = 0; i < function.size(); i++)
	{
		if (function[i] == '(')
		{
			position = i;
			break;
		}
	}

	// save function name
	string tempFname = function.substr(0, position);

	// trim out function name
	function = function.substr(position+1);
	
	// remove trailing )
	if (function.back() == ')')
	{
		function.pop_back();
	}

	// return function
	return tempFname;
}


bool Unify::isConst(string constant)
{
	return islower(constant[0]);
}

bool Unify::isVar(string variable)
{
	return isupper(variable[0]);
}

void Unify::removeSpaces(string& command)
{
	for (unsigned int i = 0; i < command.size(); i++)
	{
		if (command[i] == ' ')
		{
			command.erase(i, 1);
			i--;
		}
	}
}


void Unify::unify()
{
	side * left, * right;

	left = rootNode->left;
	right = rootNode->right;

	// function and function
	if (left->isFunction && right->isFunction)
	{
		// unify all 
	}
	// one function and other variable
	else if ((right->isFunction && left->isVar) || (left->isFunction && right->isVar))
	{
		// do something
	}
	// one variable other constant
	else if ((left->isConst && right->isVar) || (right->isConst && left->isVar))
	{
		// do something
	}
	// variable && variable
	else if (left->isVar && right->isVar)
	{
		// do something
	}
}


// Search tree for target
side * Unify::search(string target, side * node)
{
	if (node->term == target)
	{
		return node;
	}
	side * found = nullptr;
	
	if (node->left != nullptr)
	{
		found = search(target, node->left);
	}
	else
	{
		if (node->right != nullptr)
		{
			found = search(target, node->right);
		}
	}
	
	if (found != nullptr)
	{
		return found;
	}
	else
	{
		return nullptr;
	}
	
	
	
}

vector<string> Unify::splitIndideFunction(string function)
{
	
	unsigned int lastComma = 0;
	int opening = 0, closing = 0;
	vector<string> tokens;
	string tempToken;
	for (unsigned int i = 0; i < function.size(); i++)
	{
		
		if (function[i] == '(')
		{
			opening++;
		}
		if (function[i] == ')')
		{
			closing++;
		}
		if (function[i] == ',')
		{
			if ((opening - closing) == 0)
			{
				
				tempToken = function.substr(lastComma, (i - lastComma));
				if (tempToken[0] == ',')
				{
					tempToken.erase(0, 1);
				}
		
				tokens.push_back(tempToken);
				lastComma = i;
			}
		}
		
	}
	// last 
	
	tempToken = function.substr(lastComma);
	if (tempToken[0] == ',')
	{
		tempToken.erase(0, 1);
	}
	tokens.push_back(tempToken);

	return tokens;

}


side * Unify::search2(string target, side * node)
{
	if (node->term == target)
	{
		return node;
	}
	side * found = nullptr;

	for (unsigned int i = 0; i < node->children.size(); i++)
	{
		found = search2(target, node->children[i]);
		if (found != nullptr)
		{
			return found;
		}
	}
	return found;
}