#ifndef HOPE_SAMPLES_TOY_systems_Action_H
#define HOPE_SAMPLES_TOY_systems_Action_H

#include "./action/GoToAdjacent.h"
#include "./action/Extract.h"
#include "./action/ItemPick.h"
#include "./action/ItemGive.h"
#include "./action/Construct.h"


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
			systems::action::ItemPick.process();
			systems::action::ItemGive.process();
			systems::action::Construct.process();
		}

		inline void cleanup() {
			systems::action::GoToAdjacent.cleanup();
			systems::action::Extract.cleanup();
			systems::action::ItemPick.cleanup();
			systems::action::ItemGive.cleanup();
			systems::action::Construct.cleanup();

			instance.cleanup();
		}

	}

};

#endif /* HOPE_SAMPLES_TOY_systems_GoToAdjacentAction_H */