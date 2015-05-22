#ifndef HOPE_SAMPLES_TOY_LOGIC_PLAN_STORE_H
#define HOPE_SAMPLES_TOY_LOGIC_PLAN_STORE_H

#include "../../types.h"
#include "./Status.h"

namespace logic {
	namespace plan {
		namespace store {

			const PlanType PLAN_TYPE = 0x02;

			struct Options {
				EntityId machine_id;
				EntityId storage_id;
				ItemId item_id;
			};

			void assign(EntityId agent_id, EntityId storage_id, EntityId machine_id, ItemId item_id);
			void attachAction(EntityId agent_id);

			logic::plan::Status step(EntityId agent_id);
		}
	}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_PLAN_STORE_H */