#ifndef HOPE_SAMPLES_TOY_task_action_Extract_H
#define HOPE_SAMPLES_TOY_task_action_Extract_H

#include "../../logic/action/GoToAdjacent.h"
#include "../../logic/action/deposit/Extract.h"
#include "../../logic/action/itembag/Give.h"
#include "../../logic/deposit.h"

namespace task {

	const TaskType ACTION_EXTRACT = 0x102;

	namespace action {

		struct Extract {

			static void attachAction(EntityId task_id, EntityId agent_id) {
				auto Task = Components::get<ExtractTaskComponent>(task_id);
				auto Plan = Components::get<PlanComponent>(agent_id);
				auto Actor = Components::get<ActorComponent>(agent_id);

				if (Plan->size == 0){
					Plan->size = 4;
				}

				if (Task->from_id == 0) {
					Task->from_id = logic::deposit::findNearest(Task->item_id, Task->to_id);
				}

				Task->from_level = 0;

				switch (Plan->step)
				{
				case 0: {
					logic::action::GoToAdjacent::Options opt;
					opt.to_id = Task->from_id;
					Actor->action = logic::action::create(opt);
				}
				//	systems::action::GoToAdjacent.attachTo(agent_id, Task->from_id);
					break;
				case 1: {
					logic::action::deposit::Extract::Options opt;
					opt.from_id = Task->from_id;
					opt.from_level = Task->from_level;
					Actor->action = logic::action::create(opt);
				}
				//  systems::action::Extract.attachTo(agent_id, Task->from_id, Task->from_level);
					break;
				case 2: {
					logic::action::GoToAdjacent::Options opt;
					opt.to_id = Task->to_id;
					Actor->action = logic::action::create(opt);
				}
				// systems::action::GoToAdjacent.attachTo(agent_id, Task->to_id);
					break;
				case 3: {
					logic::action::itembag::Give::Options opt;
					opt.to_id = Task->to_id;
					opt.item_id = Task->item_id;
					Actor->action = logic::action::create(opt);
				}
				// systems::action::ItemBagGive.attachTo(agent_id, Task->item_id, Task->to_id);
					break;
				default:
//					hope::console::log("MISSING STEP %s: %d", __FILE__, __LINE__);
					break;
				}
			}

		};


	}
}

#endif /* HOPE_SAMPLES_TOY_task_action_Extract_H */