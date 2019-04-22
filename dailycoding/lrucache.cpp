#include <iostream>
#include <unordered_map>
#include <list>
#include <iterator>
#include <cassert>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity)
    : fCapacity(capacity) { }
    
    int get(int key) {
        if (fKeyValLookup.find(key) == fKeyValLookup.end()) 
            return -1;

        auto itr = fKeyItrLookup[key];
        fLruOrdering.splice(fLruOrdering.begin(), fLruOrdering, itr);
        itr = fLruOrdering.begin();
        fKeyItrLookup[key] = itr;
        return fKeyValLookup[key];
    }
    
    void put(int key, int value) {
        if (fKeyValLookup.find(key) == fKeyValLookup.end())
        {
            fLruOrdering.push_front(key);
            fKeyValLookup[key]= value;
            fKeyItrLookup[key] = fLruOrdering.begin();
        }
        else
        {
            fKeyValLookup[key]= value;
            get(key);
        }

        if (fKeyValLookup.size() > fCapacity)
        {
            auto last = fLruOrdering.back();
            fKeyItrLookup.erase(last);
            fKeyValLookup.erase(last);
            fLruOrdering.pop_back();
        }
    }

    // Test Method
    int getFrontKey() const {
        return fLruOrdering.front();
    }
    private:

    // list to maintain lru ordering
    std::list<int> fLruOrdering;
    
    // Stores keys -> placement (allow for easy placement)
    std::unordered_map<int, std::list<int>::iterator> fKeyItrLookup;

    // Store keys -> Values
    std::unordered_map<int, int> fKeyValLookup;

    int fCapacity;
};

int main()
{
    LRUCache lru(3);
    lru.put(1, 1);
    assert(lru.get(1) == 1);
    lru.put(2, 2);
    assert(lru.get(2) == 2);
    assert(lru.getFrontKey() == 2);
    lru.get(1);
    assert(lru.getFrontKey() == 1);
    lru.put(3,3);
    assert(lru.getFrontKey() == 3);
    lru.put(4,4);
    assert(lru.getFrontKey() == 4);
    lru.get(1);
    assert(lru.getFrontKey() == 1);


    //

    


    LRUCache lru2(2);
    assert(lru2.get(2) == -1);
    lru2.put(2,6);
    assert(lru2.get(1) == -1);
    lru2.put(1,5);
    lru2.put(1,2);
    assert(lru2.get(1) == 2);
    assert(lru2.get(2) == 6);


    //

LRUCache lru3(2);
    lru3.put(2, 1);
    lru3.put(1,1);
    lru3.put(2,3);
    lru3.put(4,1);
    cout << lru3.get(1) << endl;
    assert(lru3.get(1) == -1);
    assert(lru3.get(2) == 3);
    return 0;
}