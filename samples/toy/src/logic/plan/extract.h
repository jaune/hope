#ifndef HOPE_SAMPLES_TOY_LOGIC_PLAN_EXTRACT_H
#define HOPE_SAMPLES_TOY_LOGIC_PLAN_EXTRACT_H

#include "../../types.h"
#include "./Status.h"

namespace logic {
	namespace plan {
		namespace extract {

			const PlanType PLAN_TYPE = 0x01;

			struct Options {
				EntityId deposit_id;
				EntityId storage_id;
			};

			void assign(EntityId agent_id, EntityId storage_id, EntityId deposit_id);
			void attachAction(EntityId agent_id);

			logic::plan::Status step(EntityId agent_id);
		}
	}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_PLAN_EXTRACT_H */