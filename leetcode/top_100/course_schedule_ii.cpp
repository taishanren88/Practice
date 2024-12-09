#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    // Generate a mapping demonstrating what are the prerequisite courses and dependencies A -> [x,y], x,y depends on A
    // Generate a mapping counting the number of prequisite A -> n => A has 'n' prequisites before it can be taken
    // Do a BFS using a queue where you traverse all of the courses with 0 dependencies
    // If you traverse one, remove the courses that require it has a pre-requisite (decrement the count). If count == 0 , add back to queue

    // Generate the graph
    using CourseList = vector<int>;
    unordered_map<int, CourseList> graph;
    unordered_map<int, int> incoming;

    // Initialize
    for (int i = 0; i < numCourses; i++) {
    	graph[i] = CourseList();
    	incoming[i] = 0;
    }

    for (auto & p : prerequisites) {
    	auto course = p[0];
    	auto prerequisite = p[1];
    	graph[prerequisite].push_back(course);
    	incoming[course]++;
    }


    // Initialize the queue
    queue<int> todo;
    for (auto& course : incoming) {
    	if (course.second == 0) {
    		todo.push(course.first);
    		cout << "inserting" << course.second<< endl;
    	}
    }

    vector<int> ordering;
    // process
    while (!todo.empty()) {
    	auto current = todo.front();
    	todo.pop();

    	ordering.push_back(current);
    	// for those courses that depend on this course, decrement by count as this course has been taken
    	for (auto& subsequent : graph[current]) {
    		incoming[subsequent]--;
    		if (incoming[subsequent] == 0) {
    			todo.push(subsequent);
    		}
    	}
    }
    if (ordering.size() ==numCourses) {
    	return ordering;
    } else {
    	return vector<int>();
    }
}

int main() {
	vector<vector<int> > prerequisites = {{1,0}};
	auto result = findOrder(2, prerequisites);
	for (auto r : result ) {
		cout << r << ",";
	}

	cout << endl;
    prerequisites = {{1,0}, {2,0}, {3,1}, {3,2}};
	result = findOrder(4, prerequisites);
	for (auto r : result ) {
		cout << r << ",";
	}
	cout << endl;

	prerequisites = {};
	result = findOrder(1, prerequisites);
	for (auto r : result ) {
		cout << r << ",";
	}
}