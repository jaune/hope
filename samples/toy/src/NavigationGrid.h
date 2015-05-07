#ifndef HOPE_SAMPLES_TOY_NavigationGrid_H
#define HOPE_SAMPLES_TOY_NavigationGrid_H

#include <stdint.h>

#include <grid/Grid.h>
#include <grid/FloodFillQuery.h>

typedef int32_t NavigationGroup;

struct NavigationCell {
	NavigationGroup group;

	NavigationCell() :
		NavigationCell(0) {
	}
	

	NavigationCell(NavigationGroup group) :
		group(group) {
	}
};

class NavigationGrid : public hope::grid::GridMapWithDefault<NavigationCell> {

	int32_t group_total;
	hope::grid::IsOpenCallback callback;

public:
	NavigationGrid(size_t width, size_t height, hope::grid::IsOpenCallback callback) :
		callback(callback),
		hope::grid::GridMapWithDefault<NavigationCell>(width, height, NavigationCell(0)) {
	}

	NavigationGroup findGroup(const hope::grid::Location& location) {
		const Cell& cell = get(location);
		return cell.group;
	}

	void applyGroup(NavigationGroup group, int32_t x, int32_t y) {
		set(x, y, Cell(group));
	}

	void updateGroups() {
		hope::grid::FloodFillQuery query(getWidth(), getHeight(), callback);

		setAllToDefault();
		group_total = 1;

		bool test = true;
		while (test) {
			hope::grid::Callback cb = std::bind(&NavigationGrid::applyGroup, this, group_total, std::placeholders::_1, std::placeholders::_2);
			test = query.findFirstUnvisitedArea(cb);
			if (test) {
				group_total++;
			}
		}
	}
};

#endif /* HOPE_SAMPLES_TOY_NavigationGrid_H */