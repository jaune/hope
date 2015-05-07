#ifndef HOPE_WORLD_STORE_H
#define HOPE_WORLD_STORE_H

#include <set>

namespace hope {
namespace world {

template< typename T >
class Store {
public:
	T* pool;
	int32_t pool_cursor;
	int32_t pool_size;

	std::set<T*> release_queue;

public:
	Store() {
		pool_cursor = 0;
		pool_size = 50;
		pool = new T[pool_size];
	}

	~Store() {
		delete[] pool;
	}

	T* allocate() {
		if (pool_cursor >= pool_size) {
			pool_size += 50;
			T* newPool = new T[pool_size];
			std::memcpy(newPool, pool, (pool_size-50) * sizeof(T));
			delete[] pool;
			pool = newPool;
		}

		T* item = &pool[pool_cursor];

		pool_cursor++;

		return item;
	}

	void release(T* item) {
		release_queue.insert(item);
	}

	void cleanup() {
		
		for (auto it = release_queue.begin(); it != release_queue.end(); ++it) {
			T* item = (*it);

			pool_cursor--;
			
			*item = pool[pool_cursor];
		}

		release_queue.clear();
	}


};


} /* namespace world */
} /* namespace hope */

#endif /* HOPE_WORLD_STORE_H */ 
