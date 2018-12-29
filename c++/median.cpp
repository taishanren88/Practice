/*Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.
For example,
[2,3,4], the median is 3
[2,3], the median is (2 + 3) / 2 = 2.5
Design a data structure that supports the following two operations:
* void addNum(int num) - Add a integer number from the data stream to the data structure.
* double findMedian() - Return the median of all elements so far.
 
Example:
addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3) 
findMedian() -> 2

   
*/

#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <cassert>

 // initialize your data structure here. 
// Have two queues, minHeap (second larger half, everything greater than this), max heap (first larger half)
// try to push in first half, otherwis epush in seocnd half, 
// rebalance to make sure that first half always has precedent
class MedianFinder
{
public:
    MedianFinder() {
        
    }
    
     void addNum(int num) {
        if (firstHalf.empty() || num <= firstHalf.top())
            firstHalf.push(num);
        else // second half is empty or the element is greater than first half
            secondHalf.push(num);
        balance();
    }
    

    
    double findMedian() {
        if (firstHalf.empty() && secondHalf.empty())
            return 0.0f;
        if (firstHalf.size() > secondHalf.size())
            return firstHalf.top();
        else
            return ( firstHalf.top() + secondHalf.top() ) / 2.0f;
    }

private:
    void balance()
    {
        if (firstHalf.size() > (secondHalf.size() +1))
        {
            auto top = firstHalf.top();
            firstHalf.pop();
            secondHalf.push(top);
        }
        else if (secondHalf.size() > firstHalf.size())
        {
            auto top = secondHalf.top();
            secondHalf.pop();
            firstHalf.push(top);
        }
        
    }

    std::priority_queue<int, std::vector<int>, std::less<int>> firstHalf; // maxHeap
    std::priority_queue<int, std::vector<int>, std::greater<int>> secondHalf; // minHeap


};

int main()
{
    MedianFinder median;
    median.addNum(1);
    assert(median.findMedian() == 1);
    median.addNum(2);
    assert(median.findMedian() == 1.5f);
    median.addNum(3);
     std::cout << median.findMedian() << std::endl;
   assert(median.findMedian() == 2.0f);
}
