#include <iostream>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

using namespace std;

/*
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 */
class NestedInteger {
   public:
     // Return true if this NestedInteger holds a single integer, rather than a nested list.
     virtual bool isInteger() const {
        return m_nestedIntegerNodes.empty();
     }
 
      // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    virtual int getInteger() const {
        return m_integer;
    }
 
      // Return the nested list that this NestedInteger holds, if it holds a nested list
     // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const {
        return m_nestedIntegerNodes;
    }

    vector<NestedInteger> &getListModify()  {
        return m_nestedIntegerNodes;
    }
    vector<NestedInteger> m_nestedIntegerNodes;
        int m_integer;
  };


class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        // If we want to avoid dumping everything into a flattend list
        // We need a stack to be able to go back to adjacent items from level up
        // Need 'advance' method
        // Always guarantee that the top of the final stack is an integer
        // Maintain a stack of vector iterators containing what we haven't visite
        // While iteration , if we encounter a vector of integers, then add the chidl list to this stack
        // advance the top of the stack to the adjacent element
        // Stop once we encounter an integer
        toVisit.push(nestedList.begin());
        toVisitEnd.push(nestedList.end());
        advance();
    }
    
    void advance() {
        while (!toVisit.empty()) {
            if (toVisit.top() == toVisitEnd.top()) {
                toVisit.pop();
                toVisitEnd.pop();
            }
            else  {
                auto top = toVisit.top();
                if (top->isInteger()) {
                    return;
                }
                toVisit.top()++;
                toVisit.push(top->getList().begin());
                toVisitEnd.push(top->getList().end());
            }
        }
    }
    
    int next() {
        auto top = toVisit.top()->getInteger();
        toVisit.top()++;
        advance();
        return top;
    }
    
    bool hasNext() {
       return !toVisit.empty();
    }
    private:
    stack<std::vector<NestedInteger>::const_iterator> toVisit;
    stack<std::vector<NestedInteger>::const_iterator> toVisitEnd;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

int main() {
     /*
     Input: [[1,1],2,[1,1]]
        Output: [1,1,2,1,1]
     */
     {
             NestedInteger root;
         vector<NestedInteger> subList1;
         subList1.push_back(NestedInteger());
         subList1.push_back(NestedInteger());
         subList1[0].m_integer = 1;
         subList1[1].m_integer = 1;
          vector<NestedInteger>& rootList = root.getListModify();
          rootList.push_back(NestedInteger());
          rootList[0].getListModify() = subList1;
          rootList.push_back(NestedInteger());
          rootList[1].m_integer=2;
          rootList.push_back(NestedInteger());
          rootList[2].getListModify() = subList1;
          NestedIterator it (rootList);
          assert(it.hasNext() && it.next() == 1);
          assert(it.hasNext() && it.next() == 1);
          assert(it.hasNext() &&it.next() == 2);
          assert(it.hasNext() && it.next() == 1);
          assert(it.hasNext() && it.next() == 1);
          assert(!it.hasNext());
    }

        {
            NestedInteger root;
          vector<NestedInteger>& rootList = root.getListModify();
          rootList.push_back(NestedInteger());
           rootList.push_back(NestedInteger());
          rootList[0].m_integer=1;
          vector<NestedInteger> subList2;
          subList2.push_back(NestedInteger());
          subList2.push_back(NestedInteger());
          subList2[0].m_integer=4;
          vector<NestedInteger> subList3;
          subList3.push_back(NestedInteger());
          subList3[0].m_integer = 6;
          subList2[1].getListModify() = subList3;
          rootList[1].getListModify()= subList2;
          NestedIterator it (rootList);
          assert(it.hasNext() && it.next() == 1);
          assert(it.hasNext() &&it.next() == 4);
          assert(it.hasNext() && it.next() == 6);
          assert(!it.hasNext());
    }
}