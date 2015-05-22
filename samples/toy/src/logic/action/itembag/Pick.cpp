#include "./Pick.h"

#include "../../../Components.h"

#include <console.h>

namespace logic {
	namespace action {
		namespace itembag {
			namespace Pick {

				logic::action::Status process(EntityId actor_id, const Options& options, State& state) {
					ItemId item_id = options.item_id;
					auto fromBagComponent = Components::get<ItemBagComponent>(options.from_id);
					auto toBagComponent = Components::get<ItemBagComponent>(actor_id);

					if (fromBagComponent->items.getItemQuantity(item_id) < 1){
						hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
						return logic::action::FAILURE;
					}

					fromBagComponent->items.decrementItemQuantity(item_id);
					toBagComponent->items.incrementItemQuantity(item_id);

					hope::console::log("action ::: SUCCESS (%s: %d)", __FILE__, __LINE__);
					return logic::action::SUCCESS;
				}

			}
		}
	}
}
