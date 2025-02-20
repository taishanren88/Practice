#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

struct Item {
	Item(int aKey, int aValue) {
		key = aKey;
		value = aValue;
	}

	int key;
	int value;
};
class LRUCache {
public:
    LRUCache(int aCapacity) {
    	capacity = aCapacity;
    	// Maintain an LRU list (which has lru at the end and most recently used at the beginning)
    	// Maintain a map of key -> list pointer
    	// ON put, update the list pointer, update the value if necessary
    	// On get, retrieve the value, and also update the pointer to the beginning of the list (using splice)
    	// list.splice(list.begin(), list, current pointer)
    	// update
    }
    
    int get(int key) {
    	const auto foundItemItr = keys2Iterator.find(key);
        if (foundItemItr != keys2Iterator.end()) {
        	m_ordering.splice(m_ordering.begin(), m_ordering, foundItemItr->second);
        } else {
        	return -1;
        }
        keys2Iterator[key] = m_ordering.begin();
        return m_ordering.begin()->value;
    }
    
    void put(int key, int value) {
    	auto found = keys2Iterator.find(key);
    	if (found != keys2Iterator.end()) {
    		// update
    		get(key);
    		m_ordering.begin()->value = value;
    		return;
    	}
    	if (m_ordering.size() == capacity) {
    		// remove if at capacity
    		auto lastItem = m_ordering.back();
 			m_ordering.pop_back();
 			keys2Iterator.erase(lastItem.key);
    	}
    	// insert
    	m_ordering.push_front(Item(key, value));
    	keys2Iterator[key] = m_ordering.begin();
    }

    // For debug
    Item getFront() {
    	return *(m_ordering.begin());
    }

    int size() {
    	assert(m_ordering.size() == keys2Iterator.size());
    	return keys2Iterator.size();
    }
    unordered_map<int, std::list<Item>::iterator>  keys2Iterator;
    std::list<Item> m_ordering;
    int capacity;
};


int main() {
	LRUCache lrucache(3);
	lrucache.put(1, 2);
	assert(lrucache.size() == 1);
	assert(lrucache.getFront().value == 2);

	lrucache.put(2, 2);
	assert(lrucache.size() == 2 && lrucache.getFront().key == 2);

	lrucache.get(1);
	assert(lrucache.size() == 2 && lrucache.getFront().key == 1);

	lrucache.put(3, 3);
	lrucache.put(4,4);
	assert(lrucache.getFront().key == 4);
	assert(lrucache.get(2) == -1);

	lrucache.get(1);
	assert(lrucache.get(1) == 2);

	lrucache.get(3);
	assert(lrucache.get(3) == 3);
}