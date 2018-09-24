#pragma once
// this is the implementation file queue.cpp
// this is the implementation of the template class Stack
//the interface file for the template class queue is in the header file queue.h


#include "Evaluator.h"
#include <iostream>
#include <stdlib.h>
#include "stdafx.h"

using namespace std;


void Evaluator:: Process(string infixExpr)
{
	int result ;
	char achar;

	while (!opStack.empty())
	{
		opStack.pop();
	}

	while (!valStack.empty())
	{
		valStack.pop();
	}

	for(int i=0; i < infixExpr.length(); i++)
	{
	
		achar = infixExpr[i];

		if (isdigit(achar)) {

		valStack.push(achar);
		cout << "Pushed into valStack: " << achar << endl;
		}
		else
		{
			switch (achar)
			{

			case('('):
			{
				opStack.push(achar);
				cout << "Pushed into opStack: " << achar << endl;
				break;
			}

			case('*'):
			{
				if (opStack.empty())
				{
					opStack.push(achar);
					cout << "Pushed into opStack: " << achar << endl;
				}

				else if (achar > opStack.top())
				{
					opStack.push(achar);
					cout << "Pushed into opStack: " << achar << endl;
				}

				else
				{
					while (!opStack.empty() && achar <= opStack.top())
					{
						Execute();
						opStack.push(achar);
						cout << "Pushed into opStack: " << achar << endl;
					}
				}
				break;
			}//end if


			case('+'):
			{
				if (opStack.empty())
				{
					opStack.push(achar);
					cout << "Pushed into opStack: " << achar << endl;
				}

				else if (achar > opStack.top())
				{
					opStack.push(achar);
					cout << "Pushed into opStack: " << achar << endl;
				}

				else
				{
					while (!opStack.empty() && achar <= opStack.top())
					{
						Execute();
						opStack.push(achar);
						cout << "Pushed into opStack: " << achar << endl;
					}
				}
				break;
			}//end if

			case('-'):
			{
				if (opStack.empty())
				{
					opStack.push(achar);
					cout << "Pushed into opStack: " << achar << endl;
				}

				else if (achar > opStack.top())
				{
					opStack.push(achar);
					cout << "Pushed into opStack: " << achar << endl;
				}

				else
				{
					while (!opStack.empty() && achar <= opStack.top())
					{
						Execute();
						opStack.push(achar);
						cout << "Pushed into opStack: " << achar << endl;
					}
				}
				//end if
				break;
			}

			case('/'):
			{
				if (opStack.empty())
				{
					opStack.push(achar);
					cout << "Pushed into opStack: " << achar << endl;
				}

				else if (achar > opStack.top())
				{
					opStack.push(achar);
					cout << "Pushed into opStack: " << achar << endl;
				}

				else
				{
					while (!opStack.empty() && achar <= opStack.top())
					{
						Execute();
						opStack.push(achar);
						cout << "Pushed into opStack: " << achar << endl;
					}
				}

				break;
			}//end if

			case('^'):
			{
				if (opStack.empty())
				{
					opStack.push(achar);
					cout << "Pushed into opStack: " << achar << endl;
				}

				else if (achar > opStack.top())
				{
					opStack.push(achar);
					cout << "Pushed into opStack: " << achar << endl;
				}

				else
				{
					while (!opStack.empty() && achar <= opStack.top())
					{
						Execute();
						opStack.push(achar);
						cout << "Pushed into opStack: " << achar << endl;
					}
				}
				break;
			}//end if


			case(')'):
			{
				while (opStack.top() != '(')
				{
					Execute();
					opStack.pop();
					break;
				}
			}
			default:
				break;
			}//end switch
		}
		}//end for
 
	    while(!opStack.empty())
	    {
			Execute();
	    }   
		result = valStack.top();
		cout << "The final result for the expression is: "<< result << endl;
}//end of Process()


void Evaluator:: Execute ()
{          
	int operand2, operand1, result ;
	char op;
	string first, second;

	second = valStack.top();
	operand2 = std::stoi(second);
	valStack.pop();
	
	first = valStack.top();
	operand1 = std::stoi(first);
	valStack.pop();

	op = opStack.top();
	opStack.pop();
	
	switch(op)
	{
	case('^'):
	{
		result = operand1 ^ operand2 ;
		valStack.push(result);
		
		break;
	}
	
	case('*'):
	{
		result = operand1 * operand2 ;
		
		cout << "values " << operand1 << "  " << operand2 << endl;
		
		
		valStack.push(result);

		cout << "\n\n";
		cout << "Result for * op is: " << result <<endl;
		break;
	}
	
	case('/'):
	{
		if(operand2 == '0')
			cout <<"Division by zero error!";
		
		else
		{
			result = operand1 / operand2;
			valStack.push(result);
			break;
		}

	}
	
	case('+'):
	 {
		result = operand1 + operand2 ;
		cout << "Result:" << result << endl;
		 valStack.push(result);
		break;
	 }
 
	case('-'):
	{
		result = operand1 - operand2 ;
		 valStack.push(result);
		 break;
	}
 
	}//end switch

}


void Evaluator:: Display()
{
	while(!valStack.empty())
{
		cout <<valStack.top();
		valStack.pop();
	}
}
void Evaluator:: DisplayOp()
{
	while(!opStack.empty())
	{
		cout <<opStack.top();
		opStack.pop();
	}
}