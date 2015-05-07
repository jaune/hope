#ifndef HOPE_SAMPLES_TOY_command_StorageSetItemRequestQuantity_H
#define HOPE_SAMPLES_TOY_command_StorageSetItemRequestQuantity_H

#include "../Entities.h"

namespace command {

	struct StorageSetItemRequestQuantity {
		EntityId storage_id;
		ItemId item_id;
		ItemQuantity quantity;
	};	

}

#endif /* HOPE_SAMPLES_TOY_command_StorageSetItemRequestQuantity_H */