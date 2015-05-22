#ifndef HOPE_SAMPLES_TOY_NavigationGrid_H
#define HOPE_SAMPLES_TOY_NavigationGrid_H

#include <grid/Grid.h>
#include <grid/PathCrawler.h>

namespace hope {
	namespace grid {

		typedef int32_t NavigationGroup;

		struct NavigationCell {
			NavigationGroup group = 0;
			bool walkable = false;

			NavigationCell() :
				NavigationCell(0) {
			}

			NavigationCell(NavigationGroup group) :
				group(group) {
			}
		};

		class NavigationGrid : public hope::grid::Grid< NavigationCell > {
			int32_t group_total;
			hope::grid::IsOpenCallback callback;

		public:
			NavigationGrid(size_t width, size_t height);

			bool validatePathCrawler(const hope::grid::PathCrawler& path) const;
			hope::grid::PathCrawler* findPath(const hope::grid::Location& from_location, const hope::grid::Location& to_location) const;
			void updateGroups();

			void resetGroups();
			void resetWalkable();

			inline NavigationGroup findGroup(const hope::grid::Location& location) const {
				return at(location)->group;
			}

			inline void setGroup(int32_t x, int32_t y, NavigationGroup group) {
				at(x, y)->group = group;
			}			
			
			inline void setWalkable(int32_t x, int32_t y, bool walkable) {
				at(x, y)->walkable = walkable;
			}

			inline void setWalkable(const hope::grid::Location& location, bool walkable) {
				at(location)->walkable = walkable;
			}

			inline bool isWalkable(const hope::grid::Location& location) const {
				return at(location)->walkable;
			}
		};

	}
}

#endif /* HOPE_SAMPLES_TOY_NavigationGrid_H */