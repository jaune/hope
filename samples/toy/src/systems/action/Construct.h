#ifndef HOPE_SAMPLES_TOY_systems_ConstructAction_H
#define HOPE_SAMPLES_TOY_systems_ConstructAction_H

#include "../../Entities.h"

#include <grid/PathCrawler.h>
#include <console.h>
#include "../../Components.h"

#include "./AbstractActionSystem.h"


class ConstructActionSystem : public AbstractActionSystem< ConstructActionComponent > {
	std::function<void(ConstructActionComponent*, EntityId)> processComponent_callback;

public:
	ConstructActionSystem();
	
	void process();

	void processComponent(ConstructActionComponent* dataConstrcut, EntityId from_id);

	void attachTo(EntityId agent_id, EntityId task_id);
};



namespace systems {
	namespace action {
		
		static ConstructActionSystem Construct;


	}
}

#endif /* HOPE_SAMPLES_TOY_systems_ConstructAction_H */