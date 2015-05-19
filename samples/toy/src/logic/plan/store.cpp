#include "./store.h"

#include "../../Components.h"
#include <console.h>

#include "../../systems/action/GoToAdjacent.h"
#include "../../systems/action/ItemPick.h"
#include "../../systems/action/ItemGive.h"

namespace logic {
	namespace plan {
		namespace store {

			void step(EntityId agent_id){
				auto plan_c = Components::get<PlanComponent>(agent_id);

				plan_c->step++;

				if (plan_c->step > 3) {
					Components::detach<PlanComponent>(agent_id);
				}
			}

			void assign(EntityId agent_id, EntityId storage_id, EntityId machine_id, ItemId item_id) {
				auto plan_c = Components::attach<PlanComponent>(agent_id);

				plan_c->status = plan_c->IN_PROGRESS;
				plan_c->step = 0;
				plan_c->task_id = 0;
				plan_c->size = 0;
				plan_c->type = PLAN_TYPE;
				plan_c->options.store.machine_id = machine_id;
				plan_c->options.store.storage_id = storage_id;
				plan_c->options.store.item_id = item_id;
			}

			void attachAction(EntityId agent_id) {
				auto Action = Components::find<ActionComponent>(agent_id);

				if (Action != NULL) {
					return;
				}

				auto plan_c = Components::get<PlanComponent>(agent_id);
				EntityId machine_id = plan_c->options.store.machine_id;
				EntityId storage_id = plan_c->options.store.storage_id;
				ItemId item_id = plan_c->options.store.item_id;

				switch (plan_c->step)
				{
				case 0:
					systems::action::GoToAdjacent.attachTo(agent_id, machine_id);
					break;
				case 1:
					logic::action::machine::output::pick.attach(agent_id, item_id, machine_id);
					break;
				case 2:
					systems::action::GoToAdjacent.attachTo(agent_id, storage_id);
					break;
				case 3: {
					systems::action::ItemGive.attachTo(agent_id, item_id, storage_id);
					break;
				}
				default:
					hope::console::log("MISSING STEP %s: %d", __FILE__, __LINE__);
					plan_c->status = plan_c->FAILURE;
					break;
				}
			}

		}
	}
}

