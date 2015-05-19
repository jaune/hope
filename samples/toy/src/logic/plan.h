#ifndef HOPE_SAMPLES_TOY_LOGIC_PLAN_H
#define HOPE_SAMPLES_TOY_LOGIC_PLAN_H

#include "../types.h"

#include "./plan/extract.h"
#include "./plan/store.h"


namespace logic {
	namespace plan {

		union Options {
			logic::plan::extract::Options extract;
			logic::plan::store::Options store;
		};

		void attachAction(EntityId task_id, EntityId agent_id);
		void attachAction();
	}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_PLAN_H */