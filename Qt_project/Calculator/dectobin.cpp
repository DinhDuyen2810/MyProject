#include "dectobin.h"

dectobin::dectobin() {}

string dectobin::decimalToBinary(int n) {
    if (n == 0) {
        return "0";
    }

    string binary = "";
    while (n > 0) {
        binary = to_string(n % 2) + binary;
        n /= 2;
    }
    return binary;
}
