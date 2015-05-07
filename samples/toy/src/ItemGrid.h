#ifndef HOPE_SAMPLES_TOY_ITEMGRID_H
#define HOPE_SAMPLES_TOY_ITEMGRID_H

#include <grid/Grid.h>
#include "./ItemTable_generated.h"
#include "./ItemBag.h"

struct ItemCell {
	ItemBag items;
};

struct ItemGrid : public hope::grid::GridMapWithoutDefault < ItemCell > {
	ItemGrid(int32_t w, int32_t h) :
		hope::grid::GridMapWithoutDefault < ItemCell >(w, h) {
	}

	ItemQuantity getItemQuantityAt(const hope::grid::Location& location, ItemId item_id) {
		const ItemCell* cell = find(location);
		
		if (cell == NULL) {
			return 0;
		}

		return cell->items.getItemQuantity(item_id);
	}
};

#endif /* HOPE_SAMPLES_TOY_ITEMGRID_H */