#ifndef HOPE_GRID_PATHFINDER_H
#define HOPE_GRID_PATHFINDER_H

#include "./Grid.h"
#include "./PathCrawler.h"


#include <stack>
#include <deque>
#include <unordered_map>
#include <algorithm>
#include <queue>

template<typename T, typename Number = int>
struct PriorityQueue {
	typedef std::pair<Number, T> PQElement;

	struct Greater {
		bool operator() (const PQElement& a, const PQElement& b) const {
			return a.first > b.first;
		}
	};

	std::priority_queue< PQElement, std::vector<PQElement>, Greater > elements;

	inline bool empty() { return elements.empty(); }

	inline void push(T item, Number priority) {
		elements.emplace(priority, item);
	}

	inline void clear() {
		elements = std::priority_queue < PQElement, std::vector<PQElement>, Greater >();
	}

	inline T pop() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};


namespace hope {
	namespace grid {


		class PathFinder {
		public:

			typedef int32_t Cost;
			typedef int32_t Index;

		public:
			hope::grid::AABox bounds;

		private:
			PriorityQueue<Location> frontier;
			Location goal;

			IsOpenCallback callback;

			bool* came_from_alive;
			Location* came_from_location;

			bool* cost_so_far_alive;
			Cost* cost_so_far_value;

		private:
			inline Cost computeCost(const Location& current, const Location& next) const {
				return 1;
			}

			inline int32_t computeHeuristic(const Location& current, const Location& goal) const {
				return 10 * (abs(current.x - goal.x) + abs(current.y - goal.y));
			}

			inline bool isOpen(const Location& location) const {
				return callback(location);
			}

			inline Index index(const Location& location) const {
				return location.x + (location.y * bounds.width());
			}

			// ------------

			inline void setCostSoFar(const Location& location, Cost cost) {
				const Index i = index(location);

				cost_so_far_alive[i] = true;
				cost_so_far_value[i] = cost;
			}

			inline bool hasCostSoFar(const Location& location) const {
				return cost_so_far_alive[index(location)];
			}

			inline const Cost getCostSoFar(const Location& location) const {
				return cost_so_far_value[index(location)];
			}

			// ------------

			inline void setCameFrom(const Location& location, const Location& from) {
				const Index i = index(location);

				came_from_alive[i] = true;
				came_from_location[i] = from;
			}

			inline bool hasCameFrom(const Location& location) const {
				return came_from_alive[index(location)];
			}

			inline const Location& getCameFrom(const Location& location) const {
				return came_from_location[index(location)];
			}

			// ------------

			PathCrawler* reconstructPath(const Location& start, const Location& goal) const {
				if (!hasCameFrom(goal)) {
					return NULL;
				}

				PathCrawler* crawler = new PathCrawler(callback);

				Location current = goal;
				crawler->push(current);

				while (current != start) {
					current = getCameFrom(current);
					crawler->push(current);
				}

				if (crawler->length() == 0) {
					delete crawler;
					return NULL;
				}

				return crawler;
			}

			void processNeighbor(const Location& current, const Location& next) {
				if (isOpen(next) && bounds.contains(next)) {
					Cost new_cost = getCostSoFar(current) + computeCost(current, next);

					if (!hasCostSoFar(next) || new_cost < getCostSoFar(next)) {
						setCostSoFar(next, new_cost);
						int priority = new_cost + computeHeuristic(next, goal);
						frontier.push(next, priority);
						setCameFrom(next, current);
					}
				}
			}



		public:
			PathFinder(const hope::grid::AABox& bounds, IsOpenCallback callback) :
				callback(callback),
				bounds(bounds) {

				Index length = bounds.width() * bounds.height();

				came_from_alive = new bool[length];
				came_from_location = new Location[length];

				cost_so_far_alive = new bool[length];
				cost_so_far_value = new Cost[length];
			}			

			~PathFinder() {
				delete[] came_from_alive;
				delete[] came_from_location;

				delete[] cost_so_far_alive;
				delete[] cost_so_far_value;
			}
			
			PathCrawler* find(const Location& start, const Location& goal) {
				Index length = bounds.width() * bounds.height();

				for (Index i = 0; i < length; ++i) {
					came_from_alive[i] = false;
					cost_so_far_alive[i] = false;
				}
				frontier.clear();

				frontier.push(start, 0);
				this->goal = goal;

				while (!frontier.empty()) {
					auto current = frontier.pop();

					if (current == goal) {
						break;
					}

					processNeighbor(current, current.getTopNeighbor());
					processNeighbor(current, current.getRightNeighbor());
					processNeighbor(current, current.getBottomNeighbor());
					processNeighbor(current, current.getLeftNeighbor());
				}

				return reconstructPath(start, goal);
			}
		};


	} /* namespace grid */
} /* namespace hope */

#endif /* HOPE_GRID_PATHFINDER_H */