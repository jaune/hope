#include "./OutputPick.h"

#include "../../../Components.h"

namespace logic {
	namespace action {
		namespace machine {
			namespace OutputPick {

				logic::action::Status process(EntityId actor_id, const Options& options, State& state) {
					const EntityId from_id = options.from_id;
					const ItemId item_id = options.item_id;

					auto fromBagComponent = Components::get<MachineComponent>(from_id);
					auto toBagComponent = Components::get<ItemBagComponent>(actor_id);

					if (fromBagComponent->output.getItemQuantity(item_id) < 1){
//						hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
						return logic::action::FAILURE;
					}

					fromBagComponent->output.decrementItemQuantity(item_id);
					toBagComponent->items.incrementItemQuantity(item_id);

//					hope::console::log("action ::: SUCCESS (%s: %d)", __FILE__, __LINE__);
					return logic::action::SUCCESS;
				}

			}
		}
	}
}