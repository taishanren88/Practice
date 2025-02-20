
#include <iostream>
using namespace std;

/*
## Add big numbers
Given two positive numbers (without fraction) defined by string n1, n2, return their
sum in string.

e.g.
```
sum("321", "765") => "1086"
sum("000", "10") => "10"
```

We can safely assume all strings consist of '0'~'9' only. 
*/

string addTwoNumbers(string a, string b) {
  // Iterate over each digit of a and b. add the digits together . then keep track of the decimal place
  // also keep track of carry with current decimal place 
  // at the end we just longer string that's remaining and add those decimal places together 

  int i =  a.size() - 1;
  int j = b.size()-1;

 bool carry = false;
 string result ;
 // sum("321", "765") => "1086"
//  sum("000", "10") => "10"
 // sum("99", "4") => "103"
  // sum("99", "4") => "103"
  while (i >= 0 && j >= 0) {
    auto digit_a = a[i] - '0';
    auto digit_b = b[i] - '0';
    auto sum = digit_a + digit_b ;
    result =   static_cast<char>((carry ? (sum % 10) + 1 : sum ))+ result;
    if (sum > 10 ) {
      carry = true;
    } else {
      carry = false;
    }
    i--;
    j--;
  }

// one of these should still remain
  while (i >= 0 ) {
    auto curr_val =(a[i] - '0');
    result =   static_cast<char>((carry ? 0 : curr_val ))+ result;
    i--;
  }

  // repeat same for b
    while (j >= 0 ) {
      auto curr_val =(a[i] - '0');
     result =   static_cast<char>((carry ? 0 : curr_val ))+ result;
      j--;
  }
  if (carry) {
     result = '1' + result;
  }

  // remove the trailing zeroes
   int k = 0;
   while (k < result.size() && result[k] == '0') {
    k++;
   }
  return result.substr(k);
}
