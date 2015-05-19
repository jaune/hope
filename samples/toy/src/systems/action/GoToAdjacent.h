#ifndef HOPE_SAMPLES_TOY_systems_GoToAdjacentAction_H
#define HOPE_SAMPLES_TOY_systems_GoToAdjacentAction_H

#include <grid/PathCrawler.h>
#include <console.h>
#include "../../Components.h"
#include "../TheGrid.h"
#include "./AbstractActionSystem.h"

class GoToAdjacentActionSystem : public AbstractActionSystem< GoToAdjacentActionComponent > {

	std::function<void(GoToAdjacentActionComponent*, EntityId)> processComponent_callback;
	

public:
	GoToAdjacentActionSystem();

	void process();

	void processComponent(GoToAdjacentActionComponent* dataGoTo, EntityId agentid);

	void attachTo(EntityId agent_id, EntityId to_id);

};


namespace systems {
namespace action {

	static GoToAdjacentActionSystem GoToAdjacent;

}
}

#endif /* HOPE_SAMPLES_TOY_systems_GoToAdjacentAction_H */