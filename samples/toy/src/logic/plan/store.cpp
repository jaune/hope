#include "./store.h"

#include "../../Components.h"
#include <console.h>

#include "../../logic/action.h"

namespace logic {
	namespace plan {
		namespace store {

			logic::plan::Status step(EntityId agent_id){
				auto plan_c = Components::get<PlanComponent>(agent_id);

				attachAction(agent_id);

				plan_c->step++;

				if (plan_c->step > 3) {
					return logic::plan::Status::SUCCESS;
				}
				return logic::plan::Status::IN_PROGRESS;
			}

			void assign(EntityId agent_id, EntityId storage_id, EntityId machine_id, ItemId item_id) {
				auto plan_c = Components::attach<PlanComponent>(agent_id);

				plan_c->step = 0;
				plan_c->task_id = 0;
				plan_c->size = 0;
				plan_c->type = PLAN_TYPE;
				plan_c->options.store.machine_id = machine_id;
				plan_c->options.store.storage_id = storage_id;
				plan_c->options.store.item_id = item_id;
			}

			void attachAction(EntityId agent_id) {
				auto Actor = Components::get<ActorComponent>(agent_id);

				auto plan_c = Components::get<PlanComponent>(agent_id);
				EntityId machine_id = plan_c->options.store.machine_id;
				EntityId storage_id = plan_c->options.store.storage_id;
				ItemId item_id = plan_c->options.store.item_id;

				switch (plan_c->step)
				{
				case 0: {
					logic::action::GoToAdjacent::Options opt;
					opt.to_id = machine_id;
					Actor->action = logic::action::create(opt);
				}
				// systems::action::GoToAdjacent.attachTo(agent_id, machine_id);
					break;
				case 1: {
					logic::action::machine::OutputPick::Options opt;
					opt.item_id = item_id;
					opt.from_id = machine_id;
					Actor->action = logic::action::create(opt);
				}
//					systems::action::MachineOutputPick.attachTo(agent_id, item_id, machine_id);
					break;
				case 2: {
					logic::action::GoToAdjacent::Options opt;
					opt.to_id = storage_id;
					Actor->action = logic::action::create(opt);
				}
//					systems::action::GoToAdjacent.attachTo(agent_id, storage_id);
					break;
				case 3: {
					logic::action::itembag::Give::Options opt;
					opt.item_id = item_id;
					opt.to_id = storage_id;
					Actor->action = logic::action::create(opt);
					// systems::action::ItemBagGive.attachTo(agent_id, item_id, storage_id);
					break;
				}
				default:
					//hope::console::log("MISSING STEP %s: %d", __FILE__, __LINE__);
//					plan_c->status = plan_c->FAILURE;
					break;
				}
			}

		}
	}
}

