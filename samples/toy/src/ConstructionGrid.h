#ifndef HOPE_SAMPLES_TOY_CONSTRUCTIONGRID_H
#define HOPE_SAMPLES_TOY_CONSTRUCTIONGRID_H

#include "./EntityManager.h"

struct ConstructionCell {
	EntityId taskId;
	
	ConstructionCell() :
		taskId(0) {
	}
};

struct ConstructionGrid : public hope::grid::GridMapWithoutDefault<ConstructionCell> {
	
	ConstructionGrid(int32_t w, int32_t h) :
		hope::grid::GridMapWithoutDefault<ConstructionCell>(w, h) {
	}
};




#endif /* HOPE_SAMPLES_TOY_CONSTRUCTIONGRID_H */