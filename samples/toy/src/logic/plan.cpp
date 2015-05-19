#include "./plan.h"
#include "./location.h"

#include "../task/action/Construct.h"
#include "../task/action/ItemTransfert.h"
#include "../task/action/Extract.h"


namespace logic {
	namespace plan {


		void attachAction(EntityId task_id, EntityId agent_id) {
			auto task_c = Components::get<TaskComponent>(task_id);

			switch (task_c->type) {
			case task::ACTION_ITEM_TRANSFERT:
				task::action::ItemTransfert::attachAction(task_id, agent_id);
				break;
			case task::ACTION_EXTRACT:
				task::action::Extract::attachAction(task_id, agent_id);
				break;
			case task::ACTION_CONSTRUCT:
				task::action::Construct::attachAction(task_id, agent_id);
				break;
			}
		}

		void attachAction(){
			std::vector<EntityId> result;

			Entities::findByComponentMask(PlanComponent::COMPONENT_MASK, result);

			for (auto it = result.begin(); it != result.end(); ++it){
				EntityId agent_id = *it;
				auto plan_c = Components::get<PlanComponent>(*it);

				if (plan_c->type == logic::plan::extract::PLAN_TYPE){
					logic::plan::extract::attachAction(agent_id);
				}
				else if (plan_c->type == logic::plan::store::PLAN_TYPE) {
					logic::plan::store::attachAction(agent_id);
				}
				else {
					attachAction(plan_c->task_id, agent_id);
				}				
			}
		}
	}
}
