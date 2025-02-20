#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>
// for convenience
using json = nlohmann::json;
using namespace std;

/*  g++ json.cpp -I/usr/local/opt/nlohmann_json/include/nlohmann 
*/
void calculate() {
    // Parse the data and loop once to insert the most recent data : id -> most recent timestamp
    // Loop a second time to check if there is a more recent entry, if so print it out
    std::ifstream i("/Users/jimmy/Desktop/Practice/sonder/listings2.json");
    json input;
    i >> input;
    json listings = input["listings"];
    unordered_map<int, int> units2MostRecentTimestamps;
    for (json::iterator it = listings.begin(); it != listings.end(); ++it) {
//        std::cout << setw(4) << *it << '\n';
        auto jsonobj = *it;
        auto timestamp = jsonobj["last_updated"].get<string>();
        std::tm t = {};
        std::istringstream ss(timestamp);
        if (ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S")) {
            auto id = jsonobj["internal_id"].get<int>();
            auto time = std::mktime(&t);
            if (units2MostRecentTimestamps.find(id) != units2MostRecentTimestamps.end()) { // previously added
                units2MostRecentTimestamps[id] = std::max(units2MostRecentTimestamps[id], (int) time);
            }
            else { // never inserted before
                units2MostRecentTimestamps[id] = time;
            }
        }
    }
    
    // second time : Check if bookings have been inserted with a timestamp after this one already
    printf("Second time \n");
    for (json::iterator it = listings.begin(); it != listings.end(); ++it) {
        auto jsonobj = *it;
        auto timestamp = jsonobj["last_updated"].get<string>();
        std::tm t = {};
        std::istringstream ss(timestamp);
        if (ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S")) {
            auto id = jsonobj["internal_id"].get<int>();
            auto time = std::mktime(&t);
                if (units2MostRecentTimestamps[id] > time ) {
                    printf("Room id ::%d for partner :%s is outdated\n", id, jsonobj["partner"].get<string>().c_str());
                }
        }
    }
}
int main() {
    calculate();
    
}
