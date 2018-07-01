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
#include <unordered_map>
#include <cassert>

using namespace std;

struct KVPair
{
    KVPair(int k, int v)
    {
        key = k;
        value = v;
        count = 1;
    }
    int key, value, count;
};


class LFUCache {
public:
    
    LFUCache(int capacity)
    :m_capacity(capacity)
    { 
    }
    
    int get(int key) {
        auto found = updateCountForExistingItem(key);
        if (found != m_items.end())
            return found->second->value;
        else
            return -1;
    }
    
    // return map iterator to to item if it exists
    unordered_map<int,list<KVPair>::iterator>::iterator updateCountForExistingItem(int key)
    {
        unordered_map<int,list<KVPair>::iterator>::iterator foundItr = m_items.find(key);
        if (foundItr != m_items.end()) // update the existing element
        {
            // TODO: Move this to get
            map<int, list<KVPair>>::iterator list1FoundItr = m_key2Lists.find(foundItr->second->count);
            auto count = ++(foundItr->second->count);
            auto list2FoundItr = m_key2Lists.find(count);
            if (list2FoundItr == m_key2Lists.end())
            {
                m_key2Lists[count] = list<KVPair>();
                m_key2Lists[count].push_front(*(foundItr->second));
                list1FoundItr->second.erase(foundItr->second);
            }
            else
            {
                list2FoundItr->second.splice(list2FoundItr->second.begin(), list1FoundItr->second, foundItr->second);
            }
            foundItr->second = m_key2Lists[count].begin();
            if (m_key2Lists[count-1].empty())
                m_key2Lists.erase(count - 1);
            return foundItr;
        }

        return m_items.end();
    }
 
    void put(int key, int value) {
        if (m_capacity == 0)
            return;
        // current key iterator
        auto foundItr = updateCountForExistingItem(key);
        if (foundItr != m_items.end() ) // update the existing element
        {
            foundItr->second->value = value;
        }
        else
        {
            // new element, check to see if we have reached capacity
            if (m_items.size() == m_capacity)
            {

                // remove the oldest item
                auto lruItr = m_key2Lists.begin();

                auto lrucount = lruItr->first; // current frequency
                // erase the lsat item in this list
                auto erasedKey = lruItr->second.back().key;

                lruItr->second.pop_back();
                if (lruItr->second.empty())
                    m_key2Lists.erase(lrucount);

                m_items.erase(erasedKey);
            }
            if (m_key2Lists.find(1) == m_key2Lists.end())
                m_key2Lists[1] = list<KVPair>();

            m_key2Lists[1].push_front(KVPair(key, value));
            m_items[key] = m_key2Lists[1].begin();
        }
    }

    int m_capacity;
    unordered_map<int,list<KVPair>::iterator> m_items;  // key to item
    map<int, list<KVPair>> m_key2Lists; //  frequency to list of items in an LRU list
};

int main()
{
     LFUCache obj (2);
     obj.put(1,1);
     assert(obj.get(1) == 1);
     obj.put(2,2);
     assert(obj.get(1) == 1);
     obj.put(3,3);
     assert(obj.get(3) == 3);
     assert(obj.get(2) == -1);
     assert(obj.get(2) == -1);
     assert(obj.get(2) == -1);

     assert(obj.get(3) == 3);

     obj.put(4, 4);
     cout << obj.get(1) <<endl;
     assert(obj.get(1) == -1);
     assert(obj.get(3) == 3);
     assert(obj.get(4) == 4);
     
     LFUCache obj2 (0);
     obj2.put(0,0);
     assert(obj2.get(0) == -1);
}
