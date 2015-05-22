#ifndef HOPE_SAMPLES_TOY_LOGIC_STORAGE_H
#define HOPE_SAMPLES_TOY_LOGIC_STORAGE_H

#include "../types.h"
#include "./location.h"

#include "../logic/plan/extract.h"
#include "../logic/plan/store.h"

namespace logic {
namespace storage {
	
	EntityId create(const hope::grid::Location& location);

	void findInArea(EntityId storage_id, ComponentMask mask, std::vector<EntityId>& result);

	bool tryAssignStorePlan(EntityId storage_id, EntityId agent_id);

	EntityId tryAssignExtractPlan(EntityId storage_id, EntityId agent_id);

}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_STORAGE_H */