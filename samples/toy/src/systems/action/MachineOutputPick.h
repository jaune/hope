#ifndef HOPE_SAMPLES_TOY_systems_action_MachineOutputPick_H
#define HOPE_SAMPLES_TOY_systems_action_MachineOutputPick_H

#include "../../Entities.h"

#include <grid/PathCrawler.h>
#include <console.h>
#include "../../Components.h"
#include "./AbstractActionSystem.h"


class MachineOutputPickActionSystem : public AbstractActionSystem< MachineOutputPickActionComponent > {
	std::function<void(MachineOutputPickActionComponent*, EntityId)> processComponent_callback;
	

public:
	MachineOutputPickActionSystem();

	void process();

	void processComponent(MachineOutputPickActionComponent* dataItemTransfert, EntityId to_id);

	void attachTo(EntityId agent_id, ItemId item_id, EntityId to_id);
};


namespace systems {
namespace action {

	static MachineOutputPickActionSystem MachineOutputPick;

}
}

#endif /* HOPE_SAMPLES_TOY_systems_action_MachineOutputPick_H */