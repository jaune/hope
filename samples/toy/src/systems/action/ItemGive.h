#ifndef HOPE_SAMPLES_TOY_systems_action_ItemGive_H
#define HOPE_SAMPLES_TOY_systems_action_ItemGive_H

#include "../../Entities.h"

#include <grid/PathCrawler.h>
#include <console.h>
#include "../../Components.h"
#include "./AbstractActionSystem.h"


class ItemGiveActionSystem : public AbstractActionSystem< ItemGiveActionComponent > {
	std::function<void(ItemGiveActionComponent*, EntityId)> processComponent_callback;
	

public:
	ItemGiveActionSystem();

	void process();

	void processComponent(ItemGiveActionComponent* dataItemGive, EntityId from_id);

	void attachTo(EntityId agent_id, ItemId item_id, EntityId to_id);
};


namespace systems {
namespace action {

	static ItemGiveActionSystem ItemGive;

}
}

#endif /* HOPE_SAMPLES_TOY_systems_action_ItemGive_H */