#include "BinTreeUtils.h"
#include <vector>

using namespace std;


int main() {
	vector<std::string> input = {"2", "1", "3", "null", "null", "null", "null"};
	auto output = toTree(input);
	assert(output->val == 2);
	assert(output->left->val == 1);
	assert(output->right->val == 3);
	assert(output->left->left == nullptr);
	assert(output->left->right == nullptr);

	input = {"5", "1", "4", "null", "null", "3", "6"};
	output = toTree(input);
	assert(output->val == 5);
	assert(output->left->val == 1);
	assert(output->right->val == 4);
	assert(output->left->left == nullptr);
	assert(output->left->right == nullptr);
	assert(output->right->left->val == 3);
	assert(output->right->right->val == 6);
	assert(output->right->left->left == nullptr);
	assert(output->right->right->right == nullptr);

}