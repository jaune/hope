#ifndef HOPE_SAMPLES_TOY_systems_action_ItemBagGive_H
#define HOPE_SAMPLES_TOY_systems_action_ItemBagGive_H

#include "../../Entities.h"

#include <grid/PathCrawler.h>
#include <console.h>
#include "../../Components.h"
#include "./AbstractActionSystem.h"


class ItemBagGiveActionSystem : public AbstractActionSystem< ItemBagGiveActionComponent > {
	std::function<void(ItemBagGiveActionComponent*, EntityId)> processComponent_callback;
	

public:
	ItemBagGiveActionSystem();

	void process();

	void processComponent(ItemBagGiveActionComponent* dataItemBagGive, EntityId from_id);

	void attachTo(EntityId agent_id, ItemId item_id, EntityId to_id);
};


namespace systems {
namespace action {

	static ItemBagGiveActionSystem ItemBagGive;

}
}

#endif /* HOPE_SAMPLES_TOY_systems_action_ItemBagGive_H */