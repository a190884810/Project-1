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

	void Process(string infixExpr);
	void Execute();

	void Display();
	void DisplayOp();
private:
	stack <int> valStack;
	stack <char> opStack;
};

#endif // EVALUATOR_H
#pragma once
