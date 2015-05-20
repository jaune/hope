#ifndef HOPE_SAMPLES_TOY_systems_Action_H
#define HOPE_SAMPLES_TOY_systems_Action_H

#include "./action/GoToAdjacent.h"
#include "./action/Extract.h"
#include "./action/ItemBagPick.h"
#include "./action/ItemBagGive.h"
#include "./action/Construct.h"
#include "./action/MachineOutputPick.h"

class ActionSystem {
public:

	void cleanup (){
		std::vector<EntityId> result;

		Entities::findByComponentMask(ActionComponent::COMPONENT_MASK, result);

		for (auto it = result.begin(); it != result.end(); ++it){
			cleanupComponent(*(it));
		}
	}

	void cleanupComponent(EntityId agentid) {
		auto action = Components::get<ActionComponent>(agentid);
	
		if (action->status == ActionComponent::Status::SUCCESS || action->status == ActionComponent::Status::FAILURE){
			Components::detach<ActionComponent>(agentid);
		}
	}

};



namespace systems {
	
	namespace Action {

		ActionSystem instance;

		inline void process() {
			systems::action::GoToAdjacent.process();
			systems::action::Extract.process();
			systems::action::ItemBagPick.process();
			systems::action::ItemBagGive.process();
			systems::action::MachineOutputPick.process();
			systems::action::Construct.process();
		}

		inline void cleanup() {
			systems::action::GoToAdjacent.cleanup();
			systems::action::Extract.cleanup();
			systems::action::ItemBagPick.cleanup();
			systems::action::ItemBagGive.cleanup();
			systems::action::MachineOutputPick.cleanup();
			systems::action::Construct.cleanup();

			instance.cleanup();
		}

	}

};

#endif /* HOPE_SAMPLES_TOY_systems_GoToAdjacentAction_H */