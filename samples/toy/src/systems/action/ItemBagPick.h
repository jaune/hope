#ifndef HOPE_SAMPLES_TOY_systems_action_ItemBagPick_H
#define HOPE_SAMPLES_TOY_systems_action_ItemBagPick_H

#include "../../Entities.h"

#include <grid/PathCrawler.h>
#include <console.h>
#include "../../Components.h"
#include "./AbstractActionSystem.h"


class ItemBagPickActionSystem : public AbstractActionSystem< ItemBagPickActionComponent > {
	std::function<void(ItemBagPickActionComponent*, EntityId)> processComponent_callback;
	

public:
	ItemBagPickActionSystem();

	void process();

	void processComponent(ItemBagPickActionComponent* dataItemTransfert, EntityId to_id);

	void attachTo(EntityId agent_id, ItemId item_id, EntityId to_id);
};


namespace systems {
namespace action {

	static ItemBagPickActionSystem ItemBagPick;

}
}

#endif /* HOPE_SAMPLES_TOY_systems_action_ItemBagPick_H */