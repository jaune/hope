#include "./extract.h"

#include "../../Components.h"
#include <console.h>

#include "../../systems/action/GoToAdjacent.h"
#include "../../systems/action/Extract.h"
#include "../../systems/action/ItemBagGive.h"

namespace logic {
	namespace plan {
		namespace extract {

			void step(EntityId agent_id){
				auto plan_c = Components::get<PlanComponent>(agent_id);

				plan_c->step++;

				if (plan_c->step > 3) {
					Components::detach<PlanComponent>(agent_id);
				}
			}

			void assign(EntityId agent_id, EntityId storage_id, EntityId deposit_id) {
				auto plan_c = Components::attach<PlanComponent>(agent_id);

				plan_c->status = plan_c->IN_PROGRESS;
				plan_c->step = 0;
				plan_c->task_id = 0;
				plan_c->size = 0;
				plan_c->type = PLAN_TYPE;
				plan_c->options.extract.deposit_id = deposit_id;
				plan_c->options.extract.storage_id = storage_id;
			}

			void attachAction(EntityId agent_id) {
				auto Action = Components::find<ActionComponent>(agent_id);

				if (Action != NULL) {
					return;
				}

				auto plan_c = Components::get<PlanComponent>(agent_id);
				EntityId deposit_id = plan_c->options.extract.deposit_id;
				EntityId storage_id = plan_c->options.extract.storage_id;

				switch (plan_c->step)
				{
				case 0:
					systems::action::GoToAdjacent.attachTo(agent_id, deposit_id);
					break;
				case 1:
					systems::action::Extract.attachTo(agent_id, deposit_id, 0);
					break;
				case 2:
					systems::action::GoToAdjacent.attachTo(agent_id, storage_id);
					break;
				case 3: {
					auto deposit_c = Components::get<DepositComponent>(deposit_id);
					systems::action::ItemBagGive.attachTo(agent_id, deposit_c->item_id, storage_id);
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

