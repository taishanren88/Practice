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
    }
    int key, value;
};


class LRUCache {
public:
    
    LRUCache(int capacity)
    :m_capacity(capacity)
    { 
    }
    
    int get(int key) {
        auto found = m_items.find(key);
        if (found != m_items.end())
        {
            update(key); // move element to beginning of list
            return found->second->value;
        }
        else
            return -1;
    }

     // move element to beginning of list
    void update(int key)
    {
        m_list.splice(m_list.begin(), m_list, m_items[key]);
        m_items[key] = m_list.begin();
    }
    void put(int key, int value) {
        if (m_capacity <= 0)
            return;
        // if we're at capacity and new element doesn't exist already, we must 
        // remove
        if (m_items.size() == m_capacity 
            && m_items.find(key) == m_items.end())
        {
            auto oldestKeyEntry = m_list.back().key;
            m_list.pop_back();
            m_items.erase(oldestKeyEntry);
        }

        if (m_items.find(key) == m_items.end()) // first time
        {
            KVPair kv(key, value);
            m_list.push_front(kv);
            m_items[key] = m_list.begin();
        }
        else
        {
            update(key);
            auto foundItr = m_items.find(key);
            foundItr->second->value = value;
        }
    }

    int m_capacity;
    unordered_map<int,list<KVPair>::iterator> m_items;  // key to item
    list<KVPair> m_list; // list of all items. Head holds beginning
};

int main()
{
     LRUCache obj (2);
      obj.put(1,1);
      assert(obj.get(1) == 1);
      obj.put(2,2);
      assert(obj.get(2) == 2);
      obj.put(3,3);
      assert(obj.get(1) == -1);

      assert(obj.get(2) == 2);
      assert(obj.get(3) == 3);

      obj.put(4, 4);
      assert(obj.get(2) == -1);
      assert(obj.get(3) == 3);
      assert(obj.get(4) == 4);
      
      LRUCache obj2(2);
      assert(obj2.get(2) == -1);
      obj2.put(2,6);
      assert(obj2.get(1) == -1);
      assert(obj2.get(2) == 6);

       obj2.put(1,5);
       obj2.put(1,2);
        assert(obj2.get(1) == 2);
       assert(obj2.get(2) == 6);
}
