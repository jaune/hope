#ifndef HOPE_AI_PLAN_PLAN_H
#define HOPE_AI_PLAN_PLAN_H

#include <vector>
#include "./Step.h"

namespace hope {
namespace ai {
namespace plan {

	class Plan {
	public:
		std::vector<const Step*> actions;
	};


} /* namespace plan */
} /* namespace ai */
} /* namespace hope */


#endif /* HOPE_AI_PLAN_PLAN_H */