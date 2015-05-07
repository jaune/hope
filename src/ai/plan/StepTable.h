#ifndef HOPE_AI_PLAN_STEP_TABLE_H
#define HOPE_AI_PLAN_STEP_TABLE_H

#include "./Step.h"

#include <vector>
#include <unordered_map>

namespace hope {
namespace ai {
namespace plan {


		struct StepTable {

			typedef std::unordered_multimap<const condition::Condition*, const Step*>::value_type StepByConditionTypeValue;
			typedef std::unordered_multimap < NeedType, const Step* > StepByNeedMap;
			typedef std::unordered_multimap<const condition::Condition*, const Step*> StepByConditionMap;

			std::vector<Step*> steps;
			StepByNeedMap steps_by_need;
			StepByConditionMap steps_by_postconditions;
			StepByConditionMap steps_by_preconditions;

			~StepTable() {
				for (auto it = steps.begin(); it != steps.end(); ++it) {
					delete (*it);
				}
			}
			
			StepIndex add(const Step& action);
			void findWithAllPostcondition(std::vector<const Step *>& result, const std::vector<const condition::Condition*>& conditions) const;
			void findWithAllPrecondition(std::vector<const Step *>& result, const std::vector<const condition::Condition*>& conditions) const;
			void findWithPostcondition(std::vector<const Step *>& actions, const condition::Condition* condition) const;
			void findWithPrecondition(std::vector<const Step *>& actions, const condition::Condition* condition) const;
			void find(std::vector<const Step *>& actions, NeedType need) const;

		};



} /* namespace plan */
} /* namespace ai */
} /* namespace hope */


#endif /* HOPE_AI_ACTION_ACTION_TABLE_H */