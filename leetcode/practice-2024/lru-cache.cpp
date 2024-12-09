#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

struct KeyValue {
	KeyValue(int ikey, int ivalue)
		: key(ikey), value(ivalue) {

	}
	KeyValue(): KeyValue(0, 0) {
	}
	int key, value;
};

class LRUCache {
public:
	LRUCache(int capacity)
		: m_capacity(capacity) {
		// Maintain a list containing the ordering and the value
		// Maintain a map of key to the iterator
		// On get (move the entry to the top of the list)
		// On put , if entry exists, do a get , and hten update
		// On put , if entry does not exist, if at capacity, remove from bottom
		// ... then insert
	}

	int get(int key) {
		auto found = keys2Iterators.find(key);
		if (found != keys2Iterators.end()) {
			m_ordering.splice(m_ordering.begin(), m_ordering, found->second);
			return found->second->value;
		}
		return -1;
	}

	void put(int key, int value) {
		auto foundIterator = keys2Iterators.find(key);
		if (foundIterator != keys2Iterators.end()) {
			get(key);
			foundIterator->second->value = value;
		} else {
			if (m_ordering.size() == m_capacity) {
				keys2Iterators.erase(m_ordering.back().key);
				m_ordering.pop_back();
			}
			m_ordering.push_front(KeyValue(key,value));
			keys2Iterators[key] = m_ordering.begin();
		}
	}

	int m_capacity;
	std::list<KeyValue> m_ordering;
	unordered_map<int, std::list<KeyValue>::iterator> keys2Iterators;
};

int main() {

}