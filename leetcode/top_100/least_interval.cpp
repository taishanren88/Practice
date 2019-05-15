#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/*
Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks. Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

 

Example:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.

*/
 int leastInterval(vector<char>& tasks, int n) {
 	// Build a count of each task 
 	// We want to run tasks that are most frequent first.
 	// 1. If they are most frequent, we can parallelize as mcuch as possible and reduce future cooldown
 	// 2. We don't care what we execute specifically, so we just use a maxheap to track our tasks
 	// and execute them one by one from maxheap
 	// 3. MaxHeaps has the count of each remaining task
 	// If they still exist, consider them for the next "n" round
       
    	unordered_map<char, int> mapping;
    	for (char c : tasks)
    	{
    		if (mapping.find(c) == mapping.end())
    			mapping[c] = 1;
    		else
    			mapping[c]++; 
    	}

    	priority_queue<int> maxHeap;
    	for (auto kv : mapping)
    		maxHeap.push(kv.second);

    	int count = 0;
    	while (!maxHeap.empty())
    	{
    		vector<int> temp {maxHeap.top()};
    		maxHeap.pop();

    		auto maxHeapSize = maxHeap.size();
    		for (int i = 0; i < std::min(n, (int) maxHeapSize); i++)
    		{
    			temp.push_back(maxHeap.top());
    			maxHeap.pop();
    		}

    		for (auto val : temp)
    		{
    			val--;
    			if (val > 0) {
    				maxHeap.push(val);
    			}
    		}
    	    count += maxHeap.empty() ? temp.size() : n + 1;
    	    cout << count << endl;
    	}
        return count;
    }

int main()
{
	vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
	// cout << leastInterval(tasks, 2) << endl;
	tasks = {'A','B','C','D','E','A','B','C','D','E'};
	cout << leastInterval(tasks, 4) << endl;
}

