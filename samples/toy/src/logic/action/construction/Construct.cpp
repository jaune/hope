#include "./Construct.h"

#include "../../../Components.h"

namespace logic {
	namespace action {
		namespace construction {
			namespace Construct {

				logic::action::Status process(EntityId actor_id, const Options& options, State& state) {
					auto from_c = Components::find<LaborComponent>(actor_id);
					if (from_c == NULL) {
//						hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
						return logic::action::FAILURE;
					}

					auto to_c = Components::find<LaborComponent>(options.task_id);
					if (to_c == NULL) {
//						hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
						return logic::action::FAILURE;
					}

					if (from_c->labor < 1) {
//						hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
						return logic::action::FAILURE;
					}

					from_c->labor--;
					to_c->labor++;

//					hope::console::log("action ::: SUCCESS (%s: %d)", __FILE__, __LINE__);
					// dataAction->status = ActionComponent::Status::SUCCESS;
					return logic::action::SUCCESS;
				}

			}
		}
	}
}
