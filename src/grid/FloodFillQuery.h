#ifndef HOPE_GRID_FLOODFILLQUERY_H
#define HOPE_GRID_FLOODFILLQUERY_H

#include "./Grid.h"

#include <queue>
#include <functional>


namespace hope {
	namespace grid {


		struct FloodFillQuery {

			size_t width;
			size_t height;
			size_t length;

			const IsOpenCallback callback;

			std::queue<Location> floodFillQueue;
			bool* visitedCells;

			FloodFillQuery(size_t width, size_t height, const IsOpenCallback& callback) :
				width(width),
				height(height),
				length(width * height),
				callback(callback) {
				visitedCells = new bool[length];
				reset();
			}

			~FloodFillQuery(){
				delete[] visitedCells;
			}

			void reset() {
				for (size_t i = 0; i < length; i++) {
					visitedCells[i] = false;
				}
			}

			void queryFloodFill(int32_t x, int32_t y, const hope::grid::Callback& callback) {
				push(x, y);
				while (!floodFillQueue.empty()) {
					const Location& v = floodFillQueue.front();
					floodFillQueue.pop();

					if (isOpen(v.x, v.y) && !isVisited(v.x, v.y)) {
						queryFloodFillLine(v.x, v.y, callback);
					}
				}
			}

			void queryFloodFillLine(int32_t x, int32_t y, const hope::grid::Callback& callback) {
				int32_t xMin = x, xMax;
				int32_t xMinBottom = -1;
				int32_t xMinTop = -1;
				int32_t index;

				bool pulseBottom = false;
				bool pulseTop = false;

				while ((xMin >= 0) && isOpen(xMin, y)) { xMin--; }
				xMin++;
				xMax = xMin;

				while ((xMax < width) && isOpen(xMax, y)) {
					index = xMax + (y * width);
					if (!visitedCells[index] && isOpen(xMax, y - 1)) {
						if (xMinBottom == -1) {
							xMinBottom = xMax;
						}
						if (pulseBottom) {
							push(xMax, y - 1);
							pulseBottom = false;
						}
					}
					else {
						pulseBottom = true;
					}


					if (!visitedCells[index] && isOpen(xMax, y + 1)) {
						if (xMinTop == -1) {
							xMinTop = xMax;
						}
						if (pulseTop) {
							push(xMax, y + 1);
							pulseTop = false;
						}
					}
					else {
						pulseTop = true;
					}
					xMax++;
				}

				if (xMinBottom != -1) {
					push(xMinBottom, y - 1);
				}
				if (xMinTop != -1) {
					push(xMinTop, y + 1);
				}

				for (int32_t i = xMin; i < xMax; i++) {
					index = i + (y * width);

					if (!visitedCells[index]) {
						callback(i, y);
						visitedCells[index] = true;
					}
				}

			}
		private:
			inline void push(int32_t x, int32_t y) {
				if ((y >= 0) && (y < height) && (x >= 0) && (x < width)) {
					floodFillQueue.push({ x, y });
				}
			}
		public:
			inline bool isVisited(int32_t x, int32_t y) const {
				return visitedCells[x + (y * width)];
			}

			inline bool isOpen(int32_t x, int32_t y) const {
				return callback(Location(x, y));
			}

			bool findFirstUnvisitedArea(const hope::grid::Callback& cb) {
				int32_t x, y;

				for (x = 0; x < width; x++) {
					for (y = 0; y < height; y++) {
						if (isOpen(x, y) && !isVisited(x, y)){
							queryFloodFill(x, y, cb);
							return true;
						}
					}
				}
				return false;
			}
		};

	}/* namespace grid */
}/* namespace hope */



#endif /* HOPE_GRID_FLOODFILLQUERY_H */