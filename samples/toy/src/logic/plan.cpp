#include "./plan.h"
#include "./location.h"

#include "../task/action/Construct.h"
#include "../task/action/ItemTransfert.h"
#include "../task/action/Extract.h"
#include "../task/Task.h"


namespace logic {
	namespace plan {

		void step() {
			std::vector<EntityId> result;

			Entities::findByComponentMask(ActorComponent::COMPONENT_MASK, result);

			for (auto it = result.begin(); it != result.end(); ++it){
				EntityId agent_id = *it;
				ActorComponent* actor_c = Components::get<ActorComponent>(agent_id);

				if (actor_c->action.status == logic::action::SUCCESS || actor_c->action.status == logic::action::FAILURE) {
					PlanComponent* plan_c = Components::find<PlanComponent>(agent_id);

					bool has_plan = false;

					if (plan_c == NULL) {
						// try to create plan !
						{
							if (!has_plan) {
								has_plan = systems::Task.tryAssignPlan(agent_id);
							}

							if (!has_plan) {
								EntityId storage_id = Entities::findNearestStorageFromAgent(agent_id);
								auto storage_c = Components::get<StorageComponent>(storage_id);

								if (!has_plan) {
									has_plan = logic::storage::tryAssignStorePlan(storage_id, agent_id);
								}

								if (!has_plan) {
									has_plan = logic::storage::tryAssignExtractPlan(storage_id, agent_id);
								}
							}
						}
					}
				}

			}

			result.clear();

			Entities::findByComponentMask(ActorComponent::COMPONENT_MASK | PlanComponent::COMPONENT_MASK, result);

			for (auto it = result.begin(); it != result.end(); ++it){
				EntityId agent_id = *it;
				ActorComponent* actor_c = Components::get<ActorComponent>(agent_id);
				PlanComponent* plan_c = Components::get<PlanComponent>(agent_id);

				if (actor_c->action.status == logic::action::SUCCESS || actor_c->action.status == logic::action::FAILURE) {
					logic::plan::Status status = logic::plan::Status::NONE;

					switch (plan_c->type) {
					case logic::plan::extract::PLAN_TYPE:
						status = logic::plan::extract::step(agent_id);
						break;
					case logic::plan::store::PLAN_TYPE:
						status = logic::plan::store::step(agent_id);
						break;
					case logic::plan::task::PLAN_TYPE:
						status = systems::Task.stepPlan(agent_id);
						break;
					default:
						break;
					}

					if (status == logic::plan::SUCCESS || status == logic::plan::FAILURE) {
						Components::detach<PlanComponent>(agent_id);
					}
				}
			}
		}

	}
}
