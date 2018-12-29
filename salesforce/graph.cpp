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

static bool enablePrint = false; // Put to false if want to disable test output
 #define PRINT_DEBUG(_fmt_, _ARG_...)  if (enablePrint) printf(_fmt_ "\n", ## _ARG_)
 #define PRINT_RESULT(_fmt_, _ARG_...)  if (1) printf(_fmt_ "\n", ## _ARG_)
 #define PRINT_RESULT_NO_NEWLINE(_fmt_, _ARG_...)  if (1) printf(_fmt_, ## _ARG_)

class DependencyGraph
{
public:
    DependencyGraph()
    {

    }
    // Insert into dependency graph. Return true on success, false otherwise
    // TODO :Error cases to be handled later
    bool insert(string command, const vector<string>& dependencies)
    {

        string output = "DEPEND " + command;
        for (string s : dependencies)
            output += " " + s;
        if (!valid(command, dependencies, output))
        {
            return false;
        }
        PRINT_DEBUG(" %s command depends on :", command.c_str());
        auto commandFound = graph.find(command);
        if (commandFound == graph.end())
        {
            graph[command] = make_pair(vector<string>(), vector<string>());
        }

        for (string s : dependencies)
        {
            // output += " " + s;
            PRINT_DEBUG(" %s,", s.c_str());
            auto found = graph.find(s);
            if (found == graph.end())
                graph[s] = make_pair(vector<string>(),vector<string>());
            graph[command].first.push_back(s); // insert dependency to this command
            graph[s].second.push_back(command); //insert this command to those that  depend on it
        }
        PRINT_RESULT("%s", output.c_str());
        return true;
    }
    
    // Returns false if we have circular dependency, true otherwise on success.
    bool valid(string command, const vector<string>& dependencies, string& original)
    {
        for (auto s: dependencies)
        {
            auto found = graph.find(s);
            if (found != graph.end())
            {
                for (string t : found->second.first)
                {
                    if (t == command)
                    {
                        PRINT_RESULT("%s", original.c_str());
                        PRINT_RESULT("%s depends on %s, ignoring command", s.c_str(), command.c_str());
                        return false;
                    }
                }
            }
        }
        return true;
    }
    const vector<string> getDependencies(string command) const
    {
        const auto itr = graph.find(command);
        if (itr != graph.end())
            return itr->second.first;
        else
            return vector<string>();
    }

    const vector<string> getDependents(string command) const
    {
        const auto itr= graph.find(command);
        if (itr !=graph.end())
            return itr->second.second;
        else
            return vector<string>();
    }

    private:
    // Each node represents a command, the first item in pairis what it dpeends on
    // The second item is what depends on it
    // Assumption that for every command it doesn't have a lot of dependencies (maybe at maxiumum 100, so just use vector
    // instead of 2 more maps
    unordered_map<string, pair<vector<string>, vector<string>>> graph ;
};

class System
{
public:
    System()
    {

    }
    // installs the command
    // Returns the resulting instructions in a vector , to be used for testing
    vector<string> install(string command, const DependencyGraph& graph)
    {
        
        vector<string> output;
        PRINT_RESULT("INSTALL %s", command.c_str());
        if (command2Index.find(command) != command2Index.end())
        {
            PRINT_RESULT("%s is already installed", command.c_str());
        }
        else
            installHelper(command, graph, output);
        return output;
    }

    // lists all installed components
     // Returns the resulting instructions in a vector, to be used for testing
    vector<string> list() const
    {
        PRINT_RESULT("LIST");
        // only list those still in our set
        for (string s : installedCommands)
        {
            if (command2Index.find(s) != command2Index.end())
                PRINT_RESULT("%s", s.c_str());
        }
        return installedCommands;
    }
    void remove(string command, const DependencyGraph& graph)
    {
        PRINT_RESULT("REMOVE %s", command.c_str());
         vector<string> output;
         if (command2Index.find(command) == command2Index.end())
         {
             PRINT_RESULT("%s is not installed", command.c_str());
         }
         else if (!canRemove(command, graph, output))
         {
            PRINT_RESULT("%s is still needed", command.c_str());
         }
         else
            removeHelper(command, graph, output);
    }
private:
    // Recursive function to install all of a command's dependencies
    void installHelper(string command, const DependencyGraph& graph, vector<string>&output)
    {
        auto found = command2Index.find(command);
        if ( found != command2Index.end())
        {
            PRINT_DEBUG("%s is already installed", found->first.c_str());
            return;
        }

        const auto dependencies = graph.getDependencies(command);
        for (string dependency : dependencies)
        {
            installHelper(dependency, graph, output);
        }
        string cmd = "Installing " + command;
        PRINT_RESULT("%s", cmd.c_str());
        command2Index[command] = installedCommands.size();
        installedCommands.push_back(command);
        output.push_back(cmd);
    }

    bool canRemove(string command, const DependencyGraph& graph, vector<string>& output) const
    {
        // Already removed
        if (command2Index.find(command) == command2Index.end())
            return false;

        auto dependents = graph.getDependents(command);
        for (auto s : dependents)
        {
            if (command2Index.find(s) != command2Index.end())
                return false;
        }
        return true;
    }
    
    void removeHelper(string command, const DependencyGraph& graph, vector<string>& output)
     {
        // Recursively remove
        if (canRemove(command, graph, output))
        {
            command2Index.erase(command);
            PRINT_RESULT("Removing %s", command.c_str());
            for (auto s : graph.getDependencies(command))
                removeHelper(s, graph, output);
        }
     }


    // map command to installed location
    unordered_map<string, int> command2Index;
    vector<string> installedCommands;
};

void doIt(vector < string > input) 
{
    System system;
    DependencyGraph graph;
    // For each command. We assume that beginning (size) and end inputs are correct
    // you know that the first element is the size already and last element is "END", 
    // so just get everything in b/w
    int numCommands = input.size() - 1;
    for (int i = 0; i < numCommands; i++)
    {
            PRINT_DEBUG("COMMAND IS :%s", input[i].c_str());
           // Do the parsing here
            // Vector of string to save tokens 
            vector <string> tokens; 
            // stringstream class check1 
            stringstream check1(input[i]); 
            string first; 
            // Tokenizing w.r.t. space ' ' 
            getline(check1, first, ' '); // get the first command first to understand what we're doing
            vector<string> remaining;
            string intermediate;
            while(getline(check1, intermediate, ' ')) 
            { 
                remaining.push_back(intermediate); 
            } 
            if (first == "INSTALL")
            {
                system.install(remaining[0],graph);
            }
            else if (first == "DEPEND")
            {
                vector<string> dependencies(remaining.begin() + 1, remaining.end());
                graph.insert(remaining[0], dependencies);
            }
            else if (first == "REMOVE")
            {
                system.remove(remaining[0], graph);
                // system.remove
            }
            else if (first == "LIST")
            {
                system.list();
                ;
            }
            else
            {
                ;
                 // error
            }
    }
     PRINT_RESULT("END");

}


void testIt()
{
     cout << endl << "RUNNING TESTS NOW " << endl;
    DependencyGraph dg1; 
    dg1.insert("A", {"B", "C"});
    auto t = dg1.getDependencies("A");
    assert(t[0] == "B" && t[1] == "C");
    assert(dg1.getDependents("B")[0] == "A");
    assert(dg1.getDependents("C")[0] == "A");
    System s; 
   auto res =  s.install("A", dg1);
    assert(res[0] == "Installing B" && res[1] == "Installing C");

    cout << "ALL TEST CASES PASSED" << endl;
    
}
int main()
{
    vector<string>case1 = {"DEPEND A B C", "INSTALL B", "INSTALL A", "LIST", "END"};
     vector<string> case2 = {"DEPEND TELNET TCPIP NETCARD", "DEPEND TCPIP NETCARD", "DEPEND NETCARD TCPIP", "DEPEND DNS TCPIP NETCARD", "DEPEND BROWSER TCPIP HTML", "INSTALL NETCARD", "INSTALL TELNET", "INSTALL foo", "REMOVE NETCARD", "INSTALL BROWSER", "INSTALL DNS", "LIST", "REMOVE TELNET", "REMOVE NETCARD", "REMOVE DNS", "REMOVE NETCARD", "INSTALL NETCARD", "REMOVE TCPIP", "REMOVE BROWSER", "REMOVE TCPIP", "LIST", "END"};
     // testIt();
      doIt(case2);
}
