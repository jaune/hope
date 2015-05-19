#ifndef HOPE_SAMPLES_TOY_LOGIC_Deposit_H
#define HOPE_SAMPLES_TOY_LOGIC_Deposit_H

#include "../types.h"
#include "./location.h"

namespace logic {
	namespace deposit {

		EntityId findNearest(ItemId item_id, EntityId to_id);

		EntityId create(const hope::grid::Location& location, ItemId item_id);
	}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_Deposit_H */