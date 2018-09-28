#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

class Evaluator
{
public:
	void Determination(string str);
	void Process(string infixExpr);
	void Execute();
	int Precedence(string oper);
	void Errorhandling(int type, int position);
private:
	stack <int> valStack;  //stack for operand
	stack <string> opStack; //stack for operator
	bool is_error;  //error handling
	int position;   //tracing the position of the expression in the for loop
	string Expression;  //store the infix expression
};

#endif // EVALUATOR_H
#pragma once
