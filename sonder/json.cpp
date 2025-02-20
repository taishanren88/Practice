#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip> 
// for convenience
using json = nlohmann::json;
using namespace std;

/*  g++ json.cpp -I/usr/local/opt/nlohmann_json/include/nlohmann 
*/
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

auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");
auto j3Found = j3.find("happy");
if (j3Found != j3.end()) {
	cout << "found key " << *j3Found <<  endl;
}
cout << "Using contains " << j3.contains("happy") << endl;
cout << "Using not contains " << !j3.contains("jimmy") << endl;

cout << *(j2.find("answer"));
cout << "All done " << endl;
// Tr catching
 try
     {
         // calling at() for a non-existing key
         json j = {{"foo", "bar"}};
         json k = j.at("foo");
         j["foo"] = "baz";
         cout << "Changed j " << j << endl;
         j.erase("foo");
         cout << "removed only key " << j << endl;
     }
     catch (json::exception& e)
     {
         // output exception information
         std::cout << "message: " << e.what() << '\n'
                   << "exception id: " << e.id << std::endl;
     }

cout << endl;
int x = 10;
int y = 20;

     json creation = {
  {"pi", 3.141},
  {"happy", true},
  {"name", "Niels"},
  {"nothing", nullptr},
  {"answer", {
    {"everything", y}
  }},
  {"list", {1, 0, 2}},
  {"object", {
    {"currency", "USD"},
    {"value", x}
  }}
};

std::function<void(json&, string)> getType=[&](json& creation, string key) {
	if (!creation.contains(key) ) {
		cout << "not found key " << endl;
		return;
	}

	if (creation[key].is_boolean()) {
		cout << "Boolean type for "  << key << endl;
		cout << "bool value is " << creation[key].get<bool>() << endl;
	} else if (creation[key].is_string()) {
		cout << "string type for "  << key << endl;
		cout << "string value is " << creation[key].get<string>() << endl;
	} else if (creation[key].is_array()){ 
		cout << "array type for "  << key << endl;
		for (auto& el : creation[key].items()) {
			string itemkey = el.key(); 
			cout << el.value() <<","; 
			}
			cout << endl;
	}
	else if (creation[key].is_number_float()){ 
		cout << "double type for "  << key << endl;
		cout << "double value is " << creation[key].get<double>() << endl;
	} else if (creation[key].is_object()) {
		cout << "object type for "  << key << endl;
	}
};
/*
  {"pi", 3.141},
  {"happy", true},
  {"name", "Niels"},
  {"nothing", nullptr},
  {"answer", {
    {"everything", y}
  }},
  {"list", {1, 0, 2}},
  {"object", {
    {"currency", "USD"},
    {"value", x}
  }}
*/
getType(creation, "pi");
getType(creation, "happy");
getType(creation, "list");
getType(creation, "object");
cout << creation << endl;
cout << "Try parsing bad json " << endl;
 try
     {
         // calling at() for a non-existing key
          json myjson  = json::parse("{ \"happy\": true,sadfsdfasdfadsfasdf \"pi\": 3.141 }");
     }
     catch (json::exception& e)
     {
         // output exception information
     	cout << "failed to parse " << endl;
         std::cout << "message: " << e.what() << '\n'
                   << "exception id: " << e.id << std::endl;
     }
json jsoninput;

try {
    cout << "Reading from json file" << endl;
    // read a JSON file
		std::ifstream i("file.json");
		i >> jsoninput;
					cout << jsoninput << endl;

	}
	catch (json::exception& e ) {
		 	cout << "failed to parse " << endl;
         std::cout << "message: " << e.what() << '\n'
                   << "exception id: " << e.id << std::endl;
	}



cout << "writing to json file " << endl;
try {
	std::ofstream o("pretty.json");
	o  << setw(4) << jsoninput << std::endl;
}
catch (json::exception& e) {
	 	cout << "failed to parse " << endl;
         std::cout << "message: " << e.what() << '\n'
                   << "exception id: " << e.id << std::endl;
}

cout << "Finally done " << endl;
}

