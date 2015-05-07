#ifndef HOPE_SAMPLES_TOY_Entities_H
#define HOPE_SAMPLES_TOY_Entities_H

#include "./Components.h"
#include "./EntityManager.h"

class Entities {
	static EntityManager* getManager() {
		static EntityManager* manager = NULL;

		if (manager == NULL) {
			manager = new EntityManager();
		}
		return manager;
	}


public:
	static EntityId create() {
		return getManager()->create();
	}

	static bool testComponentMask(EntityId eid, ComponentMask cid){
		return getManager()->testComponentMask(eid, cid);
	}

	static void attachComponent(EntityId eid, ComponentMask cid){
		getManager()->attachComponent(eid, cid);
	}

	static void detachComponent(EntityId eid, ComponentMask cid){
		getManager()->detachComponent(eid, cid);
	}

	static void destroy(EntityId id) {
		Components::detachAll(id);
		getManager()->destroy(id);
	}

	static void findByComponentMask(ComponentMask mask, std::vector<EntityId>& result) {
		getManager()->findByComponentMask(mask, result);
	}
	

	template<class T>
	static EntityId findFirstWith() {
		return Components::findFirstEntityId<T>();
	}

	static EntityId findNearestStoreFromAgent(EntityId agent_id) {
		return Entities::findFirstWith<StorageComponent>();
	}
};





#endif /* HOPE_SAMPLES_TOY_Entities_H */