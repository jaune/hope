#include "./ItemGive.h"

ItemGiveActionSystem::ItemGiveActionSystem() :
processComponent_callback(std::bind(&ItemGiveActionSystem::processComponent, this, std::placeholders::_1, std::placeholders::_2)) {
}

void ItemGiveActionSystem::process() {
	Components::foreach<ItemGiveActionComponent>(processComponent_callback);
}

void ItemGiveActionSystem::processComponent(ItemGiveActionComponent* dataItemGive, EntityId from_id) {
	auto dataAction = Components::get<ActionComponent>(from_id);

	ItemId item_id = dataItemGive->item_id;
	auto fromBagComponent = Components::get<ItemBagComponent>(from_id);
	auto toBagComponent = Components::get<ItemBagComponent>(dataItemGive->to_id);

	if (fromBagComponent->items.getItemQuantity(item_id) < 1){
		hope::console::log("action ::: FAILURE (%s: %d)", __FILE__, __LINE__);
		dataAction->status = ActionComponent::Status::FAILURE;
		return;
	}

	fromBagComponent->items.decrementItemQuantity(item_id);
	toBagComponent->items.incrementItemQuantity(item_id);

	hope::console::log("action ::: SUCCESS (%s: %d)", __FILE__, __LINE__);
	dataAction->status = ActionComponent::Status::SUCCESS;
}

void ItemGiveActionSystem::attachTo(EntityId agent_id, ItemId item_id, EntityId to_id) {
	Components::attach<ActionComponent>(agent_id);
	auto Action = Components::attach<ItemGiveActionComponent>(agent_id);

	Action->item_id = item_id;
	Action->to_id = to_id;
}

