#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs) {
	// maintain a mapping of (sorted string) -> list of results
	// iterate over the mapping and return the results
	unordered_map<string,vector<string>> mapping;
	for (auto str : strs) {
		auto strOriginal = str;
		std::sort(str.begin(), str.end());
		mapping[str].push_back(strOriginal);
	}
	vector<vector<string>> results;
	for (auto kv : mapping) {
		results.push_back(kv.second);
	}
	return results;
}

int main() {

}