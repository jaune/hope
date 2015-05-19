#include "./Extract.h"

ExtractActionSystem::ExtractActionSystem() :
processComponent_callback(std::bind(&ExtractActionSystem::processComponent, this, std::placeholders::_1, std::placeholders::_2)) {
}

void ExtractActionSystem::process() {
	Components::foreach<ExtractActionComponent>(processComponent_callback);
}

void ExtractActionSystem::processComponent(ExtractActionComponent* dataExtract, EntityId to_id) {
	auto dataAction = Components::get<ActionComponent>(to_id);
	auto fromDepositComponent = Components::get<DepositComponent>(dataExtract->from_id);
	auto toBagComponent = Components::get<ItemBagComponent>(to_id);

	if (fromDepositComponent->getItemQuantity(dataExtract->from_level) < 1){
		hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
		dataAction->status = ActionComponent::Status::FAILURE;
		return;
	}

	fromDepositComponent->decrementItemQuantity(dataExtract->from_level);
	toBagComponent->items.incrementItemQuantity(fromDepositComponent->item_id);

	hope::console::log("action ::: SUCCESS (%s: %d)", __FILE__, __LINE__);
	dataAction->status = ActionComponent::Status::SUCCESS;
}

void ExtractActionSystem::attachTo(EntityId agent_id, EntityId from_id, DepositLevel from_level) {
	Components::attach<ActionComponent>(agent_id);
	auto Action = Components::attach<ExtractActionComponent>(agent_id);

	Action->from_id = from_id;
	Action->from_level = from_level;
}
