#pragma once
// this is the implementation file queue.cpp
// this is the implementation of the template class Stack
//the interface file for the template class queue is in the header file queue.h


#include "Evaluator.h"
#include <iostream>
#include <stdlib.h>
#include "stdafx.h"
#include <cmath>

using namespace std;

int Evaluator::Precedence(string oper)
{
	int precedence = 0;
	if ((oper == "!") || (oper == "++") || (oper == "--") || (oper == "-"))
		precedence = 8;
	else if (oper == "^")
		precedence = 7;
	else if ((oper == "*") || (oper == "/") || (oper == "%"))
		precedence = 6;
	else if ((oper == "+") || (oper == "-"))
		precedence = 5;
	else if ((oper == ">") || (oper == ">=") || (oper == "<") || (oper == "<="))
		precedence = 4;
	else if ((oper == "==") || (oper == "!="))
		precedence = 3;
	else if ((oper == "&&"))
		precedence = 2;
	else if ((oper == "||"))
		precedence = 1;
	return precedence;
}

void Evaluator::Process(string infixExpr)
{
	int result;
	int temp;
	char achar_1,achar_2; //each time loop runs, will take two char except the last time.

	string str = "";

	while (!opStack.empty())
	{
		opStack.pop();
	}

	while (!valStack.empty())
	{
		valStack.pop();
	}


	for (int i = 0; i < infixExpr.length(); i++)
	{
		//get two chars, they can be one operand one operator, two operators or two operands
		achar_1 = infixExpr[i];
		//if achar_1 is digit, "achar_1 + achar_2" would not be an operator like "==";
		if (isdigit(achar_1)) {
			temp = achar_1 - '0';//convert char to int;
			valStack.push(temp);
			std::cout << "Pushed into valStack: " << temp << endl;
		}
		//Note* achar_1 won't be digit below
		//if achar_1 is an operator, "achar_1 + achar_2" might be an operator but not necessarily
		else
		{
			// illustrate all two-size operator situations
			if (achar_1 == '+' || achar_1 == '=' || achar_1 == '-' || achar_1 == '*' || achar_1 == '/' || achar_1 == '!' || achar_1 == '^' || achar_1 == '%' || achar_1 == '>' || achar_1 == '<' || achar_1 == '(' || achar_1 == ')')
			{
				str.push_back(achar_1);
			}
			//special cases
			if (i != infixExpr.length() - 1)
			{
				achar_2 = infixExpr[i + 1]; //take second char;
				if (!(isdigit(achar_2))) {
					if (achar_1 == achar_2 && achar_1 == '+')
					{
						str = "++";// operator ++
						i++;
					}
					else if (achar_1 == achar_2 && achar_1 == '-')
					{
						str = "--"; //operator --
						i++;
					}
					else if (achar_1 == '>' && achar_2 == '=')
					{
						str = ">="; //operator >=
						i++;
					}
					else if (achar_1 == '<' && achar_2 == '=')
					{
						str = "<="; //operator <=
						i++;
					}
					else if (achar_1 == '!' && achar_2 == '=')
					{
						str = "!="; //operator !=
						i++;
					}
					else if (achar_1 == achar_2 && achar_1 == '&')
					{
						str = "&&"; //operator &&
						i++;
					}
					else if (achar_1 == achar_2 && achar_1 == '|')
					{
						str = "||"; //operator ||
						i++;
					}
					else if (achar_1 == achar_2 && achar_1 == '=')
					{
						str = "=="; //operator ||
						i++;
					}
				}
				
			}


			//push the operator into the opStack;
			if (str == "(")
			{
				opStack.push(str);
				std::cout << "Pushed into opStack: " << str << endl;
			}

			else if (str == ")")
			{
				while (opStack.top() != "(")
				{
					Execute();
					opStack.pop();
					break;
				}
			}

			else if(str != "")
			{
				Determination(str);
			}

			str = "";
			
		}


		
		
		
	}//end for
	
	while (!opStack.empty())
	{
		Execute();


	}
	result = valStack.top();
	cout << "The final result for the expression is: " << result << endl;
	cout << "\n\n" << "********************************" << endl;
}

void Evaluator::Determination(string str)
{
	if (opStack.empty())
	{
		opStack.push(str);
		std::cout << "Pushed into opStack: " << str << endl;
	}

	else if (Precedence(str)>Precedence(opStack.top()))
	{
		opStack.push(str);
		cout << "Pushed into opStack: " << str << endl;
	}

	else
	{
		while (!opStack.empty() && (Precedence(str) <= Precedence(opStack.top())))
		{
			Execute(); //
			if (opStack.empty())
				break;
		}
		opStack.push(str);
		cout << "Pushed into opStack: " << str << endl;
	}
}

void Evaluator::Execute()
{
	string op="";
	string first = "";
	string second = "";
	int result;

	op = opStack.top();
	opStack.pop();
	
	
	int operand2;
	operand2 = valStack.top();

	valStack.pop();
	
	if ((op == "!") || (op == "++") || (op == "--"))
	{

		if (op == "!")
		{
			result = (!operand2);
			valStack.push(result);
		}
		else if (op == "++")
		{
			result = (++operand2);
			valStack.push(result);
		}
		else if (op == "--")
		{
			result = (--operand2);
			valStack.push(result);
		}
		
	}
	// special case negative '-';
	else if ((op == "-") && (valStack.empty()))
	{
		
		result = -(operand2);
		valStack.push(result);
	}

	else
	{
		
		int operand1;
		operand1 = valStack.top();
		
		valStack.pop();
		
		if (op == "^")
		{
			result = pow(operand1,operand2);
			valStack.push(result);
		}
		else if (op == "%")
		{
			result = operand1 % operand2;
			valStack.push(result);
		}

		else if (op == ">")
		{
			if (operand1 > operand2)
				result = 1;
			else
				result = 0;
			valStack.push(result);
		}

		else if (op == "<")
		{
			if (operand1 < operand2)
				result = 1;
			else
				result = 0;
			valStack.push(result);
		}

		else if (op == "<=")
		{
			if (operand1 <= operand2)
				result = 1;
			else
				result = 0;
			valStack.push(result);
		}

		else if (op == ">=")
		{
			if (operand1 >= operand2)
				result = 1;
			else
				result = 0;
			valStack.push(result);
		}

		else if (op == "*")
		{
			
			result = operand1 * operand2;
			
			valStack.push(result);


			cout << "\n\n";
		}

		else if (op == "/")
		{
			if (operand2 == '0')
				cout << "Division by zero error!";

			else
			{
				result = operand1 / operand2;
				valStack.push(result);
			}

		}

		else if (op == "+")
		{
			result = operand1 + operand2;
			valStack.push(result);
		}

		//Arithmatic '-' operator;
		else if (op == "-")
		{
			result = operand1 - operand2;
			valStack.push(result);

		}
		else if (op == "==")
		{
			if (operand1 == operand2)
				result = 1;
			else
				result = 0;
			valStack.push(result);
		}

		else if (op == "!=")
		{
			if (operand1 != operand2)
				result = 1;
			else
				result = 0;
			valStack.push(result);
		}

		else if (op == "&&")
		{
			if (operand1 && operand2)
				result = 1;
			else
				result = 0;
			valStack.push(result);
		}

		else if (op == "||")
		{
			if (operand1 || operand2)
				result = 1;
			else
				result = 0;
			valStack.push(result);
		}
	}
	

}
