#ifndef HOPE_SAMPLES_TOY_task_action_ItemTransfert_H
#define HOPE_SAMPLES_TOY_task_action_ItemTransfert_H

#include "../../types.h"
#include "../../Components.h"
#include "../../Entities.h"

#include "../../systems/action/GoToAdjacent.h"
#include "../../systems/action/ItemPick.h"
#include "../../systems/action/ItemGive.h"

namespace task {

	const TaskType ACTION_ITEM_TRANSFERT = 0x103;

	namespace action {

		struct ItemTransfert {
			static void attachAction(EntityId task_id, EntityId agent_id) {
				auto ItemTransfert = Components::get<ItemTransfertTaskComponent>(task_id);
				auto Plan = Components::get<PlanComponent>(agent_id);
				auto Action = Components::find<ActionComponent>(agent_id);

				if (Action != NULL) {
					return;
				}

				if (Plan->size == 0){
					Plan->size = 4;
				}

				if (ItemTransfert->from_id == 0) {
					ItemTransfert->from_id = Entities::findNearestStorageFromAgent(agent_id);
				}

				switch (Plan->step)
				{
				case 0:
					systems::action::GoToAdjacent.attachTo(agent_id, ItemTransfert->from_id);
					break;
				case 1:
					systems::action::ItemPick.attachTo(agent_id, ItemTransfert->item_id, ItemTransfert->from_id);
					break;
				case 2:
					systems::action::GoToAdjacent.attachTo(agent_id, ItemTransfert->to_id);
					break;
				case 3:
					systems::action::ItemGive.attachTo(agent_id, ItemTransfert->item_id, ItemTransfert->to_id);
					break;
				default:
					hope::console::log("MISSING STEP %s: %d", __FILE__, __LINE__);
					break;
				}
			}

		};
	}
}

#endif /* HOPE_SAMPLES_TOY_task_action_ItemTransfert_H */