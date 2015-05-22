#include "./Extract.h"

#include "../../../Components.h"

namespace logic {
	namespace action {
		namespace deposit {
			namespace Extract {


				logic::action::Status process(EntityId actor_id, const Options& options, State& state) {
					auto fromDepositComponent = Components::get<DepositComponent>(options.from_id);
					auto toBagComponent = Components::get<ItemBagComponent>(actor_id);

					if (fromDepositComponent->getItemQuantity(options.from_level) < 1){
//						hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
						return logic::action::FAILURE;
					}

					fromDepositComponent->decrementItemQuantity(options.from_level);
					toBagComponent->items.incrementItemQuantity(fromDepositComponent->item_id);

//					hope::console::log("action ::: SUCCESS (%s: %d)", __FILE__, __LINE__);
					return logic::action::SUCCESS;
				}

			}
		}
	}
}