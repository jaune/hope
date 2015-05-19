#include "./Entities.h"
#include "./Components.h"




void Entities::destroy(EntityId id) {
	Components::detachAll(id);
	getManager()->destroy(id);
}


EntityId Entities::findNearestStorageFromAgent(EntityId agent_id) {
	return Components::findFirstEntityId<StorageComponent>();
}
