#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

     void sortColors(vector<int>& nums) {
        int posPlaceZero = -1;
        int posPlaceTwo = nums.size();
        int firstUnknown = 0;
        int posNonZero = 0; // This guarnatee to be where the next 0 should be placed , or is the last part in a trail of 1s
        int i = 0;
        while (posPlaceZero < posPlaceTwo && firstUnknown < posPlaceTwo)
        {
            cout << "First unknown is : "<< firstUnknown;
            if (nums[firstUnknown] == 0)
            {
                posPlaceZero++;
                cout << "HERE";
                swap(nums[posPlaceZero],nums[firstUnknown]);
                firstUnknown++;
            }
            else if (nums[firstUnknown] == 1)
            {
                cout << "HERE1";
                firstUnknown++;
            }
            else // 2
            {
                cout <<"HER2";
                posPlaceTwo--;
                swap(nums[firstUnknown], nums[posPlaceTwo]);
            }
        }
        
    }
    
int main()
{
    vector<int> test = {2,0,1};
    sortColors(test);
    for (auto i: test)
        cout << i << endl;
}
