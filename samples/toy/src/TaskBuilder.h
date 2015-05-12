#ifndef HOPE_SAMPLES_TOY_TaskBuilder_H
#define HOPE_SAMPLES_TOY_TaskBuilder_H

#include "task/action/Construct.h"
#include "task/action/Extract.h"
#include "task/action/ItemTransfert.h"

class TaskBuilder {

	EntityId createVoidTask(EntityId parent_id) {
		EntityId id = Entities::create();

		auto c = Components::attach<TaskComponent>(id);
		
		c->label = "VoidTask";
		setParent(c, parent_id);

		return id;
	}

	EntityId createItemTransfertTask(ItemId item_id, EntityId parent_id, EntityId to_id) {
		EntityId id = Entities::create();

		auto c = Components::attach<TaskComponent>(id);
		c->type = task::ACTION_ITEM_TRANSFERT;
		c->label = "ItemTransfertTask";
		setParent(c, parent_id);

		auto itt = Components::attach<ItemTransfertTaskComponent>(id);
		itt->item_id = item_id;
		itt->to_id = to_id;
				
		return id;
	}

	EntityId createAddLaborToTask(EntityId parent_id, EntityId to_id) {
		EntityId id = Entities::create();
		
		auto c = Components::attach<TaskComponent>(id);
		c->label = "AddLaborToTask";
		c->type = task::ACTION_CONSTRUCT;
		setParent(c, parent_id);
		
		auto altt = Components::attach<ConstructTaskComponent>(id);
		altt->task_id = to_id;

		return id;
	}
	

	void setParent(TaskComponent* c, EntityId parent_id){
		auto parent_c = Components::get<TaskComponent>(parent_id);

		c->parent = parent_id;
		c->level = parent_c->level + 1;
		parent_c->childrenTotal++;
	}

public:


	EntityId createConstructionTask(const asset::fbs::ConstructionRecipe* recipe, TaskPriority priority, hope::grid::Location& location) {
		EntityId id = Entities::create();

		Components::attach<LocationComponent>(id)->position.set(location);
		Components::attach<ItemBagComponent>(id);
		Components::attach<LaborComponent>(id);
		
		auto t = Components::attach<TaskComponent>(id);
		t->label = "ConstructionTask";
		t->priority = priority;
		t->level = 0;

		auto c = Components::attach<ConstructionTaskComponent>(id);
		c->recipe = recipe;

		EntityId g0 = createVoidTask(id);
		auto g0_c = Components::get<TaskComponent>(g0);


		for (auto it = c->recipe->items()->begin(); it != c->recipe->items()->end(); ++it) {
			ItemId item_id = it->item_id();

			for (ItemQuantity i = 0; i < it->quantity(); ++i) {
				EntityId newTask = createItemTransfertTask(item_id, g0, id);

				Components::attach<DoableComponent>(newTask);
			}
		}

		EntityId g1 = createVoidTask(id);
		auto g1_c = Components::get<TaskComponent>(g1);

		for (ItemQuantity i = 0; i < c->recipe->labor(); ++i) {
			createAddLaborToTask(g1, id);
		}

		g0_c->next = g1;
		g1_c->previous = g0;

		return id;
	}




};


#endif /* HOPE_SAMPLES_TOY_TaskBuilder_H */