#ifndef HOPE_SAMPLES_TOY_system_Task_H
#define HOPE_SAMPLES_TOY_system_Task_H


#include <functional>
#include "../Entities.h"
#include "../Components.h"
#include "../TaskBuilder.h"
#include "../systems/TheGrid.h"

#include <console.h>
#include <core/core.h>

#include "./action/Construct.h"
#include "./action/ItemTransfert.h"
#include "./action/Extract.h"


#include "../logic/storage.h"
#include "../logic/plan/extract.h"
#include "../logic/plan/store.h"
#include "../logic/plan/task.h"

class TaskSystem {
	std::function<void(AgentComponent*, EntityId)> callback_processLazyAgentComponent;

private:
	void assignTask(EntityId task_id, EntityId agent_id) {
		Components::detach<DoableComponent>(task_id);
		auto plan = Components::attach<PlanComponent>(agent_id);

		plan->type = logic::plan::task::PLAN_TYPE;

		plan->task_id = task_id;
	}
public:
	


	void findFreeTask(std::vector<EntityId>& result) {
		std::vector<EntityId> candidates;

		Entities::findByComponentMask(TaskComponent::COMPONENT_MASK | DoableComponent::COMPONENT_MASK, candidates);

		for (auto it = candidates.begin(); it != candidates.end(); ++it) {
			TaskComponent* task = Components::find<TaskComponent>((*it));
			if (task->previous == 0) {
				result.push_back((*it));
			}
		}

		if (result.size() < 1) {
			return;
		}

		TaskComponent_LevelAndPriorityCompare compare;

		std::sort(result.begin(), result.end(), compare);
	}

	bool tryAssignPlan(EntityId agent_id){
		EntityId task_id = findFirstFreeTask();

		if (task_id == 0) {
			return false;
		}

		assignTask(task_id, agent_id);

		return true;
	}

	EntityId findFirstFreeTask() {

		std::vector<EntityId> result;

		findFreeTask(result);

		if (result.size() < 1) {
			return 0;
		}

		return result.front();
	}

	logic::plan::Status stepPlan(EntityId agent_id){
		auto actor_c = Components::get<ActorComponent>(agent_id);
		auto plan_c = Components::get<PlanComponent>(agent_id);

		EntityId task_id = plan_c->task_id;

		if (actor_c->action.status == logic::action::SUCCESS) {
			attachAction(agent_id);

			plan_c->step++;

			if (plan_c->step >= plan_c->size) {
				setTaskDone(task_id);
				hope::console::log("PLAN ::: SUCCESS task: #%d", task_id);

				return logic::plan::Status::SUCCESS;
			}
		}
		else if (actor_c->action.status == logic::action::FAILURE){
			Components::detach<DoableComponent>(task_id);
			hope::console::log("PLAN ::: FAILURE task: #%d", task_id);
			return logic::plan::Status::FAILURE;
		}

		return logic::plan::Status::IN_PROGRESS;
	}

	EntityId findFirstNearestFreeTask(EntityId from_id) {
		LocationComponent* l = Components::find<LocationComponent>(from_id);

		if (l == NULL) {
			return 0;
		}

		hope::grid::AABox box;
		box.set(l->position, 500, 500, 500, 500);


		std::vector<EntityId> candidates;
		std::vector<EntityId> result;

		Entities::findByComponentMask(TaskComponent::COMPONENT_MASK | LocationComponent::COMPONENT_MASK | DoableComponent::COMPONENT_MASK, candidates);

		for (auto it = candidates.begin(); it != candidates.end(); ++it) {
			LocationComponent* location = Components::find<LocationComponent>((*it));
			TaskComponent* task = Components::find<TaskComponent>((*it));

			if ((task->previous == 0) && box.contains(location->position)) {
				result.push_back((*it));
			}
		}

		if (result.size() < 1) {
			return 0;
		}


		TaskComponent_LevelAndPriorityCompare compare;

		std::sort(result.begin(), result.end(), compare);

		return result.front();
	}





	void setTaskDoable_callback(EntityId parent_id, TaskComponent* component, EntityId task_id){
		if (component->parent == parent_id) {
			setTaskDoable(task_id);
		}
	}

	void setTaskDoable(EntityId task_id){
		TaskComponent *next_c = Components::get<TaskComponent>(task_id);

		if (next_c->childrenTotal == 0) {
			Components::attach<DoableComponent>(task_id);
		}
		else {
			std::function<void(TaskComponent*, EntityId)> fn = std::bind(&TaskSystem::setTaskDoable_callback, this, task_id, std::placeholders::_1, std::placeholders::_2);
			Components::foreach<TaskComponent>(fn);
		}
	}

	void setTaskDone(EntityId task_id){
		TaskComponent *current_c = Components::get<TaskComponent>(task_id);

		if (current_c->next != 0) {
			TaskComponent *next_c = Components::get<TaskComponent>(current_c->next);
			next_c->previous = 0;
			setTaskDoable(current_c->next);
		}
		if (current_c->parent != 0){
			TaskComponent *parent_c = Components::get<TaskComponent>(current_c->parent);
			parent_c->childrenDone++;
			if (parent_c->childrenDone >= parent_c->childrenTotal) {
				setTaskDone(current_c->parent);
			}
		}


		auto ct_c = Components::find<ConstructionTaskComponent>(task_id);
		if (ct_c != NULL) {
			auto l_c = Components::find<LocationComponent>(task_id);

			switch (ct_c->recipe->id())
			{
			case 353441:
				systems::TheGrid()->setWall(l_c->position.x, l_c->position.y);
				break;
			case 574164:
				systems::TheGrid()->setFloor(l_c->position.x, l_c->position.y);
				break;
			default:
				break;
			}
		}
		Entities::destroy(task_id);
	}

	void cancelTask_callback(EntityId parent_id, TaskComponent* component, EntityId task_id){
		if (component->parent == parent_id) {
			cancelTask(task_id);
		}
	}

	void cancelTask(EntityId task_id){
		TaskComponent *current_c = Components::get<TaskComponent>(task_id);

		if (current_c->childrenTotal > 0) {
			std::function<void(TaskComponent*, EntityId)> fn = std::bind(&TaskSystem::cancelTask_callback, this, task_id, std::placeholders::_1, std::placeholders::_2);
			Components::foreach<TaskComponent>(fn);
		}

		Entities::destroy(task_id);
	}

	void attachAction(EntityId agent_id){
		

		PlanComponent* plan_c = Components::get<PlanComponent>(agent_id);
		auto task_c = Components::get<TaskComponent>(plan_c->task_id);
		

		switch (task_c->type) {
		case task::ACTION_ITEM_TRANSFERT:
			task::action::ItemTransfert::attachAction(plan_c->task_id, agent_id);
			break;
		case task::ACTION_EXTRACT:
			task::action::Extract::attachAction(plan_c->task_id, agent_id);
			break;
		case task::ACTION_CONSTRUCT:
			task::action::Construct::attachAction(plan_c->task_id, agent_id);
			break;
		}

	
	}

};


namespace systems {

	static TaskSystem Task;

};

#endif /* HOPE_SAMPLES_TOY_system_Task_H */