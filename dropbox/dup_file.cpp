#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <sstream>
using namespace std;

vector<vector<string>> findDuplicate(vector<string>& paths) {
    // For each string, extract the directory  + all of the file paths
    // For each file path , concatenate the path to the directory , get its content 
    // To tokenize, tokenize by parenthese and spaces
    // Map the content string to the file path as a hash map
    auto tokenize =[](string inputString) {
            std::stringstream stringStream(inputString);
            std::string line;
            vector<string> results;
            while(std::getline(stringStream, line)) 
            {
                std::size_t prev = 0, pos;
                while ((pos = line.find_first_of(" ()", prev)) != std::string::npos)
                {
                    if (pos > prev)
                        results.push_back(line.substr(prev, pos-prev));
                    prev = pos+1;
                }
                if (prev < line.length())
                    results.push_back(line.substr(prev, std::string::npos));
            }
            return results;
    };

    unordered_map<string, vector<string>> content2Files;
    for (int i = 0; i < paths.size(); i++){
        auto tokenized = tokenize(paths[i]);
        auto directory = tokenized[0];
        int j =1 ;
        while (j < tokenized.size()){
            auto path = tokenized[j];
            auto content = tokenized[j+1];
            auto fullPath = directory + '/' + path;
            content2Files[content].push_back(fullPath);
            j+=2;
        }
    }

    vector<vector<string>> results;
    for (auto kv : content2Files) {
        if (kv.second.size() > 1)
            results.push_back(kv.second);
    }
    return results;
}


int main(){
    vector<string> paths = {"root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"};
    auto res  = findDuplicate(paths);
    for (auto vec : res) {
        for (auto str : vec)
            cout << str << "," ;
    }
    paths= {"root/a 1.txt(abcd) 2.txt(efsfgh)","root/c 3.txt(abdfcd)","root/c/d 4.txt(efggdfh)"};
    auto res2=  findDuplicate(paths);
    assert(res2.empty()); // non-dups aren't ouputed
}