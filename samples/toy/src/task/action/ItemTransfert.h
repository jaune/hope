#ifndef HOPE_SAMPLES_TOY_task_action_ItemTransfert_H
#define HOPE_SAMPLES_TOY_task_action_ItemTransfert_H

#include "../../types.h"
#include "../../Components.h"
#include "../../Entities.h"

#include "../../logic/action.h"

namespace task {

	const TaskType ACTION_ITEM_TRANSFERT = 0x103;

	namespace action {

		struct ItemTransfert {
			static void attachAction(EntityId task_id, EntityId agent_id) {
				auto ItemTransfert = Components::get<ItemTransfertTaskComponent>(task_id);
				auto Plan = Components::get<PlanComponent>(agent_id);
				auto Actor = Components::get<ActorComponent>(agent_id);

				if (Plan->size == 0){
					Plan->size = 4;
				}

				if (ItemTransfert->from_id == 0) {
					ItemTransfert->from_id = Entities::findNearestStorageFromAgent(agent_id);
				}

				switch (Plan->step)
				{
				case 0: {
					logic::action::GoToAdjacent::Options opt;
					opt.to_id = ItemTransfert->from_id;
					Actor->action = logic::action::create(opt);
				}
				// systems::action::GoToAdjacent.attachTo(agent_id, ItemTransfert->from_id);
					break;
				case 1: {
					logic::action::itembag::Pick::Options opt;
					opt.item_id = ItemTransfert->item_id;
					opt.from_id = ItemTransfert->from_id;
					Actor->action = logic::action::create(opt);
				}
				// systems::action::ItemBagPick.attachTo(agent_id, ItemTransfert->item_id, ItemTransfert->from_id);
					break;
				case 2: {
					logic::action::GoToAdjacent::Options opt;
					opt.to_id = ItemTransfert->to_id;
					Actor->action = logic::action::create(opt);
				}
				// systems::action::GoToAdjacent.attachTo(agent_id, ItemTransfert->to_id);
					break;
				case 3: {
					logic::action::itembag::Give::Options opt;
					opt.to_id = ItemTransfert->to_id;
					opt.item_id = ItemTransfert->item_id;
					Actor->action = logic::action::create(opt);
				}
				// systems::action::ItemBagGive.attachTo(agent_id, ItemTransfert->item_id, ItemTransfert->to_id);
					break;
				default:
//					hope::console::log("MISSING STEP %s: %d", __FILE__, __LINE__);
					break;
				}
			}

		};
	}
}

#endif /* HOPE_SAMPLES_TOY_task_action_ItemTransfert_H */