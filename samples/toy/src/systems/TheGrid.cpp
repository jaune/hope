#include "./TheGrid.h"
#include <grid/Location.h>

TheGridSystem::TheGridSystem() :
needUpdateNavigationGroups(false),
isCellOpenCallback(std::bind(&TheGridSystem::isCellOpen, this, std::placeholders::_1)) {
}

bool TheGridSystem::isCellOpen(const hope::grid::Location& location) const {
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

void TheGridSystem::setWall(int32_t x, int32_t y) {
	kToyGrid->at(x, y)->type = CellType::WALL;
	kRoomGrid->setToDefault(x, y);
	navigation->setToDefault(x, y);
}

void TheGridSystem::setDestroy(int32_t x, int32_t y) {
}

void TheGridSystem::setFloor(int32_t x, int32_t y) {
	kToyGrid->at(x, y)->type = CellType::FLOOR;


}

void TheGridSystem::setRoom(int32_t x, int32_t y, int32_t w, int32_t h) {
	kToyGrid->queryRect(x, y, w, h, 1,
		std::bind(&TheGridSystem::setFloor, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&TheGridSystem::setWall, this, std::placeholders::_1, std::placeholders::_2));
}

void TheGridSystem::setDoor(int32_t x, int32_t y, bool isLocked, bool isClose){
	DoorCell doorCell;

	doorCell.isLocked = isLocked;
	doorCell.isClose = isClose;

	kDoorGrid->set(x, y, doorCell);
	kToyGrid->at(x, y)->type = CellType::DOOR;
}

void TheGridSystem::updateNavigationGroups(){
	navigation->updateGroups();
}

CellType TheGridSystem::getCellType(int32_t x, int32_t y) const {
	return kToyGrid->getCellType(x, y);
}



void TheGridSystem::initialize(size_t w, size_t h) {
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



NavigationGroup TheGridSystem::getNavigationGroup(const hope::grid::Location& location) const {
	return navigation->findGroup(location);
}

hope::grid::PathCrawler* TheGridSystem::findShortestPathToAdjacent(const hope::grid::Location& from_location, EntityId to_id) const {
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

hope::grid::PathCrawler* TheGridSystem::findShortestPath(const hope::grid::Location& from_location, const hope::grid::Location& to_location) const {
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



namespace systems {

	TheGridSystem* TheGrid() {
		static TheGridSystem* system = NULL;

		if (system == NULL) {
			system = new TheGridSystem();
		}

		return system;
	}

};