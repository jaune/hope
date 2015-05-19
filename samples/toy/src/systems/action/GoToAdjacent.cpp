#include "./GoToAdjacent.h"

GoToAdjacentActionSystem::GoToAdjacentActionSystem() :
processComponent_callback(std::bind(&GoToAdjacentActionSystem::processComponent, this, std::placeholders::_1, std::placeholders::_2)) {
}

void GoToAdjacentActionSystem::process() {
	Components::foreach<GoToAdjacentActionComponent>(processComponent_callback);
}

void GoToAdjacentActionSystem::processComponent(GoToAdjacentActionComponent* dataGoTo, EntityId agentid) {
	auto dataLocation = Components::get<LocationComponent>(agentid);
	auto dataAction = Components::get<ActionComponent>(agentid);

	if (dataAction->status == ActionComponent::Status::NONE) {
		auto crawler = systems::TheGrid()->findShortestPathToAdjacent(dataLocation->position, dataGoTo->to_id);

		if (crawler == NULL) {
			hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
			dataAction->status = ActionComponent::Status::FAILURE;
			return;
		}
		dataGoTo->crawler = crawler;
	}
	else if (dataAction->status != ActionComponent::Status::IN_PROGRESS) {
		return;
	}

	if (!dataGoTo->crawler->empty()) {
		if (dataGoTo->crawler->isValid()) {
			dataGoTo->crawler->pop(dataLocation->position);
		}
		else {
			delete dataGoTo->crawler;
			dataGoTo->crawler = NULL;

			hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
			dataAction->status = ActionComponent::Status::FAILURE;
			return;
		}
	}

	if (dataGoTo->crawler->empty()) {
		delete dataGoTo->crawler;
		dataGoTo->crawler = NULL;

		hope::console::log("action ::: SUCCESS (%s: %d)", __FILE__, __LINE__);
		dataAction->status = ActionComponent::Status::SUCCESS;
		return;
	}

	// hope::console::log("action ::: IN_PROGRESS (%s: %d)", __FILE__, __LINE__);
	dataAction->status = ActionComponent::Status::IN_PROGRESS;
}

void GoToAdjacentActionSystem::attachTo(EntityId agent_id, EntityId to_id) {
	Components::attach<ActionComponent>(agent_id);
	auto Action = Components::attach<GoToAdjacentActionComponent>(agent_id);

	Action->to_id = to_id;
}
