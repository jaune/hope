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

#include <grid/NavigationGrid.h>

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
	hope::grid::NavigationGrid* navigation;


	bool needUpdateNavigationGroups;

	hope::grid::IsOpenCallback isCellOpenCallback;

	TheGridSystem();

	void setWall(int32_t x, int32_t y);

	void setDestroy(int32_t x, int32_t y);
	void setFloor(int32_t x, int32_t y);

	void setRoom(int32_t x, int32_t y, int32_t w, int32_t h);

	void setDoor(int32_t x, int32_t y, bool isLocked, bool isClose);

	void updateNavigationGroups();

	CellType getCellType(int32_t x, int32_t y) const;

	void initialize(size_t w, size_t h);

	hope::grid::NavigationGroup getNavigationGroup(const hope::grid::Location& location) const;

	hope::grid::PathCrawler* findShortestPathToAdjacent(const hope::grid::Location& from_location, EntityId to_id) const;
	hope::grid::PathCrawler* findShortestPath(const hope::grid::Location& from_location, const hope::grid::Location& to_location) const;
	hope::grid::PathCrawler* findShortestPathToAdjacent(EntityId from_id, EntityId to_id) const;
	
};



namespace systems {
	
	TheGridSystem* TheGrid();

};

#endif /* HOPE_SAMPLES_TOY_system_TheGrid_H */