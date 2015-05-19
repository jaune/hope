#include "./Construct.h"



ConstructActionSystem::ConstructActionSystem() :
processComponent_callback(std::bind(&ConstructActionSystem::processComponent, this, std::placeholders::_1, std::placeholders::_2)) {
}

void ConstructActionSystem::process() {
	Components::foreach<ConstructActionComponent>(processComponent_callback);
}

void ConstructActionSystem::processComponent(ConstructActionComponent* dataConstrcut, EntityId from_id) {
	auto dataAction = Components::get<ActionComponent>(from_id);

	auto from_c = Components::find<LaborComponent>(from_id);
	if (from_c == NULL) {
		hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
		dataAction->status = ActionComponent::Status::FAILURE;
		return;
	}

	auto to_c = Components::find<LaborComponent>(dataConstrcut->task_id);
	if (to_c == NULL) {
		hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
		dataAction->status = ActionComponent::Status::FAILURE;
		return;
	}

	if (from_c->labor < 1) {
		hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
		dataAction->status = ActionComponent::Status::FAILURE;
		return;
	}

	from_c->labor--;
	to_c->labor++;

	hope::console::log("action ::: SUCCESS (%s: %d)", __FILE__, __LINE__);
	dataAction->status = ActionComponent::Status::SUCCESS;
}

void ConstructActionSystem::attachTo(EntityId agent_id, EntityId task_id) {
	Components::attach<ActionComponent>(agent_id);
	auto Action = Components::attach<ConstructActionComponent>(agent_id);

	Action->task_id = task_id;

}
