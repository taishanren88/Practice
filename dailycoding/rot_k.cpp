#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void rotate( vector<int>& input, int k)
{
	k = k % input.size();
	int posToFill = 0;
    const int N = input.size();
    const int offset = N - k;
	int current = offset;
	while (posToFill < k)
	{
		swap(input[posToFill], input[current]);
		current++;
		posToFill++;
	}

	// Swap the remaining
	 for_each (input.begin(), input.end(), [](const int& x) {
	 	cout << x << ",";
	 });
	// while (posToFill < N)
	// {
	// 	if (current == N)
	// 		current = offset;
	// 	swap(input[posToFill], input[current]);
	// 		 for_each (input.begin(), input.end(), [](const int& x) {
	//  });
	// 		 cout << endl;
	// 	current++;
	// 	posToFill++;
	// }


}
int main()
{
	vector<int> input = {1,2,3,4,5,6,7};
	rotate(input, 3);
	 // for_each (input.begin(), input.end(), [](const int& x) {
	 // 	cout << x << "," << endl;
	 // });

}