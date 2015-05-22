#ifndef HOPE_SAMPLES_TOY_Components_H
#define HOPE_SAMPLES_TOY_Components_H

#include "./ComponentManager.h"
#include "./ItemBag.h"
#include <grid/PathCrawler.h>

#include "asset/ConstructionRecipeTable_generated.h"
#include "./logic/plan.h"


typedef int LaborQuantity;

struct GoToComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 0);

	hope::grid::PathCrawler* crawler;

	GoToComponent() :
		crawler(NULL) {
	}
};

struct LocationComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 1);

	hope::grid::Location position;
};



struct ItemBagComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 2);

	ItemBag items;
};

struct AgentComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 3);

	const char* label;

	AgentComponent() :
		label(NULL) {
	}
};


struct StorageComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 4);

	ItemBag request_quantities;

	ItemQuantity max;

	StorageComponent() : max(0) {
	}
};



struct TaskComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 5);
	
	const char* label;

	EntityId parent;
	EntityId next;
	EntityId previous;
	
	int level;
	int priority;

	size_t childrenTotal;
	size_t childrenDone;

	TaskType type;

	TaskComponent() :
		label("<unknow>"),

		type(0),

		parent(0),
		next(0),
		previous(0),

		childrenTotal(0),
		childrenDone(0),

		level(0),
		priority(0) {
	}
};




struct ConstructionTaskComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 6);

	const asset::fbs::ConstructionRecipe* recipe;
};

struct ItemTransfertTaskComponent{
	static const ComponentMask COMPONENT_MASK = (1 << 7);

	ItemId item_id;
	EntityId to_id;
	EntityId from_id;
};

struct ConstructTaskComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 8);

	EntityId task_id;
};

struct DoableComponent{
	static const ComponentMask COMPONENT_MASK = (1 << 9);
};





struct PlanComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 11);

	typedef int16_t StepIndex;

	StepIndex step;
	StepIndex size;
	EntityId task_id;

	PlanType type;

	
	logic::plan::Options options;

	PlanComponent() :
		step(0),
		size(0) {
	}
};

struct LaborComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 12);

	LaborQuantity labor;
};




struct DepositComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 13);

	ItemId item_id;
	std::vector<ItemQuantity> item_quantities;

	ItemQuantity getItemQuantity(DepositLevel level) {
		if (level >= item_quantities.size()){
			return 0;
		}

		return item_quantities.at(level);
	}

	void decrementItemQuantity(DepositLevel level) {
		if (level >= item_quantities.size()){
			return;
		}

		item_quantities[level] += 1;
	}
};


struct ExtractTaskComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 20);

	ItemId item_id;
	EntityId to_id;
	EntityId from_id;
	DepositLevel from_level;
};


struct MachineComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 21);

	MachineType type;
	CraftRecipeId recipe_id;

	CraftDuration duration;
	ItemBag input;
	ItemBag inner;
	ItemBag output;

	ItemQuantity input_max;
	ItemQuantity output_max;
};


struct TileIndexComponent{
	static const ComponentMask COMPONENT_MASK = (1 << 22);

	TileIndex index;
};

#include "./logic/action.h"

struct ActorComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 30);

	logic::action::Action action;
};

/*

struct ActionComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 14);

	enum Status {
		NONE,
		IN_PROGRESS,
		SUCCESS,
		FAILURE,
		DISPOSABLE
	};

	Status status;

	ActionComponent()
		: status(NONE) {
	}
};

struct GoToAdjacentActionComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 15);

	EntityId to_id;
	hope::grid::PathCrawler* crawler;

	GoToAdjacentActionComponent() :
		crawler(NULL) {
	}
};


struct ExtractActionComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 16);

	EntityId from_id;
	DepositLevel from_level;
};

struct ItemBagPickActionComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 17);

	ItemId item_id;
	EntityId from_id;
};

struct ConstructActionComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 18);

	EntityId task_id;
};

struct ItemBagGiveActionComponent {
	static const ComponentMask COMPONENT_MASK = (1 << 19);

	ItemId item_id;
	EntityId to_id;
};



struct MachineOutputPickActionComponent{
	static const ComponentMask COMPONENT_MASK = (1 << 23);

	ItemId item_id;
	EntityId from_id;
};

*/

#define REGISTER_COMPONENT(COMPONENT_CLASS) \
private: \
	static ComponentManager<COMPONENT_CLASS> manager_##COMPONENT_CLASS; \
public: \
	template <> static EntityId findFirstEntityId<COMPONENT_CLASS>() { return manager_##COMPONENT_CLASS.findFirstEntityId(); } \
	template <> static COMPONENT_CLASS* get<COMPONENT_CLASS>(EntityId id) { return manager_##COMPONENT_CLASS.get(id); } \
	template <> static COMPONENT_CLASS* find<COMPONENT_CLASS>(EntityId id) { return manager_##COMPONENT_CLASS.find(id); } \
	template <> static COMPONENT_CLASS* attach<COMPONENT_CLASS>(EntityId id) { return manager_##COMPONENT_CLASS.attach(id); } \
	template <> static void detach<COMPONENT_CLASS>(EntityId id) { return manager_##COMPONENT_CLASS.detach(id); } \
	template <> static void foreach<COMPONENT_CLASS>(std::function <void(COMPONENT_CLASS*, EntityId)> callback) { return manager_##COMPONENT_CLASS.foreach(callback); } \
    template <> static void foreach<COMPONENT_CLASS>(void(*callback)(COMPONENT_CLASS*, EntityId)) { return manager_##COMPONENT_CLASS.foreach(callback); }

class Components {
public:
	template <class T>
	static T* get(EntityId id) { static_assert(false, "Missing Component."); }
	
	template <class T>
	static T* find(EntityId id) { static_assert(false, "Missing Component."); }

	template <class T>
	static T* attach(EntityId id) { static_assert(false, "Missing Component."); }

	template <class T>
	static void detach(EntityId id) { static_assert(false, "Missing Component."); }

	template <class T>
	static void foreach(void(*callback)(T*, EntityId)) { static_assert(false, "Missing Component."); }

	template <class T>
	static void foreach(std::function <void(T*, EntityId)> callback) { static_assert(false, "Missing Component."); }

	template <class T>
	static EntityId findFirstEntityId() { static_assert(false, "Missing Component."); }

	
	

	REGISTER_COMPONENT(GoToComponent)
	REGISTER_COMPONENT(LocationComponent)
	REGISTER_COMPONENT(ItemBagComponent)
	REGISTER_COMPONENT(AgentComponent)
	REGISTER_COMPONENT(StorageComponent)
	

	REGISTER_COMPONENT(DoableComponent)
	REGISTER_COMPONENT(PlanComponent)
	REGISTER_COMPONENT(LaborComponent)
	REGISTER_COMPONENT(DepositComponent)


	REGISTER_COMPONENT(TaskComponent)
	REGISTER_COMPONENT(ConstructionTaskComponent)
	REGISTER_COMPONENT(ItemTransfertTaskComponent)
	REGISTER_COMPONENT(ConstructTaskComponent)
	REGISTER_COMPONENT(ExtractTaskComponent)

	REGISTER_COMPONENT(ActorComponent)
	
/*
	REGISTER_COMPONENT(ActionComponent)
	REGISTER_COMPONENT(GoToAdjacentActionComponent)
	REGISTER_COMPONENT(ExtractActionComponent)
	REGISTER_COMPONENT(ConstructActionComponent)
	REGISTER_COMPONENT(ItemBagPickActionComponent)
	REGISTER_COMPONENT(ItemBagGiveActionComponent)
	REGISTER_COMPONENT(MachineOutputPickActionComponent)
*/

	REGISTER_COMPONENT(MachineComponent)
	REGISTER_COMPONENT(TileIndexComponent)
	

	static void detachAll(EntityId id){
		manager_GoToComponent.detach(id);
		manager_ItemBagComponent.detach(id);
		manager_LocationComponent.detach(id);
		manager_AgentComponent.detach(id);
		manager_StorageComponent.detach(id);
		
		manager_TaskComponent.detach(id);
		manager_ConstructionTaskComponent.detach(id);
		manager_ItemTransfertTaskComponent.detach(id);
		manager_ConstructTaskComponent.detach(id);

		manager_DoableComponent.detach(id);
		manager_PlanComponent.detach(id);
		manager_DepositComponent.detach(id);
	}
	
};


struct TaskComponent_LevelAndPriorityCompare {
	bool operator() (const EntityId a, const EntityId b) const {
		auto ac = Components::get<TaskComponent>(a);
		auto bc = Components::get<TaskComponent>(b);

		if (ac->level < bc->level){
			return false;
		}
		if (ac->level == bc->level) {
			return ac->priority > bc->priority;
		}
		return true;
	}
};

#endif /* HOPE_SAMPLES_TOY_Components_H */