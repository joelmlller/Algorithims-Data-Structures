/*
 * Name: Joel Miller
 * Date Submitted: 01/31/2023
 * Lab Section:
 * Assignment Name:
 */

#include <string>
#include <stack>
#include <iostream>
using namespace std;


// special function returns priority of operator symbol
int special(char unique)
{
    // multiplication, division and modulo have higher priority than other operators
    if (unique == '*' || unique == '/' || unique == '%')
        return 2;
    // addition and subtraction have lower priority than other operators
    else if (unique == '+' || unique == '-')
        return 1;
    // any other symbol is not an operator
    else
        return -1;
}

// isInfix function checks if the expression is in valid infix form
bool isInfix(string infix[], int length)
{
    // stack to store parentheses in infix expression
    stack<string> stackString;
    string specChar;

    // loop through the expression
    for (int i = 0; i < length; i++) {
        // push open parenthesis onto the stack
        if (infix[i][0] == '(') {
            stackString.push(infix[i]);
            continue;
        }   

        // if closed parenthesis encountered, pop open parenthesis from the stack
        switch (infix[i][0]) {
        case ')':
            if (stackString.empty())
            {
                // return false if closed parenthesis without open parenthesis
                return false;
            }
            specChar = stackString.top();
            stackString.pop(); 
            break;
        default:
            break;
        }
    }
    // return true if stack is empty (balanced parentheses)
    return (stackString.empty()); 
}

// infixToPostfix function converts infix expression to postfix expression
int infixToPostfix(string infix[], int length, string postfix[])
{
    int startIndex = 0;
    // check if infix expression is in valid form
    if (!isInfix(infix,length))
        return 0;

    // stack to store operators in infix expression
    stack<string> stackString;
    stackString.push("P"); // push dummy value onto the stack

    // loop through the expression
    for (int i = 0; i < length; i++)
    {
        // if current element is a digit, add it to the postfix expression
        if(isdigit(infix[i][0]))
            postfix[startIndex++] = infix[i];

        // if current element is open parenthesis, push it onto the stack
        else if (infix[i][0] == '(')
            stackString.push(infix[i]);

        // if current element is closed parenthesis
        else if (infix[i][0] == ')')
		{
			while (stackString.top()[0] != 'P' && stackString.top()[0] != '(')
			{
				string  c = stackString.top();
				stackString.pop();
				postfix[startIndex++] = c;
			}
			if (stackString.top()[0] == '(')
			{
				stackString.pop();
			}
		} 
		else {
			while (stackString.top()[0] != 'P' && special(infix[i][0]) <= special(stackString.top()[0]))
			{
				string chared = stackString.top();
				stackString.pop();
				postfix[startIndex++] = chared;
			}
			stackString.push(infix[i]);
		}

	}
	while (stackString.top()[0] != 'P')
	{
		string chared = stackString.top();

		stackString.pop();
		postfix[startIndex++] = chared;
	}

	return startIndex;
}
