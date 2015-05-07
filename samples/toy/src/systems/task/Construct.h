#ifndef HOPE_SAMPLES_TOY_systems_task_Construct_H
#define HOPE_SAMPLES_TOY_systems_task_Construct_H

#include "../action/GoToAdjacent.h"
#include "../action/Construct.h"

class ConstructTaskSystem {

	void attachAction(EntityId task_id) {
		auto Construct = Components::get<ConstructTaskComponent>(task_id);
		auto AttachToAgent = Components::get<AttachToAgentComponent>(task_id);
		auto Plan = Components::get<PlanComponent>(AttachToAgent->agent);
		auto Action = Components::find<ActionComponent>(AttachToAgent->agent);

		if (Action != NULL) {
			return;
		}

		if (Plan->size == 0){
			Plan->size = 2;
		}

		switch (Plan->step)
		{
		case 0:
			systems::action::GoToAdjacent.attachTo(AttachToAgent->agent, Construct->task_id);
			break;
		case 1:
			systems::action::Construct.attachTo(AttachToAgent->agent, Construct->task_id);
			break;
		default:
			hope::console::log("MISSING STEP %s: %d", __FILE__, __LINE__);
			break;
		}
	}

public:
	void attachAction() {
		std::vector<EntityId> result;

		Entities::findByComponentMask(ConstructTaskComponent::COMPONENT_MASK | AttachToAgentComponent::COMPONENT_MASK, result);

		for (auto it = result.begin(); it != result.end(); ++it){
			attachAction(*it);
		}
	}

};



namespace systems {
namespace task {
	ConstructTaskSystem Construct;
}
}

#endif /* HOPE_SAMPLES_TOY_systems_task_Construct_H */