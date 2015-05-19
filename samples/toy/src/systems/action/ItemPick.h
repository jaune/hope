#ifndef HOPE_SAMPLES_TOY_systems_action_ItemPick_H
#define HOPE_SAMPLES_TOY_systems_action_ItemPick_H

#include "../../Entities.h"

#include <grid/PathCrawler.h>
#include <console.h>
#include "../../Components.h"
#include "./AbstractActionSystem.h"


class ItemPickActionSystem : public AbstractActionSystem< ItemPickActionComponent > {
	std::function<void(ItemPickActionComponent*, EntityId)> processComponent_callback;
	

public:
	ItemPickActionSystem();

	void process();

	void processComponent(ItemPickActionComponent* dataItemTransfert, EntityId to_id);

	void attachTo(EntityId agent_id, ItemId item_id, EntityId to_id);
};


namespace systems {
namespace action {

	static ItemPickActionSystem ItemPick;

}
}

#endif /* HOPE_SAMPLES_TOY_systems_action_ItemPick_H */