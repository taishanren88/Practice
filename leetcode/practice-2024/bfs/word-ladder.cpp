#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;


int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
   // Create a dictionary of words becaus we need to lookup
   // maintain a queue of words , where the start word is push to queue
   // iterate over the queue and start changing the letters one by one
   // if we create a word where we have not visited it before enter into the queue
   // if we reach the end word we are done
   
   unordered_set<string> visited;
   unordered_set<string> dictionary(wordList.begin(), wordList.end());
   queue<string> todo;
   int resultLen = 1;
   todo.push(beginWord);
   while (!todo.empty()) {
   	int queueLen = todo.size();
   	for (int i = 0; i < queueLen; i++) {
	   	 auto front = todo.front();
	   	 todo.pop();
	   	 if (visited.find(front) != visited.end()) {
	   	 	continue;
	   	 }
	   	 visited.insert(front);
	   	 if (front == endWord) {
	   	 	return resultLen;
	   	 }
	   	 for (int i = 0; i < front.size(); i++){
	   	 	for (char c = 'a' ; c <= 'z'; c++) {
	   	 		auto original = front[i];
	   	 		front[i] = c;
	   	 		if (dictionary.find(front) != dictionary.end()) {
	   	 			todo.push(front);
				}
	   	 		front[i] = original;
	   	 	}
	   	 }
   	}
   		   	 resultLen++;
   }
   return 0;     
}
int main() {
	vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
		cout << ladderLength("hit", "cog", wordList ) << endl;
			vector<string> wordList2 = {"hot","dot","dog","lot","log"};

		cout << ladderLength("hit", "cog", wordList2 ) << endl;

}