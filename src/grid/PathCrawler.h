#ifndef HOPE_GRID_PATHCRAWLER_H
#define HOPE_GRID_PATHCRAWLER_H

#include "./Location.h"
#include "./Grid.h"


#include <vector>

namespace hope {
	namespace grid {

		class PathCrawler {
			std::vector < Location > checkpoints;

		public:
			hope::grid::IsOpenCallback callback;

		public:
			PathCrawler(hope::grid::IsOpenCallback cb) :
				callback(cb) {
			}

			void push(const Location& l) {
				checkpoints.push_back(l);
			}

			void pop(Location& l) {
				l.set(checkpoints.back());
				checkpoints.pop_back();
			}

			bool empty() {
				return checkpoints.empty();
			}

			bool isValid() const {
				for (auto it = checkpoints.begin(); it != checkpoints.end(); it++) {
					if (!callback(*it)) {
						return false;
					}
				}
				return true;
			}

			inline size_t length() const {
				return checkpoints.size();
			}

		};

	} /* namespace grid */
} /* namespace hope */

#endif /* HOPE_GRID_PATHCRAWLER_H */