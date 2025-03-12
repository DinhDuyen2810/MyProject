#ifndef CALRESULT_H
#define CALRESULT_H

#include <stack>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class calresult
{
public:
    calresult();
    double result(double a, double b, char c);
    string postfixToValue(vector<string> s);
    int checkVar(char s);
    vector<string> infixToPostfix(string s);
    string theResult(string s);
};

#endif // CALRESULT_H
