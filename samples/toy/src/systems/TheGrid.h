#ifndef HOPE_SAMPLES_TOY_system_TheGrid_H
#define HOPE_SAMPLES_TOY_system_TheGrid_H

#include <stdint.h>

#include <grid/Grid.h>
#include <grid/PathFinder.h>
#include "../ItemGrid.h"

#include "../Plan.h"

#include "../asset/ItemTable_generated.h"

#include "../Entities.h"
#include "../CellType.h"
#include "../systems/TheGrid.h"

#include "../NavigationGrid.h"

#include "../Components.h"

struct Room {
	int32_t o2;
	int32_t cell_count;
	bool airtight;
};


struct RoomCell {
	Room* room;
};

typedef hope::grid::GridMapWithDefault<RoomCell> RoomGrid;



#include "../ToyGrid.h"

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

	TheGridSystem();

	bool isCellOpen(const hope::grid::Location& location) const;

	void setWall(int32_t x, int32_t y);

	void setDestroy(int32_t x, int32_t y);
	void setFloor(int32_t x, int32_t y);

	void setRoom(int32_t x, int32_t y, int32_t w, int32_t h);

	void setDoor(int32_t x, int32_t y, bool isLocked, bool isClose);

	void updateNavigationGroups();

	CellType getCellType(int32_t x, int32_t y) const;

	void initialize(size_t w, size_t h);

	NavigationGroup getNavigationGroup(const hope::grid::Location& location) const;

	hope::grid::PathCrawler* findShortestPathToAdjacent(const hope::grid::Location& from_location, EntityId to_id) const;

	hope::grid::PathCrawler* findShortestPath(const hope::grid::Location& from_location, const hope::grid::Location& to_location) const;
};



namespace systems {
	
	TheGridSystem* TheGrid();

};

#endif /* HOPE_SAMPLES_TOY_system_TheGrid_H */