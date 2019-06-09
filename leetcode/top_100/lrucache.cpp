#include <iostream>
#include <unordered_map>
#include <list>
#include <iterator>
#include <cassert>

using namespace std;


class LRUCache
{
public:
    LRUCache(int capacity)
    :m_capacity(capacity) {

    }
    void put(int key, int value) {
        int dummy;
        // If it already exists
        if (get(key, dummy)) {

            keyMapping[key]->value = value;
            return;
        }

        if (keyMapping.size() == m_capacity) {
            auto last = m_ordering.back();
            auto keyOldest = last.key;
            keyMapping.erase(keyOldest);
            m_ordering.pop_back();
        }

        m_ordering.push_front(KeyValuePair(key, value));
        keyMapping[key] = m_ordering.begin();
    }
    bool get(int key, int& oValue) {
        auto found = keyMapping.find(key);
        if (found != keyMapping.end())
        {
            // update the position of this element
            m_ordering.splice(m_ordering.begin(), m_ordering, found->second);
            keyMapping[key] = m_ordering.begin();
            oValue = keyMapping[key]->value;
            return true;
        }
        return false;
    }
    int getFrontKey() {
        return m_ordering.begin()->value;
    }
private:
    int m_capacity;
    struct KeyValuePair
    {
        KeyValuePair(int iKey, int iValue)
        :key(iKey), value(iValue)
        {

        }
        int key;
        int value;
    };
    std::list<KeyValuePair> m_ordering; 
    std::unordered_map<int, std::list<KeyValuePair>::iterator> keyMapping;

};

int main()
{
    LRUCache lru(3);
    lru.put(1, 1);
    int value;
    assert(lru.get(1, value) && value == 1);
    lru.put(2, 2);
    assert(lru.get(2, value) && value == 2);
    assert(lru.getFrontKey() == 2);
    lru.get(1, value);
    assert(lru.getFrontKey() == 1);
    lru.put(3,3);
     assert(lru.getFrontKey() == 3);
   lru.put(4,4);
    assert(lru.getFrontKey() == 4);
    lru.get(1, value);
     assert(lru.getFrontKey() == 1);


    //

    


    LRUCache lru2(2);
    assert(!lru2.get(2, value));
    lru2.put(2,6);
    assert(!lru2.get(1, value));
    lru2.put(1,5);
    lru2.put(1,2);
    assert(lru2.get(1, value) && value == 2);
    assert(lru2.get(2, value) && value == 6);


//     //

LRUCache lru3(2);
    lru3.put(2, 1);
    lru3.put(1,1);
    lru3.put(2,3);
    lru3.put(4,1);
    assert(!lru3.get(1, value));
    assert(lru3.get(2, value) && value == 3);
    return 0;
}