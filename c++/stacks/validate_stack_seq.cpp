#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
using namespace std;

bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        
        stack<int> newpushstack;
        int popIndex = 0;
        int pushIndex = 0;
        while (popIndex < popped.size())
        {
            cout << "Push " << pushIndex << "Pop " << popIndex <<endl;

            if (newpushstack.empty())
                cout << "empty" <<endl ;
            // while pushed stack is not at the front of the popped stack yet, keep pushing
            while (pushIndex < pushed.size() && (newpushstack.empty() || newpushstack.top() != popped[popIndex])) 
            {
                cout << "here" <<endl;
                newpushstack.push(pushed[pushIndex]);
                pushIndex++;
                cout << " empty " << newpushstack.empty() << (newpushstack.top() != popped[popIndex]) <<endl;
            }
            cout << "here2" <<endl;
            // pop everything that is equal to the top of the new push stack
            while (popIndex < popped.size() && (!newpushstack.empty() && newpushstack.top() == popped[popIndex]))
            {
                newpushstack.pop();
                popIndex++;
            }
            cout << "Push " << pushIndex << "Pop " << popIndex <<endl;
            // if we pushed everything, but haven't popped this is an error
            if (pushIndex == pushed.size() && popIndex < popped.size())
                return false;
        }
        return true;
    }

int main()
{
    vector <int>v = {1,0};
    vector <int>v2 = {1,0};
    assert(validateStackSequences(v, v2));
}