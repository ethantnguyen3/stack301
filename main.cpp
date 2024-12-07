#include <iostream>
#include "evalulator.h"
#include <string>


//
// Created by ethan on 12/1/2024.
//
int main() {

    Eval e;
    cout << "Hello World!" << endl;
    const string x = e.infixToPostfix("3+2");
    cout << x << endl;
    const double y = e.compare(">",2,3);
    cout << y << endl;
    const double result = e.evaluate("++3+2");
    cout << result;
    cout << "done." << endl;
    return 0;
}
