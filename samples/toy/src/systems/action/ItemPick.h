#ifndef HOPE_SAMPLES_TOY_systems_action_ItemPick_H
#define HOPE_SAMPLES_TOY_systems_action_ItemPick_H

#include "../Entities.h"

#include <grid/PathCrawler.h>
#include <console.h>
#include "../Components.h"

#include "./TheGrid.h"


class ItemPickActionSystem : public AbstractActionSystem< ItemPickActionComponent > {
	std::function<void(ItemPickActionComponent*, EntityId)> processComponent_callback;
	

public:
	ItemPickActionSystem() :
		processComponent_callback(std::bind(&ItemPickActionSystem::processComponent, this, std::placeholders::_1, std::placeholders::_2)) {
	}

	void process() {
		Components::foreach<ItemPickActionComponent>(processComponent_callback);
	}

	void processComponent(ItemPickActionComponent* dataItemTransfert, EntityId to_id) {
		auto dataAction = Components::get<ActionComponent>(to_id);

		ItemId item_id = dataItemTransfert->item_id;
		auto fromBagComponent = Components::get<ItemBagComponent>(dataItemTransfert->from_id);
		auto toBagComponent = Components::get<ItemBagComponent>(to_id);
	
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

	void attachTo(EntityId agent_id, ItemId item_id, EntityId to_id) {
		Components::attach<ActionComponent>(agent_id);
		auto Action = Components::attach<ItemPickActionComponent>(agent_id);

		Action->item_id = item_id;
		Action->from_id = to_id;
	}
};


namespace systems {
namespace action {

	ItemPickActionSystem ItemPick;

}
}

#endif /* HOPE_SAMPLES_TOY_systems_action_ItemPick_H */