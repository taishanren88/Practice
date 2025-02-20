#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

struct Object {
    Object(int ik, int iv):
    key(ik), val(iv), frequency(1)
     {

    }
    int key;
    int val;
    int frequency;
};
class LFUCache {
public:
    LFUCache(int capacity)
    :m_capacity(capacity) {
        
    }
    
    int get(int key) {
        // move the item from this frequency to the next frequency
        // update the frequency
        auto foundItr = m_items.find(key);
        if (foundItr != m_items.end()) {
            foundItr->second->frequency++;
            m_frequencies[foundItr->second->frequency].splice(m_frequencies[foundItr->second->frequency].begin(),
                                         m_frequencies[foundItr->second->frequency -1], foundItr->second);
            return foundItr->second->val;
        }
        return -1;

    }
    
    void put(int key, int value) {
        // maintain a mapping of frequencies -> lru list
        // maintain a mapping of item -> list iterator
        // maintain map of list<Object> (key, value, frequency)
        
        // during insertion , put the key at  frequency of 1 (item doesn't exist)
        // if cache is at capacity then remove the item in the back at the frequnency list 
        // during set , do a get and update the value (item exists)
        if (get(key) != -1) {
            m_items[key]->val = value;
            return;
        }

        if (m_capacity == 0)
            return;

        if (m_items.size() == m_capacity) {
            int start = 1;
            auto entry = lfu();
            m_frequencies[entry.frequency].pop_back();
            m_items.erase(entry.key);
        }
        m_frequencies[1].push_front(Object(key, value));
        m_items[key] = m_frequencies[1].begin();

    }

    Object lfu() {
        int start = 1;
       while(true) {
            if (!m_frequencies[start].empty()) {
                auto entry = m_frequencies[start].back();
                return entry;
            } else {
                start++;
            }
        }
    }
private:
    unordered_map<int, std::list<Object>> m_frequencies;
    unordered_map<int, std::list<Object>::iterator> m_items;
    int m_capacity;
};

int main() {
    LFUCache cache(3);
    cache.put(1, 1);

    assert(cache.lfu().val == 1);
    assert(cache.get(1) == 1);

    cache.put(2, 3);
    assert(cache.get(2) == 3);
    assert(cache.get(3)  == -1);

    cache.put(3, 4);
    assert(cache.get(3)  == 4);
    cache.put(4,5);
    assert(cache.get(1) == -1);
    assert(cache.lfu().key == 4 && cache.lfu().val == 5);
    assert(cache.get(4) == 5 && cache.lfu().key == 2);
    assert(cache.get(2) == 3 && cache.lfu().key == 3);

    LFUCache cache2(0);
    cache2.put(0, 0);
    assert(cache2.get(0) == -1);
}
