#ifndef HOPE_AI_PLAN_STEP_H
#define HOPE_AI_PLAN_STEP_H

#include <vector>

#include "../condition/Condition.h"

namespace hope {
namespace ai {
namespace plan {

		typedef int32_t NeedLevel;

		typedef uint16_t NeedType;
		const NeedType NEED_INVALID = 0;

		struct Effect {
			NeedType type;
			NeedLevel level;
		};

		typedef int32_t StepIndex;


		struct Step {
			StepIndex index;
			std::vector < const condition::Condition* > postconditions;
			std::vector < const condition::Condition* > preconditions;
			std::vector < const Effect > effects;

			bool hasPrecondition(const condition::Condition* condition) const {
				for (auto condIt = preconditions.begin(); condIt != preconditions.end(); ++condIt) {
					if ((*condIt) == condition) {
						return true;
					}
				}
				return false;
			}
			
			bool hasPostcondition(const condition::Condition* condition) const {
				for (auto condIt = postconditions.begin(); condIt != postconditions.end(); ++condIt) {
					if ((*condIt) == condition) {
						return true;
					}
				}
				return false;
			}
		};


} /* namespace plan */
} /* namespace ai */
} /* namespace hope */



#endif /* HOPE_AI_PLAN_STEP_H */