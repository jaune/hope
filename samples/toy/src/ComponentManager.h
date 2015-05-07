#ifndef HOPE_SAMPLES_TOY_ComponentManager_H
#define HOPE_SAMPLES_TOY_ComponentManager_H

#include "EntityManager.h"



template <class T>
class ComponentManager {

	typedef std::unordered_map<EntityId, T*> ComponentMap;

	ComponentMap components;

public:
	T* get(EntityId id) {
		T* c = find(id);
		assert(c != NULL);
		return c;
	}
	
	T* find(EntityId id) {
		auto it = components.find(id);

		if (it == components.end()) {
			return NULL;
		}

		return it->second;
	}

	T* attach(EntityId id) {
		T* c = find(id);
		assert(c == NULL);

		c = new T();

		components.insert(ComponentMap::value_type(id, c));
		Entities::attachComponent(id, T::COMPONENT_MASK);

		return c;
	}

	void detach(EntityId id) {
		auto it = components.find(id);

		if (it == components.end()) {
			return;
		}

		Entities::detachComponent(id, T::COMPONENT_MASK);
		delete it->second;
		components.erase(it);
	}

	void foreach(void(*callback)(T*, EntityId)) {
		for (auto it = components.begin(); it != components.end(); ++it){
			callback(it->second, it->first);
		}
	}

	void foreach(std::function <void(T*, EntityId)> callback) {
		for (auto it = components.begin(); it != components.end(); ++it){
			callback(it->second, it->first);
		}
	}

	EntityId findFirstEntityId() {
		auto it = components.begin();

		if (it == components.end()) {
			return 0;
		}		

		return it->first;
	}


};


#endif /* HOPE_SAMPLES_TOY_ComponentManager_H */