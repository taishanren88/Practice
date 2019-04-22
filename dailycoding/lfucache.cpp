#include <iostream>
#include <map>
#include <unordered_map>
#include <list>
#include <iterator>
#include <cassert>

using namespace std;

class LFUCache {
public:
    LFUCache(int capacity)
    :m_capacity(capacity) {
        
    }
    
    int get(int key) {
       if (keys2Values.find(key) == keys2Values.end())
                return -1;
       auto frequency = keys2Frequencies[key];
        auto itr = keys2Iterators[key];
        frequencies2Lists[frequency].erase(itr);
         if (frequencies2Lists[frequency].empty()) // no longer needed
             frequencies2Lists.erase(frequency);
        
        frequency++;
        addElement(key, frequency, keys2Values[key]);

        return keys2Values[key];
    }

    
    void put(int key, int value) {
        if (m_capacity == 0) return;
        if (keys2Values.find(key) == keys2Values.end())
        {
            if (keys2Values.size() == m_capacity)
            {
                auto oldestFrequency = frequencies2Lists.begin();
                auto frequency = oldestFrequency->first;
                auto oldestKey = frequencies2Lists[frequency].back();

                keys2Values.erase(oldestKey);
                keys2Frequencies.erase(oldestKey);
                keys2Iterators.erase(oldestKey);
                frequencies2Lists[frequency].pop_back();
                if (frequencies2Lists[frequency].empty()) // no longer needed
                    frequencies2Lists.erase(frequency);
                cout << "evicting " << oldestKey << endl;
            }
            createListIfNecessary(1);
            addElement(key, 1, value);
        }
        else
        {
             get(key);
             keys2Values[key] = value;
        }
    }
private:
     int m_capacity;
     unordered_map<int, int> keys2Values;
     unordered_map<int, int> keys2Frequencies;
     unordered_map<int, std::list<int>::iterator> keys2Iterators;
     map<int, std::list<int>> frequencies2Lists;

 void createListIfNecessary (int freq){
            if (frequencies2Lists.find(freq) == frequencies2Lists.end())
                frequencies2Lists[freq] = std::list<int>();
        }
    void addElement (int key, int frequency , int value){
            createListIfNecessary(frequency);
            frequencies2Lists[frequency].push_front(key);
            keys2Iterators[key] = frequencies2Lists[frequency].begin();
            keys2Frequencies[key] = frequency;
            keys2Values[key] = value;
        }
};

int main()
{
LFUCache cache2(0);
cache2.put(0,0);
assert(cache2.get(0) == -1);
LFUCache cache ( 2 /* capacity */ );
cache.put(1, 1);

cache.put(2, 2);
  assert(cache.get(1) == 1);
cache.put(3,3);
assert(cache.get(2) == -1);
assert(cache.get(3) == 3);
cout << "about to insert 4 " << endl;
cache.put(4,4);
cout << cache.get(1) << endl;
assert(cache.get(1) == -1);
assert(cache.get(3) == 3);
assert(cache.get(4) == 4);
}