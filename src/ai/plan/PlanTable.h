#ifndef HOPE_AI_PLAN_PLAN_TABLE_H
#define HOPE_AI_PLAN_PLAN_TABLE_H

#include "Plan.h"
#include "./StepTable.h"

#include <stack>
#include <vector>

namespace hope {
namespace ai {
namespace plan {


	struct PlanTable {
		std::vector<const plan::Plan*> plans;

		const ::hope::ai::plan::StepTable& actionTable;

		PlanTable(const ::hope::ai::plan::StepTable& actionTable)
			: actionTable(actionTable) {

		}

		~PlanTable() {
			for (auto it = plans.begin(); it != plans.end(); ++it) {
				delete (*it);
			}
		}

		void addPlan(const plan::Plan* plan) {
			plans.push_back(plan);
		}
		
		void findPlans(std::vector<const plan::Plan*>& result, const ::hope::ai::plan::Step* finalAction) {
			std::stack<plan::Plan*> stackPlan;

			plan::Plan* currentPlan = new plan::Plan();
			currentPlan->actions.push_back(finalAction);

			stackPlan.push(currentPlan);

			while (!stackPlan.empty()) {
				currentPlan = stackPlan.top();
				stackPlan.pop();

				const ::hope::ai::plan::Step* nexAction = currentPlan->actions.back();

				if (nexAction->preconditions.empty()) {
					result.push_back(currentPlan);
					addPlan(currentPlan);
				}
				else {

					std::vector<const ::hope::ai::plan::Step *> candidates;
					actionTable.findWithAllPostcondition(candidates, nexAction->preconditions);

					for (auto it = candidates.begin(); it != candidates.end(); ++it) {
						plan::Plan* newPlan = new plan::Plan(*currentPlan);

						newPlan->actions.push_back((*it));

						stackPlan.push(newPlan);
					}
				}

			}
		}

		void findPlans(std::vector<const Plan*>& plans, NeedType need) {
			std::vector<const ::hope::ai::plan::Step *> finalActions;

			actionTable.find(finalActions, need);

			if (finalActions.empty()) {
				return;
			}

			for (auto it = finalActions.begin(); it != finalActions.end(); ++it) {
				findPlans(plans, (*it));
			}

		}

	};


} /* namespace plan */
} /* namespace ai */
} /* namespace hope */


#endif /* HOPE_AI_PLAN_PLAN_H */