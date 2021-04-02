#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <map>
#include <cctype>

//This block of code provides the macros for memory leaks
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

//These lines instantiate the stacks and the map we will use to make things easier in converting Roman Numerals to modern numbers
stack<char> roman_numerals;
stack<int> add_stack;
map<char, size_t> value =
{
	{'I', 1},
	{'V', 5},
	{'X', 10},
	{'L', 50},
	{'C', 100},
	{'D', 500},
	{'M', 1000}
};

//These are the function declarations for the functions I will use in the main function.
void empty_stacks();
bool check_digit(string commmand);
void evaluate_digit(string command);
void evaluate_roman(string command);

int main(int argc, char* argv[])
{
	VS_MEM_CHECK; //This checks for memory leaks

	//This is the opening text you will see on the window that pops up when you compile.
	cout << "WELCOME TO THE NUMBER CONVERTER!!" << endl;
	cout << "TYPE IN ROMAN NUMERALS OR MODERN NUMBERS, AND I WILL OUTPUT THE OTHER!" << endl;
	cout << "MAKE SURE TO JUST TYPE IN NUMBERS OR CAPITAL ROMAN NUMERALS WITHOUT SPACES OR EXTRA CHARACTERS!" << endl;
	cout << "TYPE \"QUIT\" TO QUIT" << endl;

	//This is the loop that will take the user's input until they type in "QUIT"
	string command;
	while (getline(cin, command))
	{
		//This is the exit case for the loop
		if (command == "QUIT")
		{
			break;
		}

		//This if else block checks if the input is a modern number or not and calls the appropriate function
		if (check_digit(command) == true)
		{
			evaluate_digit(command);
		}
		else
		{
			evaluate_roman(command);
		}

		//This section of code outputs the Roman Numeral if there is a need to, and it outputs nothing if there was no Roman numeral to evaluate.
		size_t roman_sum = 0;
		while (!roman_numerals.empty())
		{
			roman_sum += value[roman_numerals.top()];
			roman_numerals.pop();
		}
		while (!add_stack.empty())
		{
			roman_sum += add_stack.top();
			add_stack.pop();
		}
		if (roman_sum > 0)
		{
			cout << " " << roman_sum << endl;
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}

//This function empties the stacks
void empty_stacks()
{
	while (!roman_numerals.empty()) roman_numerals.pop();
	while (!add_stack.empty()) add_stack.pop();
}

//This function returns true if the command is completely digits and false otherwise
bool check_digit(string command)
{
	for (size_t i = 0; i < command.size(); ++i)
	{
		if (isdigit(command[i]))
		{
			if (i == command.size() - 1) return true;
			else
			{
				continue;
			}
		}
		else
		{
			return false;
		}
	}
}

//This is the function that takes a modern number and converts it to Roman Numerals
//It starts at 1000, and slowly works its way down to 1
void evaluate_digit(string command)
{
	stringstream integer(command);
	int number = 0;
	integer >> number;
	while (number - 1000 >= 0)
	{
		number -= 1000;
		cout << "M";
	}
	while (number - 900 >= 0)
	{
		number -= 900;
		cout << "CM";
	}
	while (number - 500 >= 0)
	{
		number -= 500;
		cout << "D";
	}
	while (number - 400 >= 0)
	{
		number -= 400;
		cout << "CD";
	}
	while (number - 100 >= 0)
	{
		number -= 100;
		cout << "C";
	}
	while (number - 90 >= 0)
	{
		number -= 90;
		cout << "XC";
	}
	while (number - 50 >= 0)
	{
		number -= 50;
		cout << "L";
	}
	while (number - 40 >= 0)
	{
		number -= 40;
		cout << "XL";
	}
	while (number - 10 >= 0)
	{
		number -= 10;
		cout << "X";
	}
	while (number - 9 >= 0)
	{
		number -= 9;
		cout << "IX";
	}
	while (number - 5 >= 0)
	{
		number -= 5;
		cout << "V";
	}
	while (number - 4 >= 0)
	{
		number -= 4;
		cout << "IV";
	}
	while (number - 1 >= 0)
	{
		number -= 1;
		cout << "I";
	}
}

//This is the function that converts roman numerals to modern numbers
void evaluate_roman(string command)
{
	//These two lines define some enumerated integers to be useful in making sure the numbers are correct
	//subtract is the int we will use for this
	enum subtracted {DEFAULT, X, C };
	int subtract = DEFAULT;

	//These will just count how many of each numeral we have as needed
	int num_i = 0;
	int num_v = 0;
	int num_x = 0;
	int num_l = 0;
	int num_c = 0;
	int num_d = 0;
	int num_m = 0;
	
	bool ended = false; //This boolean has the purpose of letting the function know if the statement should be done or not

	for (size_t i = 0; i < command.size(); ++i)
	{
		//This breaks the loop should the statement need to be ended before it actually does
		if (ended)
		{
			cout << " UNKNOWN CHARACTER COMBINATION...CANNOT EVALUATE";
			empty_stacks();
			ended = false;
			break;
		}

		//This is the if statement for 'I'
		else if (command[i] == 'I')
		{
			roman_numerals.push(command[i]);
			num_i += 1;
		}

		//This is the if statement for 'V'
		else if (command[i] == 'V')
		{
			if (roman_numerals.empty())
			{
				roman_numerals.push(command[i]);
				num_v += 1;
			}
			else if (roman_numerals.top() == 'I')
			{
				if (num_i < 2)
				{
					add_stack.push(value[command[i]] - value[roman_numerals.top()]);
					roman_numerals.pop();
					num_v += 1;
					ended = true;
				}
				else
				{
					cout << " UNKNOWN CHARACTER COMBINATION...CANNOT EVALUATE";
					empty_stacks();
					break;
				}
			}
			else if (roman_numerals.top() == 'V')
			{
				cout << " UNKNOWN CHARACTER COMBINATION...CANNOT EVALUATE";
				empty_stacks();
				break;
			}
			else
			{
				roman_numerals.push(command[i]);
				num_v += 1;
			}
		}

		//This is the if statement for 'X'
		else if (command[i] == 'X')
		{
			if (roman_numerals.empty())
			{
				roman_numerals.push(command[i]);
				num_x += 1;
			}
			else if (roman_numerals.top() == 'I')
			{
				if (num_i < 2)
				{
					add_stack.push(value[command[i]] - value[roman_numerals.top()]);
					roman_numerals.pop();
					num_x += 1;
					ended = true;
				}
				else
				{
					cout << " UNKNOWN CHARACTER COMBINATION...CANNOT EVALUATE";
					empty_stacks();
					break;
				}
			}
			else if (subtract == X)
			{
				cout << " UNKNOWN CHARACTER COMBINATION...CANNOT EVALUATE";
				empty_stacks();
				break;
			}
			else if (roman_numerals.top() == 'V')
			{
				cout << " UNKNOWN CHARACTER COMBINATION...CANNOT EVALUATE";
				empty_stacks();
				break;
			}
			else if (roman_numerals.top() == 'X')
			{
				if (num_x < 3)
				{
					roman_numerals.push(command[i]);
					num_x += 1;
				}
				else
				{
					cout << " UNKNOWN CHARACTER COMBINATION... CANNOT EVALUATE";
					empty_stacks();
					break;
				}
			}
			else
			{
				roman_numerals.push(command[i]);
				num_x += 1;
			}
		}

		//This is the if statement for 'L'
		else if (command[i] == 'L')
		{
			if (roman_numerals.empty())
			{
				roman_numerals.push(command[i]);
				num_l += 1;
			}
			else if ((roman_numerals.top() == 'I') || (roman_numerals.top() == 'V') || (roman_numerals.top() == 'L'))
			{
				cout << " UNKNOWN CHARACTER COMBINATION... CANNOT EVALUATE";
				empty_stacks();
				break;
			}
			else if (roman_numerals.top() == 'X')
			{
				if (num_x < 2)
				{
					subtract = X;
					add_stack.push(value[command[i]] - value[roman_numerals.top()]);
					roman_numerals.pop();
					num_l += 1;
				}
				else
				{
					cout << " UNKNOWN CHARACTER COMBINATION...CANNOT EVALUATE";
					empty_stacks();
					break;
				}
			}
			else
			{
				roman_numerals.push(command[i]);
				num_l += 1;
			}
		}

		//This is the if statement for 'C'
		else if (command[i] == 'C')
		{
			if (roman_numerals.empty())
			{
				roman_numerals.push(command[i]);
				num_c += 1;
			}
			else if ((roman_numerals.top() == 'I') || (roman_numerals.top() == 'V') || (roman_numerals.top() == 'L'))
			{
				cout << " UNKNOWN CHARACTER COMBINATION... CANNOT EVALUATE";
				empty_stacks();
				break;
			}
			else if (roman_numerals.top() == 'X')
			{
				if (num_x < 2)
				{
					subtract = X;
					add_stack.push(value[command[i]] - value[roman_numerals.top()]);
					roman_numerals.pop();
					num_c += 1;
				}
				else
				{
					cout << " UNKNOWN CHARACTER COMBINATION...CANNOT EVALUATE";
					empty_stacks();
					break;
				}
			}
			else if (subtract == C)
			{
				cout << " UNKNOWN CHARACTER COMBINATION... CANNOT EVALUATE";
				empty_stacks();
				break;
			}
			else if (roman_numerals.top() == 'C')
			{
				if (num_c < 3)
				{
					roman_numerals.push(command[i]);
					num_c += 1;
				}
				else
				{
					cout << " UNKNOWN CHARACTER COMBINATION... CANNOT EVALUATE";
					empty_stacks();
					break;
				}
			}
			else
			{
				roman_numerals.push(command[i]);
				num_c += 1;
			}
		}

		//This is the if statement for 'D'
		else if (command[i] == 'D')
		{
			if (roman_numerals.empty())
			{
				roman_numerals.push(command[i]);
				num_d += 1;
			}
			else if ((roman_numerals.top() == 'I') || (roman_numerals.top() == 'V') || (roman_numerals.top() == 'X') || (roman_numerals.top() == 'L') || (roman_numerals.top() == 'D'))
			{
				cout << " UNKNOWN CHARACTER COMBINATION... CANNOT EVALUATE";
				empty_stacks();
				break;
			}
			else if (roman_numerals.top() == 'C')
			{
				if (num_c < 2)
				{
					subtract = C;
					add_stack.push(value[command[i]] - value[roman_numerals.top()]);
					roman_numerals.pop();
					num_d += 1;
				}
				else
				{
					cout << " UNKNOWN CHARACTER COMBINATION...CANNOT EVALUATE";
					empty_stacks();
					break;
				}
			}
			else
			{
				roman_numerals.push(command[i]);
				num_d += 1;
			}
		}

		//This is the if statement for 'M'
		else if (command[i] == 'M')
		{
			if (roman_numerals.empty())
			{
				roman_numerals.push(command[i]);
				num_m += 1;
			}
			else if ((roman_numerals.top() == 'I') || (roman_numerals.top() == 'V') || (roman_numerals.top() == 'X') || (roman_numerals.top() == 'L') || (roman_numerals.top() == 'D'))
			{
				cout << " UNKNOWN CHARACTER COMBINATION... CANNOT EVALUATE";
				empty_stacks();
				break;
			}
			else if (roman_numerals.top() == 'C')
			{
				if (num_c < 2)
				{
					subtract = C;
					add_stack.push(value[command[i]] - value[roman_numerals.top()]);
					roman_numerals.pop();
					num_m += 1;
				}
				else
				{
					cout << " UNKNOWN CHARACTER COMBINATION...CANNOT EVALUATE";
					empty_stacks();
					break;
				}
			}
			else
			{
				roman_numerals.push(command[i]);
				num_m += 1;
			}
		}

		//This statement takes care of all chars that are not Roman Numerals
		else
		{
			cout << " UNKNOWN CHARACTER...CANNOT EVALUATE";
			empty_stacks();
			break;
		}
	}
}