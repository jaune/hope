#include "./NavigationGrid.h"

#include <grid/PathFinder.h>
#include <grid/FloodFillQuery.h>

#include <profile.h>

namespace hope {
	namespace grid {


		NavigationGrid::NavigationGrid(size_t width, size_t height) :
			hope::grid::Grid<NavigationCell>(width, height),
			callback(std::bind(&NavigationGrid::isWalkable, this, std::placeholders::_1)) {

			resetWalkable();
			resetGroups();
		}

		bool NavigationGrid::validatePathCrawler(const hope::grid::PathCrawler& path) const {
			return path.isValid();
		}
		
		hope::grid::PathCrawler* NavigationGrid::findPath(const hope::grid::Location& from_location, const hope::grid::Location& to_location) const {

			hope::profile::begin(__FUNCTION__);

			if (!isWalkable(from_location)) {
				return NULL;
			}
			if (!isWalkable(to_location)) {
				return NULL;
			}

			if (findGroup(from_location) != findGroup(to_location)){
				return NULL;
			}

			hope::grid::PathFinder pf(aabox, callback);

			auto r = pf.find(from_location, to_location);

			hope::profile::end();

			return r;
		}

		void NavigationGrid::resetWalkable() {
			for (size_t i = 0; i < length; ++i) {
				cells[i].walkable = true;
			}
		}

		void NavigationGrid::resetGroups() {
			for (size_t i = 0; i < length; ++i) {
				cells[i].group = 0;
			}			
		}

		void NavigationGrid::updateGroups() {
			hope::grid::FloodFillQuery query(width, height, callback);

			resetGroups();
			group_total = 1;

			bool test = true;
			while (test) {
				hope::grid::Callback cb = std::bind(&NavigationGrid::setGroup, this, std::placeholders::_1, std::placeholders::_2, group_total);
				test = query.findFirstUnvisitedArea(cb);
				if (test) {
					group_total++;
				}
			}
		}


	}
}
