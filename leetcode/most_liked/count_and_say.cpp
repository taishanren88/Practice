#include <iostream>
#include <unordered_map>
#include <string>
#include <cassert>
using namespace std;

 string countAndSay(int n) {
     // For the ith term, take the i-1th term and say it out loud
     // When you say it loud, map it to it's actual value
    // previous term -> out loud -> mapped
     // "1" -> one one" -> 11
     // "2" -> one two -> 12
     // "11" -> two one -> 21

    string previous = "1";
    for (int i = 2; i <= n; i++)
    {
        string result = "";
        int j = 0;
        while(j < previous.size())
        {
            char current = previous[j];
            // count number of same characters
            int count = 0;
            while (j < previous.size()
                && previous[j] == current)
            {
                count++;
                j++;
            }
            result += std::to_string(count) + current;
        }
         previous = result;
    }
    return previous;

    }
int main() {
   assert(countAndSay(1) == "1");
    assert( countAndSay(2) == "11");
    assert( countAndSay(3) == "21");
    assert( countAndSay(4) == "1211");
    assert(countAndSay(5) == "111221");
    assert(countAndSay(6) == "312211");

}