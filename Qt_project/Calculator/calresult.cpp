#include "calresult.h"

calresult::calresult() {}

// tính  a "phép tính c" b
double calresult::result(double a, double b, char c){
    switch (c){
        case '+' : return a + b;
        case '-' : return a - b;
        case '*' : return a * b;
        case '/' : return a / b;
        default: return pow(a, b);
    }
}

// Tính toán kq từ hậu tố
string calresult::postfixToValue(vector<string> s){
    stack<double> stack;
    for (int i = 0; i < static_cast<int>(s.size()); i++){
        if(!isdigit(s[i][0]) && s[i][0] != '(' && s[i][0] != ')' && s[i][0] != '+' && s[i][0] != '-'
            && s[i][0] != '*' && s[i][0] != '/' && s[i][0] != '^'){
            return "ERR";
        }
        if(isdigit(s[i][0])){
            stack.push(stod(s[i]));
        } else {
            if(stack.empty()){
                return "ERR";
            }
            double b = stack.top();
            stack.pop();
            if(stack.empty()){
                return "ERR";
            }
            double a = stack.top();
            stack.pop();
            if(b == 0 && s[i][0] == '/'){
                return "ERR";
            }
            stack.push(result(a, b, s[i][0]));
        }
    }
    double value = stack.top();
    stack.pop();
    return to_string(value);
}

// xét độ uu tiên toán tử
int calresult::checkVar(char s){
    switch (s) {
        case '+' : case '-' : return 4;
        case '*' : case '/' : return 5;
        case '^' : return 6;
    }
    return 1;
}

//Chuyển trung tố thành hậu tố
vector<string> calresult::infixToPostfix(string s)
{
    vector<string> arr;
    int n = s.length(), j = 0;
    stack<char> stack;
    while(j != n){
        char a = s[j];
        if(isdigit(a)){
            int sum = a - '0';
            a = s[j + 1];
            while(isdigit(a)){
                sum = sum * 10 + (a - '0');
                j++;
                a = s[j + 1];
            }
            arr.push_back(to_string(sum));
            j++;
        } else if(stack.empty() || a == '('){
            stack.push(a);
            j++;
        } else if(a == ')') {
            do{
                if(a != '('){
                    arr.push_back(string(1, stack.top()));
                    stack.pop();
                }
            } while (stack.top() != '(');
            j++;
            stack.pop();
        } else {
            while(!stack.empty() && checkVar(stack.top()) >= checkVar(a)){
                if(a == '^'){
                    break;
                }
                arr.push_back(string(1, stack.top()));
                stack.pop();
            }
            stack.push(a);
            j++;
        }
        if(j == n){
            while(!stack.empty()){
                arr.push_back(string(1, stack.top()));
                stack.pop();
            }
        }
    }
    return arr;
}

//tính kết quả
string calresult::theResult(string s)
{
    vector<string> pf = infixToPostfix(s);
    return postfixToValue(pf);
}
