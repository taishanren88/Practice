#include <iostream>
#include <cassert>
using namespace std;

 int myAtoi(string str) {
    // eliminate leading whitespace
    // find end of number or end  of string
    // and consider -
    // compare bounds
    int index = 0;
    while (str[index] == ' ')
        index++;
    if (index == str.size()
            || !(str[index] ==  '-' 
                 || str[index] == '+'
                || (str[index] >= '0' && str[index] <= '9')))
        return 0;
    bool isNeg = false;
    if (str[index] == '-' || str[index] == '+') {
        isNeg = str[index] == '-';
        index++;
    }

    int end = index;
    while (str[end] >= '0' && str[end] <= '9')
        end++;
    auto numAsStr = str.substr(index, end - index);
    long value = 0;
    const long posMaximum = static_cast<long>(INT_MAX);
    const long negMaximum = posMaximum + 1;

    for ( char c : numAsStr) {
        value = value * 10 + (c - '0');
        if (isNeg && (value > negMaximum)) {
            return INT_MIN;
        }
        else if (!isNeg && value > posMaximum) {
            return INT_MAX;
        }
    }
    return isNeg ? value * -1 : value ;
}


int main() {
    assert(myAtoi("42") == 42);
    assert(myAtoi("     -42") == -42);
    assert(myAtoi("4193 with words") == 4193);
    assert(myAtoi("words and 987") == 0);
    assert(myAtoi("-9128347233") == INT_MIN);
    assert(myAtoi("9128347233") == INT_MAX);
    assert(myAtoi("2147483647") == INT_MAX);
    assert(myAtoi("-2147483648") == INT_MIN);

}

