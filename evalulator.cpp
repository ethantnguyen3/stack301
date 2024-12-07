//
// Created by ethan on 12/1/2024.
//

#include "evalulator.h"


#include <cctype>
#include <cmath>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

using namespace std;

Eval::Eval() = default;
Eval::~Eval() = default;
// Function to determine the priority of operators
int Eval::priority(const string &op) {
    if (op == "||") return 1;
    if (op == "&&") return 2;
    if (op == "==" || op == "!=") return 3;
    if (op == "<" || op == "<=" || op == ">" || op == ">=") return 4;
    if (op == "+" || op == "-") return 5;
    if (op == "*" || op == "/" || op == "%") return 6;
    if (op == "^") return 7;
    if (op == "-" || op == "!" || op == "++" || op == "--") return 8;
    return -1;
}

// Function to check for binary operators
bool Eval::isBinaryOperator(const string &op) {
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "%" || op == "^";
}

// Function to check for unary operators
bool Eval::isUnaryOperator(const string &op) {
    return op == "-" || op == "--" || op == "++";
}

// Function to check for comparison operators
bool Eval::isCompareOperator(const string &op) {
    return op == "||" || op == "&&" || op == "==" || op == "!=" || op == "<" ||
           op == "<=" || op == ">" || op == ">=";
}
bool Eval::isNotOperand(const string &op) {
  return op == "!";
}
double Eval::notOperation(const string &op, double a) {
    if (op == "!") return !static_cast<bool>(a);
    throw out_of_range("operation not supported");
}
// Convert infix to postfix
string Eval::infixToPostfix(const string &infix) {
    stack<string> operators;
    string postfix;

    for (char c : infix) {
        if (isspace(c)) continue;

        if (isalnum(c)) {
            postfix.append(1,c);
        } else if (c == '(') {
            operators.push(to_string(c));
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != "(") {
                postfix += operators.top();
                operators.pop();
            }
            if (!operators.empty()) operators.pop();
        } else {
            string op(1, c);
            while (!operators.empty() && Eval::priority(operators.top()) >= Eval::priority(op)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(op);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

// Perform unary operations
double Eval::performUnaryOperation(double a, const string &op) {
    if (op == "++") return a + 1;
    if (op == "--") return a - 1;
    if (op == "-") return -a;

    throw invalid_argument("Invalid unary operator");
}

// Perform binary operations
double Eval::performBinaryOperation(double a, double b, const string &op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw invalid_argument("Division by zero");
        return a / b;
    }
    if (op == "%") return fmod(a, b);
    if (op == "^") return pow(a, b);
    throw invalid_argument("Invalid binary operator");
}

// Perform comparisons
double Eval::compare(const string &op, double a, double b) {
    if (op == "&&") return static_cast<bool>(a) && static_cast<bool>(b);
    if (op == "||") return static_cast<bool>(a) || static_cast<bool>(b);
    if (op == "==") return a == b;
    if (op == "!=") return a != b;
    if (op == ">") return a > b;
    if (op == ">=") return a >= b;
    if (op == "<") return a < b;
    if (op == "<=") return a <= b;

    throw invalid_argument("Invalid comparison operator");
}
/*
// Evaluate postfix expression
int Eval::evaluate(const string &postfix) {
    stack<double> operands;

    for (size_t i = 0; i < postfix.size(); ++i) {
        char c = postfix[i];

        if (isdigit(c)) {
            double num = 0;
            while (i < postfix.size() && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                //++i;
            }
            //--i; // Adjust index after loop
            operands.push(num);
        } else {
            string op(1, c);
            if (Eval::isUnaryOperator(op)) {
                if (operands.empty()) throw invalid_argument("Invalid postfix expression");
                double a = operands.top();
                operands.pop();
                operands.push(Eval::performUnaryOperation(a, op));
            } else if (Eval::isBinaryOperator(op)) {
                if (operands.size() < 2) throw invalid_argument("Invalid postfix expression");
                double b = operands.top();
                operands.pop();
                double a = operands.top();
                operands.pop();
                operands.push(Eval::performBinaryOperation(a, b, op));
            } else {
                throw invalid_argument("Invalid character in postfix expression");
            }
        }
    }

    if (operands.size() != 1) throw invalid_argument("Invalid postfix expression");
    return operands.top();
} */
double Eval::evaluate(const string &infix) {
  //int answer;
  const string postfix = infixToPostfix(infix);
  stack<double> operands;
  //stack<bool> equations;
    cout << "testing" << endl;
  for (size_t i = 0; i < postfix.size(); ++i) {
    char c = postfix[i];
    if (isdigit(c)) {
      int num = 0;
      if (i < postfix.size() && isdigit(postfix[i])) {
        num = num * 10 + (postfix[i] - '0');
        }
        operands.push(num);

    }

    else {
        string op;

        // Check for multi-character operators
        if (i + 1 < postfix.size() &&
            (postfix.substr(i, 2) == "++" || postfix.substr(i, 2) == "--" ||
             postfix.substr(i, 2) == ">=" || postfix.substr(i, 2) == "<=" ||
             postfix.substr(i, 2) == "==" || postfix.substr(i, 2) == "!=")) {
            op = postfix.substr(i, 2); // Multi-character operator
            i++; // Skip the second character of the operator
             } else {
                 op = string(1, c); // Single-character operator
             }
      if (Eval::isNotOperand(op)) {
        if (operands.empty()) throw invalid_argument("Invalid postfix expression");
        double a = operands.top();
        operands.pop();
        operands.push(Eval::notOperation(op, a));

      }
      else if (Eval::isUnaryOperator(op)) {
        if (operands.empty()) throw invalid_argument("Invalid postfix expression");
        double a = operands.top();
        operands.pop();
        operands.push(Eval::performUnaryOperation(a, op));

} else if (Eval::isBinaryOperator(op)) {
  if (operands.size() < 2) throw invalid_argument("Invalid postfix expression");
  double b = operands.top();
  operands.pop();
  double a = operands.top();
  operands.pop();
  operands.push(Eval::performBinaryOperation(a, b, op));

} else if (Eval::isCompareOperator(op)) {
  if (operands.empty()) throw invalid_argument("Invalid postfix expression");
    double b = operands.top();
    operands.pop();
    double a = operands.top();
    operands.pop();
    operands.push(Eval::compare(op, a, b));
}else {
  throw invalid_argument("Invalid character in postfix expression");

}
        cout << "testing" << endl;
}
}
if (operands.size() != 1) throw invalid_argument("Invalid postfix expression");
    cout << "testing" << endl;
return operands.top();

}
