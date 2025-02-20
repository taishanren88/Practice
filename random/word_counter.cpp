#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <map>
#include <future>
#include <sstream>
#include <mutex>
using namespace std;


void wordCounter(string file) {
	std::mutex g_pages_mutex;

	// Loop through file, line by line
	// tokenize line into words 
	// store words -> count in hash map
	// at end, sort words and output one by one
	ifstream myfile (file);
	unordered_map<string, int> wordCounts;
	std::vector<std::future<void>> futures;
	auto wordcount = [&wordCounts, &g_pages_mutex](vector<string> lines) {
		    std::thread::id this_id = std::this_thread::get_id();
		    // printf("got lock :%d\n", this_id);
		    std::lock_guard<std::mutex> guard(g_pages_mutex);

		for (string & line : lines ) {
			stringstream check1(line); 
		    string token; 

		    // Tokenizing w.r.t. space ' ' 
		    while(getline(check1, token, ' ')) 
		    { 
		    	auto foundItr = wordCounts.find(token);
		    	if (foundItr == wordCounts.end()){
		    		wordCounts[token] = 1; // firstTime adding
		    	} else {
		    		foundItr->second++; // increment
		    	}
		    }
			}
			// printf("after lock :%d\n", this_id);

		};
	vector<string> lines;
	int lineSize = 8096;
	if (myfile.is_open())
	{
		string line;
		while ( getline (myfile,line) )
		{
			lines.push_back(line);
			if (lines.size() == lineSize) {
				auto fut = std::async(std::launch::async, wordcount, (std::move(lines)));
				 futures.push_back(std::move(fut));
				lines = vector<string>();
			}
		}
		auto fut = std::async(std::launch::deferred, wordcount, (std::move(lines)));
		futures.push_back(std::move(fut));
	}

	for (auto& future : futures) {
		future.get();
	}
	map<string, int> sortedOutput(wordCounts.begin(), wordCounts.end());
	for (auto kv : sortedOutput) {
		printf("%s %d\n", kv.first.c_str(), kv.second);
	}
}
int main() {
	wordCounter("word_counter_input.txt");
}