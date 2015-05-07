#ifndef HOPE_AI_SYSTEM_H
#define HOPE_AI_SYSTEM_H

#include "Agent.h"
#include <ai/plan/PlanTable.h>
#include <ai/plan/Step.h>

namespace hope {
namespace ai {



	class System {
	public:
		::hope::ai::plan::StepTable actionTable;
		::hope::ai::plan::PlanTable planTable;

		std::vector<condition::Condition*> conditions;
		std::vector<const char*> needs;
		
		System() :
			planTable(actionTable) {
		}


		::hope::ai::plan::NeedType createNeed(const char* label) {
			needs.push_back(label);

			return needs.size();
		}

		const condition::Condition* createCondition(const char* label) {
			// TODO LABEL !!!!
			condition::Condition * c = new condition::Condition();
			conditions.push_back(c);
			return c;
		}

	private:
		void setCurrentPlan(hope::ai::plan::NeedType needType, hope::ai::plan::NeedLevel level, Agent& agent) {
			
			std::vector<const hope::ai::plan::Plan*> plans;

			planTable.findPlans(plans, needType);

			// TODO choose plan

			if (plans.empty()) {
				agent.currentPlan = NULL;
				agent.currentPlanStep = hope::ai::plan::NEED_INVALID;
				agent.currentPlanLevel = 0;
			}
			else {
				agent.currentPlan = plans.front();
				agent.currentPlanStep = 0;
				agent.currentPlanLevel = level;
			}
		}

	public:
		const ::hope::ai::plan::Step* nextStep(::hope::ai::Agent& agent) {
			hope::ai::plan::NeedType needType;
			hope::ai::plan::NeedLevel needLevel;

			agent.getNeediest(needType, needLevel);

			if (agent.currentPlan == NULL) {
				setCurrentPlan(needType, needLevel, agent);
			}
			else {
				if (needLevel > agent.currentPlanLevel) {
					setCurrentPlan(needType, needLevel, agent);
				}
				else {
					agent.currentPlanStep++;
				}
			}

			return agent.getCurrentStepAction();
		}
	};




} /* namespace ai */
} /* namespace hope */


#endif /* HOPE_AI_SYSTEM_H */