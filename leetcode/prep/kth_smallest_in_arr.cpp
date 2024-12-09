#include <iostream>
#include <queue>
using namespace std;

struct Element{
	Element(int rr, int cc, int vv){
		row = rr;
		col = cc;
		val = vv;
	}
	int row;
	int col;
	int val;
};

int kthSmallest(vector<vector<int>>& matrix, int k) {
	// Make a minheap of the first element of each column
	// It's guaranteed that the top of the minheap is always the smallest element
	// We'll try to pop from it 'k' times
	// Each time pushing the element from the next row of the element we just popped
	if (matrix.empty()){ 
		return 0;
	}

	auto cmp =[](Element& a, Element& b) {
		return a.val > b.val;
	};

    std::priority_queue<Element, std::vector<Element>, decltype(cmp) > minHeap(cmp);
    for (int j = 0; j < matrix[0].size(); j++ ) {
    	Element ele(0, j, matrix[0][j]);
    	minHeap.push(ele);
    }
    int last = 0;
    int count = 0;
    while (!minHeap.empty()) {
    	auto currentMin = minHeap.top();
    	last = currentMin.val;
    	count++;
    	minHeap.pop();
    	if (count < k) {
    		if (currentMin.row + 1 < matrix.size()) {
    			Element next(currentMin.row + 1, currentMin.col, matrix[currentMin.row + 1][currentMin.col]);
    			minHeap.push(next);
    		}
    	} else {
    		break;
    	}
    }
    return last;
}

int main() {
vector <vector<int>> mat = {
   { 1,  5,  9},
   {10, 11, 13},
   {12, 13, 15}
};
cout << kthSmallest(mat, 8) << endl;

}