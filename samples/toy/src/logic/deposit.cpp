#include "./deposit.h"

namespace logic {
	namespace deposit {

		EntityId findNearest(ItemId item_id, EntityId to_id){
			return Components::findFirstEntityId<DepositComponent>();
		}

		EntityId create(const hope::grid::Location& location, ItemId item_id) {
			EntityId id = Entities::create();

			Components::attach<LocationComponent>(id)->position.set(location);
			Components::attach<DepositComponent>(id)->item_id = item_id;

			return id;
		}
	}
}

