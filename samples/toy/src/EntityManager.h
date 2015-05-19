#ifndef HOPE_SAMPLES_TOY_EntityManager_H
#define HOPE_SAMPLES_TOY_EntityManager_H

#include "./types.h"

typedef uint32_t ComponentMask;

#include <map>
#include <unordered_map>

class EntityManager {

	uint16_t counter;

	typedef std::unordered_map<EntityId, ComponentMask> ComponentMaskMap;

	ComponentMaskMap entities;

public:
	EntityManager() :
		counter(0x42) {
	}

	EntityId create() {
		EntityId id = counter++;

		id = id << 1;		

		entities.insert(ComponentMaskMap::value_type(id, 0));

		return id;
	}

	void attachComponent(EntityId eid, ComponentMask cid){
		auto it = entities.find(eid);

		if (it == entities.end()) {
			return;
		}

		it->second |= cid;
	}

	void detachComponent(EntityId eid, ComponentMask cid){
		auto it = entities.find(eid);

		if (it == entities.end()) {
			return;
		}

		it->second |= cid;
		it->second ^= cid;
	}

	void destroy(EntityId id) {
		auto it = entities.find(id);

		if (it == entities.end()) {
			return;
		}

		entities.erase(it);
	}

	bool testComponentMask(EntityId eid, ComponentMask mask){
		auto it = entities.find(eid);

		if (it == entities.end()) {
			return false;
		}

		return (it->second & mask) == mask;
	}

	void findByComponentMask(ComponentMask mask, std::vector<EntityId>& result) const {
		for (auto it = entities.begin(); it != entities.end(); ++it) {
			if ((it->second & mask) == mask) {
				result.push_back(it->first);
			}
		}
	}
};

#endif /* HOPE_SAMPLES_TOY_EntityManager_H */