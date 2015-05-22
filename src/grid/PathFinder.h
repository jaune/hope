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
			hope::grid::AABox bounds;

		private:
			IsOpenCallback callback;

		private:
			inline int32_t computeCost(const Location& current, const Location& next) const {
				return 1;
			}

			inline int32_t computeHeuristic(const Location& current, const Location& goal) const {
				return 10 * (abs(current.x - goal.x) + abs(current.y - goal.y));
			}

			inline bool isOpen(const Location& location) const {
				return callback(location);
			}

		public:


			PathFinder(const hope::grid::AABox& bounds, IsOpenCallback callback) :
				callback(callback),
				bounds(bounds) {
			}

			~PathFinder() {
			}

			std::unordered_map<Location, Location> came_from;
			std::unordered_map<Location, int> cost_so_far;
			PriorityQueue<Location> frontier;
			Location goal;

			PathCrawler* reconstructPath(const Location& start, const Location& goal) const {
				if (came_from.find(goal) == came_from.end()){
					return NULL;
				}

				PathCrawler* crawler = new PathCrawler(callback);

				Location current = goal;
				crawler->push(current);

				while (current != start) {
					current = came_from.at(current);
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
					int new_cost = cost_so_far[current] + computeCost(current, next);

					if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
						cost_so_far[next] = new_cost;
						int priority = new_cost + computeHeuristic(next, goal);
						frontier.push(next, priority);
						came_from[next] = current;
					}
				}
			}



			PathCrawler* find(const Location& start, const Location& goal) {
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



		class PathFinder_blob_v1 {
		public:
			hope::grid::AABox bounds;

		private:
			IsOpenCallback callback;

		private:
			int32_t computeCost(const Location& current, const Location& next) {
				return 1;
			}

			int32_t computeHeuristic(const Location& current, const Location& goal){
				return 10 * (abs(current.x - goal.x) + abs(current.y - goal.y));
			}

			bool isOpen(const Location& location) const {
				return callback(location);
			}

		public:
			PathFinder_blob_v1(const hope::grid::AABox& bounds, IsOpenCallback callback) :
				callback(callback),
				bounds(bounds) {
			}

			~PathFinder_blob_v1(){
			}

			std::unordered_map<Location, Location> came_from;
			std::unordered_map<Location, int> cost_so_far;

			PathCrawler* reconstructPath(const Location& start, const Location& goal) const {
				PathCrawler* crawler = new PathCrawler(callback);

				Location current = goal;
				crawler->push(current);
				while (current != start) {
					current = came_from.at(current);
					crawler->push(current);
				}

				if (crawler->length() == 0) {
					delete crawler;
					return NULL;
				}

				return crawler;
			}

			PathCrawler* find(const Location& start, const Location& goal) {

				PriorityQueue<Location> frontier;

				frontier.push(start, 0);

				Location Neighbors[4];

				while (!frontier.empty()) {
					auto current = frontier.pop();

					if (current == goal) {
						break;
					}

					current.get4Neighbors(Neighbors);

					for (auto next : Neighbors) {
						if (isOpen(next) && bounds.contains(next)) {
							int new_cost = cost_so_far[current] + computeCost(current, next);

							if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
								cost_so_far[next] = new_cost;
								int priority = new_cost + computeHeuristic(next, goal);
								frontier.push(next, priority);
								came_from[next] = current;
							}
						}
					}
				}

				return reconstructPath(start, goal);
			}
		};


		class PathFinder_mine_v1 {

		public:


		private:

			struct Node {
				int32_t x;
				int32_t y;
				bool isOpen;
				bool isClose;
				Node* parent;

				int32_t g, f, h;

				Node() : g(0), f(0), h(0), isOpen(false), isClose(false), parent(NULL), x(0), y(0) {
				}

				Node(int32_t x, int32_t y) : g(0), f(0), h(0), isOpen(false), isClose(false), parent(NULL), x(x), y(y) {
				}

				Node(const Location& key) : g(0), f(0), h(0), isOpen(false), isClose(false), parent(NULL), x(key.x), y(key.y) {
				}

				Node(int32_t x, int32_t y, int32_t h) : g(0), f(0), h(h), isOpen(false), isClose(false), parent(NULL), x(x), y(y) {
				}

				Node(const Location& key, int32_t h) : g(0), f(0), h(h), isOpen(false), isClose(false), parent(NULL), x(key.x), y(key.y) {
				}

				void setGScore(int32_t newG) {
					g = newG;
					f = h + newG;
				};
			};

			struct CompareNodeF {
				bool operator() (Node* a, Node* b) {
					return a->f > b->f;
				}
			} compareNodeF;

			typedef std::unordered_map<Location, Node*> NodeMap;

			NodeMap nodes;
			std::vector<Node*> heap;

			Location end;

			IsOpenCallback callback;

			inline bool isHeapEmpty() const {
				return heap.empty();
			}

			void sortHeap() {
				std::sort(heap.begin(), heap.end(), compareNodeF);
			}

			void pushNode(Node* node) {
				heap.push_back(node);
			}

			Node* popNode() {
				Node* back = heap.back();
				heap.pop_back();

				return back;
			}

			Node* getNode(const Location& key) {
				auto it = nodes.find(key);

				if (it == nodes.end()) {
					int32_t h = 10 * (abs(key.x - end.x) + abs(key.y - end.y));

					Node* node = new Node(key, h);

					nodes.insert(NodeMap::value_type(key, node));

					return node;
				}

				return it->second;
			}

			bool hasNode(const Location& key) {
				return nodes.find(key) != nodes.end();
			}

			bool inCloseList(const Location& key) {
				return hasNode(key) && getNode(key)->isClose;
			}

			void processNeighbour(Node* currentNode, const Location& key) {
				if (!bounds.contains(key)) {
					return;
				}

				int32_t neighbourG = currentNode->g + 10;

				if (isOpen(key) && !inCloseList(key)) {
					Node* neighbour = getNode(key);
					if (!neighbour->isOpen) {
						neighbour->isOpen = true;
						neighbour->parent = currentNode;
						neighbour->setGScore(neighbourG);
						pushNode(neighbour);
						sortHeap();
					}
					else {
						if (neighbour->g < neighbourG) {
							neighbour->parent = currentNode;
							neighbour->setGScore(neighbourG);
							sortHeap();
						}
					}
				}
			}

			PathCrawler* createCrawler(Node* current) {
				Location v;
				Node* n = current;

				PathCrawler* crawler = new PathCrawler(callback);

				while (n) {
					v.set(n->x, n->y);
					crawler->push(v);
					n = n->parent;
				}

				return crawler;
			}

			void clearup() {
				for (auto it = nodes.begin(); it != nodes.end(); ++it) {
					delete it->second;
				}
				nodes.clear();
			}

			bool isOpen(const Location& location) const {
				return callback(location);
			}

			hope::grid::AABox bounds;

		public:
			PathFinder_mine_v1(const hope::grid::AABox& bounds, IsOpenCallback callback) :
				callback(callback),
				bounds(bounds) {
			}

			~PathFinder_mine_v1(){
				clearup();
			}

			PathCrawler* find(const Location& start, int32_t endX, int32_t endY) {
				return find(start.x, start.y, endX, endY);
			}

			PathCrawler* find(const Location& start, const Location& end) {
				return find(start.x, start.y, end.x, end.y);
			}

			PathCrawler* find(int32_t startX, int32_t startY, int32_t endX, int32_t endY) {
				end.set(endX, endY);

				Location key;
				int32_t iteration = 0;
				Node* current;

				key.set(startX, startY);
				Node* startNode = new Node(key);
				nodes.insert(NodeMap::value_type(key, startNode));
				pushNode(startNode);

				while (!isHeapEmpty() && (iteration < 5000)) {
					current = popNode();

					if ((current->x == endX) && (current->y == endY)) {
						PathCrawler* crawler = createCrawler(current);
						return crawler;
					}

					current->isOpen = false;
					current->isClose = true;

					key.set(current->x, current->y + 1);
					processNeighbour(current, key);

					key.set(current->x + 1, current->y);
					processNeighbour(current, key);

					key.set(current->x, current->y - 1);
					processNeighbour(current, key);

					key.set(current->x - 1, current->y);
					processNeighbour(current, key);

					iteration++;
				}
				return NULL;
			}
		};




	} /* namespace grid */
} /* namespace hope */

#endif /* HOPE_GRID_PATHFINDER_H */