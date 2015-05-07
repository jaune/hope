#ifndef HOPE_SAMPLES_TOY_system_task_Construction_H
#define HOPE_SAMPLES_TOY_system_task_Construction_H

#include <grid/Grid.h>
#include "../../ConstructionGrid.h"
#include "../../ConstructionRecipeTable_generated.h"
#include "../../TaskBuilder.h"
#include "../../CellType.h"
#include "../TheGrid.h"
#include <asset/asset.h>

typedef std::unordered_map<int32_t, const hope::samples::toy::fbs::ConstructionRecipe*> ConstructionRecipeTable;

class ConstructionTaskSystem {
public:
	ConstructionGrid* kConstructionGrid = NULL;
	ConstructionRecipeTable table_ConstructionRecipeTable;

	void cancelConstruction(int32_t x, int32_t y) {
		const ConstructionCell* cell = kConstructionGrid->find(x, y);
		if (cell != NULL) {
			// cancelTask(cell->taskId); TODO
			kConstructionGrid->setToNull(x, y);
		}
	}

	bool initialize(int32_t w, int32_t h){
		kConstructionGrid = new ConstructionGrid(w, h);
		return true;
	}
	
	bool loadConstructionRecipeTable(const hope::asset::Asset& asset){
		if (asset.is_null()) {
			return false;
		}
		const hope::samples::toy::fbs::ConstructionRecipeTable* fbs_ConstructionRecipeTable = hope::samples::toy::fbs::GetConstructionRecipeTable(asset.pointer);
		if (fbs_ConstructionRecipeTable == NULL) {
			return false;
		}

		for (auto it = fbs_ConstructionRecipeTable->recipes()->begin(); it != fbs_ConstructionRecipeTable->recipes()->end(); ++it) {
			table_ConstructionRecipeTable.insert(ConstructionRecipeTable::value_type(it->id(), *it));
		}

		return true;
	}

	EntityId findTask(hope::grid::Location& location){
		auto cell = kConstructionGrid->find(location);
		if (cell == NULL){
			return 0;
		}
		return cell->taskId;
	}

	void beginConstruction(int32_t x, int32_t y, const hope::samples::toy::fbs::ConstructionRecipe* recipe) {
		CellType type = systems::TheGrid()->kToyGrid->at(x, y)->type;

		if (!(type == CellType::VOID || type == CellType::WALL)) {
			return;
		}

		//ConstructionTask* task = new ConstructionTask(kConstructionRecipeTable[574164], hope::grid::Location(x, y));
		//TaskHeader* header = TheGrid::kTaskPool->addTask(task);

		TaskPriority priority = 10;

		ConstructionCell cell;

		// cell.type = CellType::FLOOR;

		priority += systems::TheGrid()->kToyGrid->getCellType(x + 1, y) == CellType::VOID ? 0 : 1;
		priority += systems::TheGrid()->kToyGrid->getCellType(x - 1, y) == CellType::VOID ? 0 : 1;
		priority += systems::TheGrid()->kToyGrid->getCellType(x, y + 1) == CellType::VOID ? 0 : 1;
		priority += systems::TheGrid()->kToyGrid->getCellType(x, y - 1) == CellType::VOID ? 0 : 1;

		if (type == CellType::WALL){
			priority = 0;
		}

		//header->priority = priority;

		TaskBuilder tb;

		EntityId task_id = tb.createConstructionTask(recipe, priority, hope::grid::Location(x, y));

		cell.taskId = task_id;

		kConstructionGrid->set(x, y, cell);
	}

	void beginFloorConstruction(int32_t x, int32_t y) {

		CellType type = systems::TheGrid()->kToyGrid->at(x, y)->type;

		if (!(type == CellType::VOID || type == CellType::WALL)) {
			return;
		}

		//ConstructionTask* task = new ConstructionTask(kConstructionRecipeTable[574164], hope::grid::Location(x, y));
		//TaskHeader* header = TheGrid::kTaskPool->addTask(task);

		TaskPriority priority = 10;

		ConstructionCell cell;

		// cell.type = CellType::FLOOR;

		priority += systems::TheGrid()->kToyGrid->getCellType(x + 1, y) == CellType::VOID ? 0 : 1;
		priority += systems::TheGrid()->kToyGrid->getCellType(x - 1, y) == CellType::VOID ? 0 : 1;
		priority += systems::TheGrid()->kToyGrid->getCellType(x, y + 1) == CellType::VOID ? 0 : 1;
		priority += systems::TheGrid()->kToyGrid->getCellType(x, y - 1) == CellType::VOID ? 0 : 1;

		if (type == CellType::WALL){
			priority = 0;
		}

		//header->priority = priority;

		TaskBuilder tb;

		EntityId task_id = tb.createConstructionTask(table_ConstructionRecipeTable[574164], priority, hope::grid::Location(x, y));

		cell.taskId = task_id;

		kConstructionGrid->set(x, y, cell);
	}

	void beginWallConstruction(int32_t x, int32_t y)  {

		CellType type = systems::TheGrid()->kToyGrid->at(x, y)->type;

		if (!(type == CellType::VOID || type == CellType::FLOOR)) {
			return;
		}

		//ConstructionTask* task = new ConstructionTask(kConstructionRecipeTable[353441], hope::grid::Location(x, y));
		//TaskHeader* header = TheGrid::kTaskPool->addTask(task);

		TaskPriority priority = 1;

		ConstructionCell cell;
		// cell.type = CellType::WALL;

		priority += systems::TheGrid()->kToyGrid->getCellType(x + 1, y) == CellType::VOID ? 0 : 1;
		priority += systems::TheGrid()->kToyGrid->getCellType(x - 1, y) == CellType::VOID ? 0 : 1;
		priority += systems::TheGrid()->kToyGrid->getCellType(x, y + 1) == CellType::VOID ? 0 : 1;
		priority += systems::TheGrid()->kToyGrid->getCellType(x, y - 1) == CellType::VOID ? 0 : 1;


		TaskBuilder tb;

		EntityId task_id = tb.createConstructionTask(table_ConstructionRecipeTable[353441], priority, hope::grid::Location(x, y));

		cell.taskId = task_id;

		kConstructionGrid->set(x, y, cell);
	}
};

namespace systems {
namespace task {
	static ConstructionTaskSystem Construction;
}
}

#endif /* HOPE_SAMPLES_TOY_system_task_Construction_H */