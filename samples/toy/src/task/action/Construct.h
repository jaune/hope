#ifndef HOPE_SAMPLES_TOY_task_action_Construct_H
#define HOPE_SAMPLES_TOY_task_action_Construct_H

#include "../../systems/action/GoToAdjacent.h"
#include "../../systems/action/Construct.h"

namespace task {

	const TaskType ACTION_CONSTRUCT = 0x101;

	namespace action {

		struct Construct {

			static void attachAction(EntityId task_id, EntityId agent_id) {
				auto Construct = Components::get<ConstructTaskComponent>(task_id);
				auto Plan = Components::get<PlanComponent>(agent_id);
				auto Action = Components::find<ActionComponent>(agent_id);

				if (Action != NULL) {
					return;
				}

				if (Plan->size == 0){
					Plan->size = 2;
				}

				switch (Plan->step)
				{
				case 0:
					systems::action::GoToAdjacent.attachTo(agent_id, Construct->task_id);
					break;
				case 1:
					systems::action::Construct.attachTo(agent_id, Construct->task_id);
					break;
				default:
					hope::console::log("MISSING STEP %s: %d", __FILE__, __LINE__);
					break;
				}
			}
		};

	}
}

#endif /* HOPE_SAMPLES_TOY_task_action_Construct_H */