/*
 * Name: Joel Miller
 * Date Submitted: 02/13/2023
 * Lab Section: 004
 * Assignment Name: Calculate Post Fix Expression
 */


#include <string>
#include <stack>

using namespace std;

//Calculates a postfix expression with integer operands using a stack
//The expression is represented using an array of strings
//Each string is either an operand or operator symbol
//Operator symbols:
//"+" addition
//"-" subtraction
//"*" multiplication
//"/" divison
//"%" remainder
//Example expression: "8", "5", "-" evaluates to a result of 3:
//1: push 8, 2: push 5,
//3: "-"-> pop top two values, earlier value is the left-side operand: 8 - 5
//The result of the operation (8-5) is 3, push 3 onto stack
//After evaluation of the expression, the final result should be
//the only value on the stack, return 0 if the stack is
//non-empty after popping the result
//Return 0 if expression is zero-length or if there are insufficient operands
//for an operation
//The STL Stack class can be used
//To easily convert a numeric string to an int you may use the stoi() function
//which takes a string as a parameter and returns a string
int calculatePostfixExpression(string expression[], int length)
{
    int num;
    int num2;
    stack<int> postFix;

    // check if length is 0
    if (length == 0) {
        return 0;
    }

    // loop through each element of expression
    for (int i = 0; i < length; i++) {
        // if expression[i] is "+"
        if (expression[i] == "+") {
            // check if there are at least 2 numbers in stack
            if (postFix.size() < 2) {
                return 0;
            }
            // pop top 2 numbers, add them, and push the result back to the stack
            num = postFix.top();
            postFix.pop();
            num2 = postFix.top();
            postFix.pop();
            postFix.push(num2 + num);
        }
        // if expression[i] is "-"
        else if (expression[i] == "-") {
            // check if there are at least 2 numbers in stack
            if (postFix.size() < 2) {
                return 0;
            }
            // pop top 2 numbers, subtract them, and push the result back to the stack
            num = postFix.top();
            postFix.pop();
            num2 = postFix.top();
            postFix.pop();
            postFix.push(num2 - num);
        }
        // if expression[i] is "*"
        else if (expression[i] == "*") {
            // check if there are at least 2 numbers in stack
            if (postFix.size() < 2) {
                return 0;
            }
            // pop top 2 numbers, multiply them, and push the result back to the stack
            num = postFix.top();
            postFix.pop();
            num2 = postFix.top();
            postFix.pop();
            postFix.push(num2 * num);
        }
        // if expression[i] is "/"
        else if (expression[i] == "/") {
            // check if there are at least 2 numbers in stack
            if (postFix.size() < 2) {
                return 0;
            }
            // pop top 2 numbers, divide them, and push the result back to the stack
            num = postFix.top();
            postFix.pop();
            num2 = postFix.top();
            postFix.pop();
            postFix.push(num2 / num);
        }
        // if expression[i] is "%"
        else if (expression[i] == "%") {
            // check if there are at least 2 numbers in stack
            if (postFix.size() < 2) {
                return 0;
            }
            // pop top 2 numbers, calculate the modulus, and push the result back to the stack
            num = postFix.top();
            postFix.pop();
            num2 = postFix.top();
            postFix.pop();
            postFix.push(num2 % num);
        }
        // if expression[i] is a number, push it to the stack
        else {
            postFix.push(stoi(expression[i]));
        }
    }

    // check if there is exactly 1 number in stack, which is the final result
    if (postFix.size() != 1) {
        return 0;
    }

    return postFix.top();
}
