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
vector<pair<int,int>> getAvailability(int start, vector<vector<int>>& units) {
    unordered_map<int,int> availabilities;
    for (int i = 0; i < units.size(); i++) {
        int val = units[i][start];
        int j = start;
        // If previous unit can be moved or considered in another place
        // If it's the first position , it's available
        // If it's another position, ensure it's  different from before , latter case to detect that we can't break consecutive bookings, if it's value is 0 , surely we can use it
        if ( j == 0 || (units[i][j]  != units[i][j-1]) || units[i][j] == 0) {
            while (j < units[i].size() && units[i][j] == val) {
                j++;
            }
            while ( j < units[i].size() && units[i][j] == 0)
                j++;
        }
        availabilities[i] = j - start;
    }
    vector<pair<int,int>> results(availabilities.begin(), availabilities.end());
    return results;
}
// maps id -> stay length
vector<pair<int,int>> getPreviousStays(int start, vector<vector<int>>& units) {
    unordered_map<int, int> stays2Lengths;
    for (int i = 0; i < units.size(); i++) {
        int val = units[i][start];
        int j = start;
        // Check who has stayed here before
        // If it's the first position , ensure it's not 0
        // If it's subsequent ensure not 0 and different from before , latter case to detect that we can't break consecutive bookings
        if ( (j == 0 && units[i][j] != 0)
            || (j > 0 && units[i][j] != 0 && units[i][j]  != units[i][j-1])) {
            while (j < units[i].size() && units[i][j] == val) {
                units[i][j] = 0;
                j++;
            }
            stays2Lengths[val] = j - start;
        }
    }
    vector<pair<int,int>> results (stays2Lengths.begin(), stays2Lengths.end());
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
        people.push_back(make_pair(bookingId, checkout - checkin));
        sort(availability.begin(), availability.end(), [](pair<int,int>& a, pair<int,int>& b) {
            return a.second > b.second;

        });
        sort(people.begin(), people.end(), [](pair<int,int>& a, pair<int,int>& b) {
            return a.second > b.second;
        });
        auto availablePos = 0;
        for (auto person : people) {
            auto unit = availability[availablePos].first;
            int personId = person.first;
            int stayLength = person.second;
            for (int i = 0; i < stayLength; i++ ){
                units[unit][checkin + i] = personId;
            }
            availablePos++;
        }
    }
    
    for (int i = 0; i < units.size(); i++) {
        printf("Unit :%d, ", i);
        for (int j = 0; j < units[i].size(); j++ ){
            cout << setw(5) << units[i][j] << " ";
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
     { "id": 729, "check_in": 3, "check_out": 5 },
     { "id": 184, "check_in": 6, "check_out": 7 },
     { "id": 399, "check_in": 8, "check_out": 13 },
     */
    auto j1 = json::parse("{ \"id\": 729, \"check_in\": 3, \"check_out\": 5 }");
   auto j2 = json::parse( "{\"id\": 184, \"check_in\": 6, \"check_out\": 7}");
   auto j3 = json::parse("{ \"id\": 399, \"check_in\": 8, \"check_out\": 13 }");
    vector<json> bookings = {j1, j2, j3};
    printCalendar(units, bookings);
//
//    // Medium case
     units = {
         {900, 900, 900, 0,   281, 281, 0,   0,   0,   831, 831, 831, 0,   0, 0},
         {0,   0,   0,   768, 0,   278, 465, 465, 465, 0,   0,   0,   444, 0, 0}
    };
    j1 = json::parse("{ \"id\": 983, \"check_in\": 3, \"check_out\": 5 }");
    j2 = json::parse( "{\"id\": 290, \"check_in\": 0, \"check_out\": 3}");
    j3 = json::parse("{ \"id\": 100, \"check_in\": 12, \"check_out\": 14 }");

    bookings = {j1, j2, j3};
    printCalendar(units, bookings);
    }