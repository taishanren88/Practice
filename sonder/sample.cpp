#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
// for convenience
using json = nlohmann::json;
using namespace std;

/*  g++ json.cpp -I/usr/local/opt/nlohmann_json/include/nlohmann 
*/
// Unit -> availability count
// Return list of availabilities
map<int, int, greater <int>> getAvailability(int start, vector<vector<int>>& units) {
    map<int,int, greater <int>> results;
    for (int i = 0; i < units.size(); i++) {
        int val = units[i][start];
        int j = start;
        if (j > 0 && units[i][j] != val) {
            while (j < units[i].size() && units[i][j] == val) {
                j++;
            }
            while ( j < units[i].size() && units[i][j] == 0)
                j++;
        }
        results[i] = j - i;
    }
    return results;
}
// maps id -> stay length
map<int, int, greater<int>> getPreviousStays(int start, vector<vector<int>>& units) {
    map<int, int, greater<int>> results;
    for (int i = 0; i < units.size(); i++) {
        int val = units[i][start];
        int j = start;
        if (j > 0 && units[i][j] != val) {
            while (j < units[i].size() && units[i][j] == val) {
                j++;
                units[i][j] = 0;
            }
            printf("inserting id :%d with lengt :%d\n", val, j -i);
            results[val] = j - i;
        }
    }
    return results;
}

void printCalendar(vector<vector<int>> & units, vector<json> bookings) {
    // At each point, of insertion , for each json booking, take the existing booking of all the units
    // deserialize the json
    
    // get their length , sort by increasing length of availability
    // loop through from this offset to the next value and check for length of stay
   
    // get all of the existing json bookings along with the current one and sort by length of stay
    for (auto booking : bookings) {
        int bookingId = booking["id"];
        int checkin = booking["check_in"];
        int checkout = booking ["check_out"];
        printf("id : %d, checkin :%d, checkout :%d\n", bookingId, checkin, checkout);
        auto availability = getAvailability(checkin, units);
        auto people = getPreviousStays(checkin, units);
        people[checkin] =  checkout - checkin;
        for (auto kv : availability) {
            int unit = kv.first;
            for (auto person : people) {
                int personId = person.first;
                int stayLength = person.second;
                printf("Trying to add person :%d with stay length :%d\n", personId, stayLength);

                for (int i = 0; i < stayLength; i++ ){
                    units[unit][checkin] = personId;
                }
            }
            
        }
    }
    
    for (int i = 0; i < units.size(); i++) {
        printf("Unit :%d, ", i);
        for (int j = 0; j < units[i].size(); j++ ){
            printf("%d ", units[i][j]);
        }
        printf("\n");
    }
    
    
}
int main() {
    vector<vector<int>> units = {
        {241, 241, 241, 0,   0, 367, 367, 0, 0, 198, 198, 198, 0, 0, 0},
        {0,   0,   193, 193, 0, 0,   0,   0, 0, 0,   0,   0,   0, 0, 0}
    };
    /*
     { "id": 983, "check_in": 3, "check_out": 5 },
     { "id": 7237, "check_in": 7, "check_out": 9 },
     { "id": 290, "check_in": 0, "check_out": 3 },
     { "id": 100, "check_in": 12, "check_out": 14 }
     */
    auto j1 = json::parse("{ \"id\": 729, \"check_in\": 3, \"check_out\": 5 }");
//    auto j2 = json::parse( "{\"id\": 184, \"check_in\": 6, \"check_out\": 7}");
//    auto j3 = json::parse("{ \"id\": 399, \"check_in\": 8, \"check_out\": 13 }");
//    auto j4 = json::parse("{ \"id\": 100, \"check_in\": 12, \"check_out\": 14 }");
    vector<json> bookings = {j1};
    printCalendar(units, bookings);

}
