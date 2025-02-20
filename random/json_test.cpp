#include <iostream>
#include <json.hpp>
using namespace nlohmann;
using namespace std;
/* 
Instructions on how to use:
https://github.com/nlohmann/homebrew-json

Compile like so : g++ json_test.cpp -I/usr/local/opt/nlohmann_json/include/nlohmann/ */
void dfs(json& o){
for (auto& el : o.items()) {
		if (el.value().is_object())
			dfs(el.value());
		else
  			std::cout << el.key() << " : " << el.value() << "\n";
	}
}
int main() {
// create an empty structure (null)
json j;

// add a number that is stored as double (note the implicit conversion of j to an object)
j["pi"] = 3.141;

// add a Boolean that is stored as bool
j["happy"] = true;

// add a string that is stored as std::string
j["name"] = "Niels";

// add another null object by passing nullptr
j["nothing"] = nullptr;

// add an object inside the object
j["answer"]["everything"] = 42;

// add an array that is stored as std::vector (using an initializer list)
j["list"] = { 1, 0, 2 };

// add another object (using an initializer list of pairs)
j["object"] = { {"currency", "USD"}, {"value", 42.99} };

// instead, you could also write (which looks very similar to the JSON above)
json j2 = {
  {"pi", 3.141},
  {"happy", true},
  {"name", "Niels"},
  {"nothing", nullptr},
  {"answer", {
    {"everything", 42}
  }},
  {"list", {1, 0, 2}},
  {"object", {
    {"currency", "USD"},
    {"value", 42.99}
  }}
};
// cout << j << endl;
// json j3 = "{ \"happy\": true, \"pi\": 3.141 }"_json;
// cout << endl << j3 << endl;
//  if (j["happy"].is_null())
//  	cout << "is boolean" << endl;
//  auto hapVal = j["happy"];
//  cout << hapVal << endl;

//  for (json::iterator it = j2.begin(); it != j2.end(); ++it) {
//   std::cout << it.key() << " : " << it.value() << "\n";
// }
dfs(j2);
}