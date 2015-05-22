#include "./Give.h"

#include "../../../Components.h"

namespace logic {
	namespace action {
		namespace itembag {
			namespace Give {

				logic::action::Status process(EntityId actor_id, const Options& options, State& state) {
					ItemId item_id = options.item_id;
					auto fromBagComponent = Components::get<ItemBagComponent>(actor_id);
					auto toBagComponent = Components::get<ItemBagComponent>(options.to_id);

					if (fromBagComponent->items.getItemQuantity(item_id) < 1){
//						hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
						return logic::action::FAILURE;
					}

					fromBagComponent->items.decrementItemQuantity(item_id);
					toBagComponent->items.incrementItemQuantity(item_id);

//					hope::console::log("action ::: SUCCESS (%s: %d)", __FILE__, __LINE__);
					return logic::action::SUCCESS;
				}

			}
		}
	}
}
