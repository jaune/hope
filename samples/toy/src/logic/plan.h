#ifndef HOPE_SAMPLES_TOY_LOGIC_PLAN_H
#define HOPE_SAMPLES_TOY_LOGIC_PLAN_H

#include "../types.h"

#include "./plan/extract.h"
#include "./plan/store.h"
#include "./plan/Status.h"

namespace logic {
	namespace plan {


		union Options {
			logic::plan::extract::Options extract;
			logic::plan::store::Options store;
		};

		
		void attachActionToBuzyActor();
		void attachPlanToLazyActor();

		void step();
	}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_PLAN_H */