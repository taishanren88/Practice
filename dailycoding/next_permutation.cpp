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

  void nextPermutation(vector<int>& nums) {
        auto myreverse = [&nums](int l, int r){
            while (l < r)
            {
                std::swap(nums[l], nums[r]);
                l++;
                r--;
            }
        };
         for (int i = nums.size() - 1 ; i >= 0; i--)
         {
             if (i >0 && nums[i] > nums[i-1])
             {
                // At this point , eerything to the right of i is < adjacent element
                 // e.g. 1 ,4,3, , i = 1, j = 0
                // Minimize the cost of the new element by finding a smaller to swap with 
                // 
                 for (int k = nums.size() -1 ; k > i -1; k--)
                 {
                    if (nums[k] > nums[i-1])
                    {
                        swap(nums[i-1], nums[k]);
                        break;
                    }
                 }
               
                myreverse(i, nums.size() - 1);
                return;
              }
         }
        myreverse(0, nums.size() - 1);
    }

int main()
{
    vector<int> v1 = {1,2,3};
    nextPermutation(v1);
  
      assert(v1[0] == 1 && v1[1] == 3);
    // // 1, 3, 2
    //   // 3 1 2
    // // 1, 5,7, 6
    nextPermutation(v1);

    // cout << endl;
     assert(v1[0] == 2 && v1[1] == 1 && v1[2] == 3);
        v1 = {4,2,0,2,3,2,0};
     nextPermutation(v1);
    // for (auto n : v1)
    //     cout << n << ",";
    //  assert(v1[0] == 2 && v1[1] == 1 && v1[2] == 3);

}

