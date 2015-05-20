#include "./MachineOutputPick.h"

MachineOutputPickActionSystem::MachineOutputPickActionSystem() :
	processComponent_callback(std::bind(&MachineOutputPickActionSystem::processComponent, this, std::placeholders::_1, std::placeholders::_2)) {
}

void MachineOutputPickActionSystem::process() {
	Components::foreach<MachineOutputPickActionComponent>(processComponent_callback);
}

void MachineOutputPickActionSystem::processComponent(MachineOutputPickActionComponent* dataItemTransfert, EntityId to_id) {
	auto dataAction = Components::get<ActionComponent>(to_id);

	ItemId item_id = dataItemTransfert->item_id;
	auto fromBagComponent = Components::get<MachineComponent>(dataItemTransfert->from_id);
	auto toBagComponent = Components::get<ItemBagComponent>(to_id);

	if (fromBagComponent->output.getItemQuantity(item_id) < 1){
		hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
		dataAction->status = ActionComponent::Status::FAILURE;
		return;
	}

	fromBagComponent->output.decrementItemQuantity(item_id);
	toBagComponent->items.incrementItemQuantity(item_id);

	hope::console::log("action ::: SUCCESS (%s: %d)", __FILE__, __LINE__);
	dataAction->status = ActionComponent::Status::SUCCESS;
}

void MachineOutputPickActionSystem::attachTo(EntityId agent_id, ItemId item_id, EntityId to_id) {
	Components::attach<ActionComponent>(agent_id);
	auto Action = Components::attach<MachineOutputPickActionComponent>(agent_id);

	Action->item_id = item_id;
	Action->from_id = to_id;
}
