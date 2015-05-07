#ifndef HOPE_SAMPLES_TOY_systems_task_ItemTransfert_H
#define HOPE_SAMPLES_TOY_systems_task_ItemTransfert_H

#include "../action/GoToAdjacent.h"
#include "../action/ItemPick.h"
#include "../action/ItemGive.h"

class ItemTransfertTaskSystem {

	void attachAction(EntityId task_id) {
		auto ItemTransfert = Components::get<ItemTransfertTaskComponent>(task_id);
		auto AttachToAgent = Components::get<AttachToAgentComponent>(task_id);
		auto Plan = Components::get<PlanComponent>(AttachToAgent->agent);
		auto Action = Components::find<ActionComponent>(AttachToAgent->agent);

		if (Action != NULL) {
			return;
		}

		if (Plan->size == 0){
			Plan->size = 4;
		}
				
		if (ItemTransfert->from_id == 0) {
			ItemTransfert->from_id = Entities::findNearestStoreFromAgent(AttachToAgent->agent);
		}
		
		switch (Plan->step)
		{
		case 0:
			systems::action::GoToAdjacent.attachTo(AttachToAgent->agent, ItemTransfert->from_id);
			break;
		case 1:
			systems::action::ItemPick.attachTo(AttachToAgent->agent, ItemTransfert->item_id, ItemTransfert->from_id);
			break;
		case 2:
			systems::action::GoToAdjacent.attachTo(AttachToAgent->agent, ItemTransfert->to_id);
			break;
		case 3:
			systems::action::ItemGive.attachTo(AttachToAgent->agent, ItemTransfert->item_id, ItemTransfert->to_id);
			break;
		default:
			hope::console::log("MISSING STEP %s: %d", __FILE__, __LINE__);
			break;
		}
	}

public:
	void attachAction() {
		std::vector<EntityId> result;

		Entities::findByComponentMask(ItemTransfertTaskComponent::COMPONENT_MASK | AttachToAgentComponent::COMPONENT_MASK, result);

		for (auto it = result.begin(); it != result.end(); ++it){
			attachAction(*(it));
		}
	}
	
};



namespace systems {
namespace task {
	ItemTransfertTaskSystem ItemTransfert;
}
}

#endif /* HOPE_SAMPLES_TOY_systems_task_ItemTransfertTask_H */