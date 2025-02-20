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

void printCalendar(vector<vector<int>> & units, vector<json> bookings) {
    // At each point, of insertion , for each json booking, take the existing booking of all the units
    // deserialize the json
    // get previous stay length, have map of each offset -> pair(id, stay length)
    // at each point, get the offset and all the pairs, sort by stay length
    // get their length , sort by increasing length of availability
    // loop through from this offset to the next value and check for length of stay
    
    auto getPreviousStaysAndClear =[&](int start, vector<pair<int,int>>& results) {
        results.clear();
        for (int i = 0; i < units.size();i ++){
            if (units[i][start] == 0
                || (start > 0 && units[i][start] == units[i][start - 1])) // ignore people which occupy this unit at at an earlier time , so we dn't break them
                continue;
            int j = start;
            const int startId = units[i][j];
            while (j < units[i].size() && units[i][j] == startId) {
                units[i][j] = 0;
                j++;
            }
            printf("Adding :%d with len :%d\n", startId, j - start);
            results.push_back(make_pair(startId, j - start));
         }
    };
    
   auto  getAvailability =[&](int start) {
       vector<pair<int,int>> availabilities;
        for (int i = 0; i < units.size(); i++) {
            int j = start;
            while (j < units[i].size() && units[i][j] == 0)
                j++;
            printf("Creating space at unit :%d,%d\n", i, j - start);
            availabilities.push_back(make_pair(i, j - start));
        }
       sort(availabilities.begin(), availabilities.end(),[](pair<int,int>& a, pair<int,int>& b) {
           return a.second > b.second;
       });
        return availabilities;
   };

    // get all of the existing json bookings along with the current one and sort by length of stay
    for (auto booking : bookings) {
        int bookingId = booking["id"];
        int checkin = booking["check_in"];
        int checkout = booking ["check_out"];
        printf("id : %d, checkin :%d, checkout :%d\n", bookingId, checkin, checkout);
        vector<pair<int,int>> previousStayLengths;
        getPreviousStaysAndClear(checkin, previousStayLengths);
        previousStayLengths.push_back(make_pair(bookingId, checkout - checkin));
        sort(previousStayLengths.begin(), previousStayLengths.end(), [](pair<int,int>& a, pair<int,int>& b) {
            return a.second > b.second;
        });
        
        auto availability = getAvailability(checkin);
        int availablePos = 0;

        for (int i = 0; i < previousStayLengths.size(); i++ ){
            int personId = previousStayLengths[i].first;
            int stayLength = previousStayLengths[i].second;
            int availableUnit = availability[availablePos].first;
            printf("Unit :%d at :%d available with length of :%d\n", availableUnit, checkin, availability[availablePos].second);

            printf("Insertingperson :%d with length of :%d\n", personId, stayLength);
            for (int j = 0; j < previousStayLengths[i].second; j++) {
                units[availableUnit][j + checkin] = personId;
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
    
    units = {
        {0, 190, 0,  0,   680, 680, 0,   0,   902, 0,   397, 0, 700, 0,   459},
        {0, 0,   0,  0,   166, 166, 166, 0,   0,   601, 0,   0, 358, 0,   129},
        {0, 757, 0,  130, 130, 130, 0,   0,   0,   0,   561, 0, 0,   735, 0},
        {0, 0,   0,  0,   0,   0,   0, 0, 0,   0,   0,   0, 0 ,  0,   0}
    };

    j1 = json::parse("{ \"id\": 289, \"check_in\": 0, \"check_out\": 2 }");
    j2 = json::parse( "{\"id\": 678, \"check_in\": 1, \"check_out\": 2 }");
    j3 = json::parse("{ \"id\": 800, \"check_in\": 5, \"check_out\": 9 }");
    auto j4 = json::parse("{ \"id\": 222, \"check_in\": 7, \"check_out\": 11 }");
    auto j5 = json::parse("{ \"id\": 685, \"check_in\": 7, \"check_out\": 13 }");
    bookings[0] = j1;
    bookings[1] = j2;
    bookings[2] = j3;
    bookings.push_back(j4);
    bookings.push_back(j5);

    printCalendar(units, bookings);
    
}
