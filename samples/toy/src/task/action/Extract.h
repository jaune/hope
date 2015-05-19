#ifndef HOPE_SAMPLES_TOY_task_action_Extract_H
#define HOPE_SAMPLES_TOY_task_action_Extract_H

#include "../../systems/action/GoToAdjacent.h"
#include "../../systems/action/Extract.h"
#include "../../systems/action/ItemGive.h"
#include "../../logic/deposit.h"

namespace task {

	const TaskType ACTION_EXTRACT = 0x102;

	namespace action {

		struct Extract {

			static void attachAction(EntityId task_id, EntityId agent_id) {
				auto Task = Components::get<ExtractTaskComponent>(task_id);
				auto Plan = Components::get<PlanComponent>(agent_id);
				auto Action = Components::find<ActionComponent>(agent_id);

				if (Action != NULL) {
					return;
				}

				if (Plan->size == 0){
					Plan->size = 4;
				}

				if (Task->from_id == 0) {
					Task->from_id = logic::deposit::findNearest(Task->item_id, Task->to_id);
				}

				Task->from_level = 0;

				switch (Plan->step)
				{
				case 0:
					systems::action::GoToAdjacent.attachTo(agent_id, Task->from_id);
					break;
				case 1:
					systems::action::Extract.attachTo(agent_id, Task->from_id, Task->from_level);
					break;
				case 2:
					systems::action::GoToAdjacent.attachTo(agent_id, Task->to_id);
					break;
				case 3:
					systems::action::ItemGive.attachTo(agent_id, Task->item_id, Task->to_id);
					break;
				default:
					hope::console::log("MISSING STEP %s: %d", __FILE__, __LINE__);
					break;
				}
			}

		};


	}
}

#endif /* HOPE_SAMPLES_TOY_task_action_Extract_H */