#ifndef HOPE_SAMPLES_TOY_THEGRID_H
#define HOPE_SAMPLES_TOY_THEGRID_H

#include <stdint.h>

#include <grid/Grid.h>
#include "./ItemGrid.h"

#include "./Plan.h"
#include "./Task.h"

#include "./asset/ItemTable_generated.h"

#include "./Entities.h"
#include "./CellType.h"
#include "./systems/TheGrid.h"

#include "./NavigationGrid.h"

struct Room {
	int32_t o2;
	int32_t cell_count;
	bool airtight;
};


struct RoomCell {
	Room* room;
};

typedef hope::grid::GridMapWithDefault<RoomCell> RoomGrid;



#include "./ToyGrid.h"

struct DoorCell {

	bool isClose;
	bool isLocked;

};

typedef hope::grid::GridMapWithoutDefault<DoorCell> DoorGrid;


struct TheGridSystem {

	size_t width;
	size_t heigth;
	hope::grid::AABox bounds;

	DoorGrid* kDoorGrid;
	ToyGrid* kToyGrid;
	RoomGrid* kRoomGrid;
	ItemGrid* kItemGrid;
	NavigationGrid* navigation;


	bool needUpdateNavigationGroups;

	hope::grid::IsOpenCallback isCellOpenCallback;

	TheGridSystem() :
		needUpdateNavigationGroups(false),
		isCellOpenCallback(std::bind(&TheGridSystem::isCellOpen, this, std::placeholders::_1)) {
	}

	bool isCellOpen(const hope::grid::Location& location) const {
		CellType type = kToyGrid->at(location)->type;

		if (type == FLOOR || type == VOID) {
			return true;
		}
		else if (type == DOOR) {
			const DoorCell* cell = kDoorGrid->find(location);

			if (cell != NULL) {
				return !cell->isLocked;
			}
			return true;
		}

		return false;
	}

	void setWall(int32_t x, int32_t y) {
		kToyGrid->at(x, y)->type = CellType::WALL;
		kRoomGrid->setToDefault(x, y);
		navigation->setToDefault(x, y);
	}

	void setDestroy(int32_t x, int32_t y) {
	}

	void setFloor(int32_t x, int32_t y) {
		kToyGrid->at(x, y)->type = CellType::FLOOR;

		
	}

	void setRoom(int32_t x, int32_t y, int32_t w, int32_t h) {
		kToyGrid->queryRect(x, y, w, h, 1, 
			std::bind(&TheGridSystem::setFloor, this, std::placeholders::_1, std::placeholders::_2), 
			std::bind(&TheGridSystem::setWall, this, std::placeholders::_1, std::placeholders::_2));
	}

	void setDoor(int32_t x, int32_t y, bool isLocked, bool isClose){
		DoorCell doorCell;

		doorCell.isLocked = isLocked;
		doorCell.isClose = isClose;

		kDoorGrid->set(x, y, doorCell);
		kToyGrid->at(x, y)->type = CellType::DOOR;
	}

	void updateNavigationGroups(){
		navigation->updateGroups();
	}

	CellType getCellType(int32_t x, int32_t y) const {
		return kToyGrid->getCellType(x, y);
	}

	

	void initialize(size_t w, size_t h) {
		width = w;
		heigth = h;

		bounds.setX(0, width - 1);
		bounds.setY(0, heigth - 1);


		
		//	TheGrid::kGrid = new hope::grid::IsOpenGrid(100, 100);
		kToyGrid = new ToyGrid(w, h);

		RoomCell defaultRoomCell;
		defaultRoomCell.room = NULL;

		kRoomGrid = new RoomGrid(w, h, defaultRoomCell);

		kItemGrid = new ItemGrid(w, h);

		navigation = new NavigationGrid(w, h, isCellOpenCallback);

		kDoorGrid = new DoorGrid(w, h);

	}

	

	NavigationGroup getNavigationGroup(const hope::grid::Location& location) const {
		return navigation->findGroup(location);
	}
	
	hope::grid::PathCrawler* findShortestPathToAdjacent(const hope::grid::Location& from_location, EntityId to_id) const {
		auto dataLocation = Components::get<LocationComponent>(to_id);

		hope::grid::Location neighbors[4];

		dataLocation->position.get4Neighbors(neighbors);

		hope::grid::PathCrawler* currentPath = NULL;
		hope::grid::PathCrawler* shortestPath = NULL;

		for (size_t i = 0; i < 4; i++) {
			currentPath = findShortestPath(from_location, neighbors[i]);

			if (currentPath != NULL) {
				if (shortestPath == NULL) {
					shortestPath = currentPath;
				}
				else {
					if (currentPath->length() < shortestPath->length()){
						shortestPath = currentPath;
					}
					else {
						delete currentPath;
					}
				}
			}
		}
		return shortestPath;
	}

	hope::grid::PathCrawler* findShortestPath(const hope::grid::Location& from_location, const hope::grid::Location& to_location) const {
		if (!isCellOpen(from_location)) {
			return NULL;
		}
		if (!isCellOpen(to_location)) {
			return NULL;
		}

		if (getNavigationGroup(from_location) != getNavigationGroup(to_location)){
			return NULL;
		}

		
		hope::grid::PathFinder pf(bounds, isCellOpenCallback);

		return pf.find(from_location, to_location);
	}
};



#endif /* HOPE_SAMPLES_TOY_THEGRID_H */