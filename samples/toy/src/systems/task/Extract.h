#ifndef HOPE_SAMPLES_TOY_systems_task_Extract_H
#define HOPE_SAMPLES_TOY_systems_task_Extract_H

#include "../action/GoToAdjacent.h"
#include "../action/Extract.h"
#include "../action/ItemGive.h"
#include "../Deposit.h"

class ExtractTaskSystem {

	void attachAction(EntityId task_id) {
		auto Task = Components::get<ExtractTaskComponent>(task_id);
		auto AttachToAgent = Components::get<AttachToAgentComponent>(task_id);
		auto Plan = Components::get<PlanComponent>(AttachToAgent->agent);
		auto Action = Components::find<ActionComponent>(AttachToAgent->agent);

		if (Action != NULL) {
			return;
		}

		if (Plan->size == 0){
			Plan->size = 4;
		}
				
		if (Task->from_id == 0) {
			Task->from_id = systems::Deposit.findNearest(Task->item_id, Task->to_id);
		}

		Task->from_level = 0;

		switch (Plan->step)
		{
		case 0:
			systems::action::GoToAdjacent.attachTo(AttachToAgent->agent, Task->from_id);
			break;
		case 1:
			systems::action::Extract.attachTo(AttachToAgent->agent, Task->from_id, Task->from_level);
			break;
		case 2:
			systems::action::GoToAdjacent.attachTo(AttachToAgent->agent, Task->to_id);
			break;
		case 3:
			systems::action::ItemGive.attachTo(AttachToAgent->agent, Task->item_id, Task->to_id);
			break;
		default:
			hope::console::log("MISSING STEP %s: %d", __FILE__, __LINE__);
			break;
		}
	}

public:
	void attachAction() {
		std::vector<EntityId> result;

		Entities::findByComponentMask(ExtractTaskComponent::COMPONENT_MASK | AttachToAgentComponent::COMPONENT_MASK, result);

		for (auto it = result.begin(); it != result.end(); ++it){
			attachAction(*(it));
		}
	}
	
};



namespace systems {
namespace task {
	ExtractTaskSystem Extract;
}
}

#endif /* HOPE_SAMPLES_TOY_systems_task_ItemTransfertTask_H */