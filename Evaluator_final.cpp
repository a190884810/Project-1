#pragma once
// this is the implementation file queue.cpp
// this is the implementation of the template class Stack
//the interface file for the template class queue is in the header file queue.h


#include "Evaluator.h"
#include <iostream>
#include <stdlib.h>
#include "stdafx.h"
#include <sstream>
#include <cmath>

using namespace std;

//a method for evaluating the precedence of each operator
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

//Main Evaluating function
void Evaluator::Process(string infixExpr)
{
	int result;    // final result
	int temp;	   //operand input		
	int count;	   
	bool is_space = false;
	char temp_char;
	char achar_1,achar_2; //each time loop runs, will take two char except the last time.
	is_error = false;  //determine whether there is an error
	int i;
	string temp_string = "";   //reading extra stuff in the process of reading operator
	string digit_string = "";  //reading operands
	string str = "";        //reading operators

	Expression = infixExpr;  //Infix expression

	//make sure two stacks are clear
	while (!opStack.empty())
	{
		opStack.pop();
	}

	while (!valStack.empty())
	{
		valStack.pop();
	}

	//main for loop, getting operands and operators
	for (position = 0; position < infixExpr.length(); position++)
	{
		//get two chars, they can be one operand one operator, two operators or two operands
		achar_1 = infixExpr[position];
		//if achar_1 is digit, "achar_1 + achar_2" would not be an operator like "==";
		if (isdigit(achar_1)) {
			//handle multiple digits
			count = 0;
			//if it is the end of the expression, means only one digit operand
			if (position == infixExpr.length() - 1)
			{
				temp_char = infixExpr[position];
				temp = temp_char - '0';  //convert char number into int number for calculation
			}
			else  //if it is not, it probably have multiple digits 
			{
				for (i = position; i < (infixExpr.length()); i++) //to find out the behind stuff is number or something else
				{
					temp_char = infixExpr[i];
					if (i == infixExpr.length() - 1)
					{
						temp = temp_char - '0';  
					}
					if (!isdigit(temp_char)) //if the behind stuff is not a number
					{
						if (temp_char == ' ')  //if it is a space, it can return you error 3 when it is followed by another number
						{
							is_space = true;
							count++;
							continue;
						}
						else  //if it is an operator we can pack up all operand numbers before into string 'digit_string' and stream into temp
						{
							stringstream dig(digit_string); //stream the value from digit_string to temp;
							dig >> temp;
							digit_string = " "; //clear digit_string;
							break;
						}
					}
					if ((is_space == true) && (isdigit(temp_char))) // if there is a space between two number
					{
						Errorhandling(3, i); //handling error 3;
						std::system("pause");
					}
					count++;
					digit_string.push_back(temp_char);
					

				}
				position += (count - 1); //the position will change by the length of the operand
			}
			
			
			valStack.push(temp);
			std::cout << "Pushed into valStack: " << temp << endl;
		}
		//Note* achar_1 won't be digit below
		//if achar_1 is an operator, "achar_1 + achar_2" might be an operator but not necessarily
		else
		{
			//space case
			if (achar_1 == ' ')
			{
				continue;
			}
			// illustrate all one-size length operator situations
			if (achar_1 == '+' || achar_1 == '=' || achar_1 == '-' || achar_1 == '*' || achar_1 == '/' || achar_1 == '!' || achar_1 == '^' || achar_1 == '%' || achar_1 == '>' || achar_1 == '<' || achar_1 == '(' || achar_1 == ')')
			{
				str.push_back(achar_1);
			}
			//special cases for two_sizes operators
			if (position != infixExpr.length() - 1)
			{
				achar_2 = infixExpr[position + 1]; //take second char;
				if (!(isdigit(achar_2))) {
					if (achar_1 == achar_2 && achar_1 == '+')
					{
						str = "++";// operator ++
						position++;
					}
					else if (achar_1 == achar_2 && achar_1 == '-')
					{
						str = "--"; //operator --
						position++;
					}
					else if (achar_1 == '>' && achar_2 == '=')
					{
						str = ">="; //operator >=
						position++;
					}
					else if (achar_1 == '<' && achar_2 == '=')
					{
						str = "<="; //operator <=
						position++;
					}
					else if (achar_1 == '!' && achar_2 == '=')
					{
						str = "!="; //operator !=
						position++;
					}
					else if (achar_1 == achar_2 && achar_1 == '&')
					{
						str = "&&"; //operator &&
						position++;
					}
					else if (achar_1 == achar_2 && achar_1 == '|')
					{
						str = "||"; //operator ||
						position++;
					}
					else if (achar_1 == achar_2 && achar_1 == '=')
					{
						str = "=="; //operator ||
						position++;
					}
				}
				
			}

			//considering parenthesis is a special case
			
			if (str == "(")
			{
				opStack.push(str);
				std::cout << "Pushed into opStack: " << str << endl; //*highest precedence for "(" 
			}

			else if (str == ")") 
			{
				////when comes to a ")", if the opstack is empty means it start with ")";
				if (opStack.empty()) //error 1 handling
				{
					Errorhandling(0, position);
					is_error = true;
				}
				else
				{
					//if there is no a "(" in the opstack it will also return you an error 1
					while ((!opStack.empty()) && (opStack.top() != "(")) //error 1 handling
					{
						Execute();
						if (opStack.empty())
						{
							Errorhandling(0, position);
							is_error = true;
							system("Pause");
						}
						opStack.pop();
					}
				}
				
			}

			else if(str != "")
			{
				if (str == "+" || str == "==" || str == "*" || str == "/" || str == "^" || str == "%" || str == ">" || str == "<") //error 1 handling, the thing is if "-" was taken as the first token, it would be consider as a negative "-"
				{
					if (valStack.empty())
					{
						Errorhandling(1, position);
						std::system("Pause");
					}
				}
				else if ((str == "++") || (str == "--") || (str == "!")) //Error 5 handling
				{
					for (i = position + 1; i < infixExpr.length(); i++)
					{
						temp_char = infixExpr[i];
						if (temp_char == ' ')
							continue;
						else if (isdigit(temp_char))
							break;
						temp_string.push_back(temp_char);
						if (temp_string == "+" || temp_string == "==" || temp_string == "*" || temp_string == "/" || temp_string == "^" || temp_string == "%" || temp_string == ">" || temp_string == "<")
						{
							Errorhandling(4, i);
							std::system("Pause");
						}

					}
					temp_string = ""; //clear the temp_string;
				}
				//push the operator into the opStack;
				Determination(str);
			}

			str = "";
			
		}

		if (is_error == true)
			std::system("Pause");
		
		
		
	} //end for
	

	//after plugging in all these operands and operators, do the computation using Execute();
	while (!opStack.empty())
	{
		Execute();

	}
	result = valStack.top();
	std::cout << "The final result for the expression is: " << result << endl;
	std::cout << "\n\n" << "********************************" << endl;
}

void Evaluator::Determination(string str)
{
	if (opStack.empty())
	{
		opStack.push(str);
		std::cout << "Pushed into opStack: " << str << endl;
	}

	else if (Precedence(str)>Precedence(opStack.top())) //if the operator has higher precedence than the top of the stack, plug it in;
	{
		opStack.push(str);
		std::cout << "Pushed into opStack: " << str << endl;
	}

	else
	{
		while (!opStack.empty() && (Precedence(str) <= Precedence(opStack.top()))) //if the operator has lower precedence than the top of the stack, computer the one in the stack first;
		{
			Execute(); //
			if (opStack.empty())
				break;
		}
		opStack.push(str);
		std::cout << "Pushed into opStack: " << str << endl;
	}
}

void Evaluator::Execute()
{
	string op=""; //operator
	string first = ""; //first operand
	string second = ""; //second operand
	int result; // one-time result

	op = opStack.top(); 
	opStack.pop();
	
	
	int operand2; 
	operand2 = valStack.top();

	valStack.pop();


	
	if ((op == "!") || (op == "++") || (op == "--")) //unary operator
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

	else    //binary operator
	{
		if (valStack.empty()) //error 2 handling
		{
			Errorhandling(2, position - 1);
			std::system("Pause");
		}

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

		}

		else if (op == "/")//Error 5 handling
		{
			if (operand2 == 0)
			{
				char tem_char;
				int error_posit = 0;
				for (int j = position; j >= 0; j--)
				{
					tem_char = Expression[j];
					if (tem_char == '/')
					{
						error_posit = j;
						break;
					}

				}
				Errorhandling(5, error_posit);//Error 5 handling, note:at that moment error_posit is the position of '/' operator;
				std::system("Pause");
			}

			result = operand1 / operand2;
			valStack.push(result);

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


//show the error message including the error char position;
void Evaluator::Errorhandling(int type, int position)
{
	switch (type)
	{
	case(0):
		std::cout << "Expression can not start with a closing parenthesis @ char: " << position << endl;
		break;
	case(1):
		std::cout << "Expression can not start with a binary operator @ char: " << position << endl;
		break;
	case(2):
		std::cout << "Two binary operators in a row @ char: " << position << endl;
		break;
	case(3):
		std::cout << "Two operands in a row @ char: " << position << endl;
		break;
	case(4):
		std::cout << "A unary operand can not be followed by a binary operator @ char: " << position << endl;
		break;
	case(5):
		std::cout << "Division by zero @ char: " << position << endl;
		break;
	default:
		break;
	}
}
