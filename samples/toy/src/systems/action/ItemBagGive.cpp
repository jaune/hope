#include "./ItemBagGive.h"

ItemBagGiveActionSystem::ItemBagGiveActionSystem() :
processComponent_callback(std::bind(&ItemBagGiveActionSystem::processComponent, this, std::placeholders::_1, std::placeholders::_2)) {
}

void ItemBagGiveActionSystem::process() {
	Components::foreach<ItemBagGiveActionComponent>(processComponent_callback);
}

void ItemBagGiveActionSystem::processComponent(ItemBagGiveActionComponent* dataItemBagGive, EntityId from_id) {
	auto dataAction = Components::get<ActionComponent>(from_id);

	ItemId item_id = dataItemBagGive->item_id;
	auto fromBagComponent = Components::get<ItemBagComponent>(from_id);
	auto toBagComponent = Components::get<ItemBagComponent>(dataItemBagGive->to_id);

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

void ItemBagGiveActionSystem::attachTo(EntityId agent_id, ItemId item_id, EntityId to_id) {
	Components::attach<ActionComponent>(agent_id);
	auto Action = Components::attach<ItemBagGiveActionComponent>(agent_id);

	Action->item_id = item_id;
	Action->to_id = to_id;
}

