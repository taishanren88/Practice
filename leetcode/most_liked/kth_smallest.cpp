#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

struct MatrixData {
    MatrixData(int ii , int jj, int aVal)
        : i(ii), j(jj), val(aVal) {

    }

    bool operator ==(const MatrixData& other) const {
        return i == other.i && j == other.j && val == other.val;
    }

    int i, j, val;
};

struct pair_hash {
    inline std::size_t operator()(const MatrixData & v) const {
        return v.i * 31 + v.j;
    }
};
/*
*/
int kthSmallest(vector<vector<int> >& matrix, int k) {

// Create a min heap where elements inside need to be explored
// At each iteration , pop off min element. If count == k , return this element
// Otherwise, check elements next row/ column (down/right) and put into heap if it's not there

    auto cmp = [] (MatrixData & a, MatrixData & b) {
        return a.val > b.val;
    };
    priority_queue<MatrixData, std::vector<MatrixData>, decltype(cmp)> minHeap(cmp);
    unordered_set<MatrixData, pair_hash> visited;

    int count = 0;

    const int N = matrix.size();
    auto validIndex =[N](int i , int j) {
        return i < N && j < N;
    };
    auto addElementToHeapIfUnvisited = [&](int i , int j) {
        if (validIndex(i, j)) {
            MatrixData data(i, j, matrix[i][j]);
            if (visited.find(data) == visited.end()) {
                minHeap.push(data);
                visited.insert(data);
                // printf("ADDING VAL :%d\n", data.val);
            }
        }
    };
    minHeap.push(MatrixData(0, 0, matrix[0][0]));
    int last = minHeap.top().val;
    while (count < k ) {

        auto top = minHeap.top();
        last = top.val;
        // printf("POPPED :%d\n", last);
        int rightElementI = top.i + 1;
        int rightElementJ = top.j;

        int bottomElementI = top.i;
        int bottomElementJ = top.j + 1;
        addElementToHeapIfUnvisited(rightElementI, rightElementJ);
        addElementToHeapIfUnvisited(bottomElementI, bottomElementJ);

        minHeap.pop();
        count++;
    }
    return last;
}

int main() {
    vector<vector<int>> mat= {{1, 5,9 },{10,11,13}, {12,13,15}};
    assert(kthSmallest(mat, 8) == 13);
    assert(kthSmallest(mat, 3)  == 9);

    vector<vector<int>> mat2= {{1, 2 },{1, 3}};
    assert(kthSmallest(mat2, 2)  == 1);

    vector<vector<int>> mat3 = {{1,3,5}, {6,7,12}, { 11,14,14}};
    assert(kthSmallest(mat3, 5) == 7);
    assert(kthSmallest(mat3, 6) == 11);

}