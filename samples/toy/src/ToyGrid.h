#ifndef HOPE_SAMPLES_TOY_TOYGRID_H
#define HOPE_SAMPLES_TOY_TOYGRID_H

struct ToyCell{
	CellType type;
};

struct ToyGrid : public ::hope::grid::Grid < ToyCell > {
	ToyGrid(int32_t w, int32_t h) : ::hope::grid::Grid<ToyCell>(w, h) {
		size_t index;

		for (index = 0; index < length; index++) {
			cells[index].type = CellType::VOID;
		}
	}

	CellType getCellType(int32_t x, int32_t y) {

		if (in(x, y)) {
			return at(x, y)->type;
		}

		return CellType::VOID;
	}
};


#endif /* HOPE_SAMPLES_TOY_TOYGRID_H */