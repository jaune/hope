#include "./extract.h"

#include "../../Components.h"
#include <console.h>

#include "../../logic/action.h"


namespace logic {
	namespace plan {
		namespace extract {

			logic::plan::Status step(EntityId agent_id){
				auto plan_c = Components::get<PlanComponent>(agent_id);

				attachAction(agent_id);

				plan_c->step++;

				if (plan_c->step > 3) {
					return logic::plan::Status::SUCCESS;
				}

				return logic::plan::Status::IN_PROGRESS;
			}

			void assign(EntityId agent_id, EntityId storage_id, EntityId deposit_id) {
				auto plan_c = Components::attach<PlanComponent>(agent_id);

				plan_c->step = 0;
				plan_c->task_id = 0;
				plan_c->size = 0;
				plan_c->type = PLAN_TYPE;
				plan_c->options.extract.deposit_id = deposit_id;
				plan_c->options.extract.storage_id = storage_id;
			}

			void attachAction(EntityId agent_id) {
				auto Actor = Components::get<ActorComponent>(agent_id);

				auto plan_c = Components::get<PlanComponent>(agent_id);
				EntityId deposit_id = plan_c->options.extract.deposit_id;
				EntityId storage_id = plan_c->options.extract.storage_id;

				switch (plan_c->step)
				{
				case 0: {
					logic::action::GoToAdjacent::Options opt;
					opt.to_id = deposit_id;
					Actor->action = logic::action::create(opt);
				}
// systems::action::GoToAdjacent.attachTo(agent_id, deposit_id);
					break;
				case 1: {
					logic::action::deposit::Extract::Options opt;
					opt.from_id = deposit_id;
					opt.from_level = 0;
					Actor->action = logic::action::create(opt);
				}
// systems::action::Extract.attachTo(agent_id, deposit_id, 0);
					break;
				case 2:{
					logic::action::GoToAdjacent::Options opt;
					opt.to_id = storage_id;
					Actor->action = logic::action::create(opt);
				}
// systems::action::GoToAdjacent.attachTo(agent_id, storage_id);
					break;
				case 3: {
					auto deposit_c = Components::get<DepositComponent>(deposit_id);

					logic::action::itembag::Give::Options opt;
					opt.item_id = deposit_c->item_id;
					opt.to_id = storage_id;
					Actor->action = logic::action::create(opt);
//  systems::action::ItemBagGive.attachTo(agent_id, deposit_c->item_id, storage_id);
					break;
				}
				default:
//					hope::console::log("MISSING STEP %s: %d", __FILE__, __LINE__);
//					plan_c->status = plan_c->FAILURE;
					break;
				}
			}

		}
	}
}

