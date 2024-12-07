//
// Created by ethan on 12/1/2024.
//
#pragma once


#include <string>

using namespace std;
class Eval {
public:
    Eval();
    ~Eval();
    // Function to determine the priority of operators
    static int priority(const string &op);

    // Function to check for binary operators
    static bool isBinaryOperator(const string &op);

    // Function to check for unary operators
    static bool isUnaryOperator(const string &op);

    // Function to check for comparison operators
    static bool isCompareOperator(const string &op);

    // Function to check for NOT operand
    static bool isNotOperand(const string &op);

    // Function to perform NOT operation
    static double notOperation(const string &op, double a);

    // Convert infix to postfix
    static string infixToPostfix(const string &infix);

    // Perform unary operations
    static double performUnaryOperation(double a, const string &op);

    // Perform binary operations
    static double performBinaryOperation(double a, double b, const string &op);

    // Perform comparisons
    static double compare(const string &op, double a, double b);

    // Evaluate postfix expression
    static double evaluate(const string &infix);

    // Evaluate comparison expressions
    //static bool comparison(const string &postfix);

private:
    //Eval() = default;
};


