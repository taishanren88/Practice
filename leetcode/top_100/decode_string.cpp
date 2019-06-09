 #include <iostream>
#include <stack>
#include <string>
#include <cassert>

using namespace std;
 string decodeString(string s) {
 	if (s.empty()) return "";
        // If we hit a number, and therefore a '[' , it means we are considering a new string
        // 1. If we encounter number, which results in an adjacent '[', add a new string to a stack
        // 2. IF we counter a ']' , calculate the resulting string on stack top, and append it to the stack
        // 3. If we encounter a character, append to the existing string on stack top
        stack<int> numbers;
        stack<string> strings;
        for (int i = 0; i < s.size(); i++)
        {
            string digit = "";
            if (isdigit(s[i]))
            {
                while (isdigit(s[i]))
                {
                    digit += s[i];
                    i++;
                }
                numbers.push(atoi(digit.c_str()));
                strings.push("");
             }
            else if (s[i] == ']')
            {
                auto number = numbers.top();
                numbers.pop();
                string result;
                for (int i = 0; i < number; i++)
                {
                    result += strings.top();
                }
                strings.pop();
                if (strings.empty())
                	strings.push(result);
                else
                	strings.top() += result;
            }
            else 
            {
            	if (strings.empty())
            		strings.push("");

                strings.top() += s[i];
            }
        }
        return strings.top();
    }

  int main() {
  	assert(decodeString("3[a]2[bc]") == "aaabcbc");
  	assert(decodeString("3[a2[c]]") == "accaccacc");
  	assert(decodeString("2[abc]3[cd]ef") == "abcabccdcdcdef");
  	assert(decodeString("") == "");
  }