#ifndef HOPE_SAMPLES_TOY_systems_ExtractAction_H
#define HOPE_SAMPLES_TOY_systems_ExtractAction_H

#include <grid/PathCrawler.h>
#include <console.h>
#include "../../Components.h"
#include "./AbstractActionSystem.h"

class ExtractActionSystem : public AbstractActionSystem< ExtractActionComponent > {
	std::function<void(ExtractActionComponent*, EntityId)> processComponent_callback;
	
public:
	ExtractActionSystem();

	void process();

	void processComponent(ExtractActionComponent* dataExtract, EntityId to_id);

	void attachTo(EntityId agent_id, EntityId from_id, DepositLevel from_level);
};



namespace systems {
namespace action {
	static ExtractActionSystem Extract;
}
}

#endif /* HOPE_SAMPLES_TOY_systems_ExtractAction_H */