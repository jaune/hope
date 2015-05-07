#ifndef HOPE_AI_AGENT_H
#define HOPE_AI_AGENT_H

#include "./plan/Plan.h"

#include <unordered_map>

namespace hope {
namespace ai {

struct Agent {
	std::unordered_map<hope::ai::plan::NeedType, hope::ai::plan::NeedLevel> needs;

	const hope::ai::plan::Plan* currentPlan;
	hope::ai::plan::NeedLevel currentPlanLevel;
	size_t currentPlanStep;

	Agent() {
		currentPlan = NULL;
		currentPlanStep = 0;
		currentPlanLevel = 0;
	}

	void getNeediest(::hope::ai::plan::NeedType& type, ::hope::ai::plan::NeedLevel& level) const {
		::hope::ai::plan::NeedType typeFound = hope::ai::plan::NEED_INVALID;
		::hope::ai::plan::NeedLevel levelFound = 0;

		for (auto it = needs.begin(); it != needs.end(); it++) {
			if (it->second > levelFound) {
				typeFound = it->first;
				levelFound = it->second;
			}
		}

		type = typeFound;
		level = levelFound;
	}

	::hope::ai::plan::NeedType getNeediest() const {
		::hope::ai::plan::NeedType type;
		::hope::ai::plan::NeedLevel level;
		
		getNeediest(type, level);

		return type;
	}


	const hope::ai::plan::Step* getCurrentStepAction() {
		if (currentPlan == NULL) {
			return NULL;
		}

		if (currentPlanStep < currentPlan->actions.size()) {
			return currentPlan->actions[currentPlan->actions.size() - currentPlanStep - 1];
		}
		else {
			currentPlan = NULL;
			currentPlanStep = 0;
			currentPlanLevel = 0;
			return NULL;
		}
	}
};

} /* ai */
} /* hope */

#endif /* HOPE_AI_AGENT_H */