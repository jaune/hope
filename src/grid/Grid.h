#ifndef HOPE_GRID_GRID_H
#define HOPE_GRID_GRID_H

#include "./Location.h"

#include <vector>
#include <queue>
#include <map>
#include <functional>
#include <unordered_map>

namespace hope {
	namespace grid {

		typedef std::function<void(int32_t, int32_t)> Callback;
		typedef std::function<bool(const Location&)> IsOpenCallback;


		struct AABox {
			int32_t xMax;
			int32_t yMax;

			int32_t xMin;
			int32_t yMin;

			AABox() :
				xMax(0),
				yMax(0),
				xMin(0),
				yMin(0) {
			}

			void set(const Location& location, int32_t top, int32_t right, int32_t bottom, int32_t left) {
				setX(location.x + right, location.x - left);
				setY(location.y + top, location.y - bottom);
			}

			inline bool isZero() const {
				return xMax == 0 && yMax == 0 && xMin == 0 && yMin == 0;
			}

			inline bool contains(int32_t x, int32_t y) const {
				return (x <= xMax) && (x >= xMin) && (y <= yMax) && (y >= yMin);
			}

			inline bool contains(const Location& location) const {
				return (location.x <= xMax) && (location.x >= xMin) && (location.y <= yMax) && (location.y >= yMin);
			}

			void addLocation(const Location& location){
				xMin = (location.x < xMin) ? location.x : xMin;
				yMin = (location.y < yMin) ? location.y : yMin;

				xMax = (location.x > xMax) ? location.x : xMax;
				yMax = (location.y > yMax) ? location.y : yMax;
			}

			void setX(int32_t a, int32_t b) {
				xMin = (a < b) ? a : b;
				xMax = (a > b) ? a : b;
			}

			void setY(int32_t a, int32_t b) {
				yMin = (a < b) ? a : b;
				yMax = (a > b) ? a : b;
			}

			inline int32_t width() const {
				return xMax - xMin;
			}

			inline int32_t height() const {
				return yMax - yMin;
			}
		};


		template <typename T>
		struct GridMapWithDefault {

			typedef T Cell;

			size_t width;
			size_t height;
			AABox bounds;
			Cell defaultCell;

			typedef std::unordered_map<Location, Cell> CellMap;

			CellMap cells;

			GridMapWithDefault(size_t width, size_t height, const Cell& defaultCell) :
				width(width),
				height(height),
				defaultCell(defaultCell) {

				bounds.yMin = 0;
				bounds.xMin = 0;

				bounds.yMax = height;
				bounds.xMax = width;
			}

			size_t getWidth() const {
				return width;
			}

			size_t getHeight() const {
				return height;
			}

			void setAllToDefault() {
				cells.clear();
			}

			void setToDefault(const Location& location) {
				auto it = cells.find(location);

				if (it != cells.end()) {
					cells.erase(it);
				}
			}

			void setToDefault(int32_t x, int32_t y) {
				return setToDefault(Location(x, y));
			}

			void set(const Location& location, const Cell& cell){
				auto it = cells.find(location);

				if (it != cells.end()) {
					cells[location] = cell;
				}
				else {
					cells.insert(CellMap::value_type(location, cell));
				}
			}

			void set(int32_t x, int32_t y, const Cell& cell){
				set(Location(x, y), cell);
			}



			const Cell& get(const Location& location) const {
				auto it = cells.find(location);

				if (it == cells.end()) {
					return defaultCell;
				}

				return it->second;
			}

			const Cell& get(int32_t x, int32_t y) const {
				return get(Location(x, y));
			}

			Cell* find(const Location& location) {
				auto it = cells.find(location);

				if (it == cells.end()) {
					return NULL;
				}

				return &it->second;
			}

			Cell* find(int32_t x, int32_t y) {
				return find(Location(x, y));
			}
		};

		template <typename T>
		struct GridMapWithoutDefault {

			typedef T Cell;

			size_t width;
			size_t height;
			AABox aabox;

			typedef std::unordered_map<Location, Cell> CellMap;

			CellMap cells;

			GridMapWithoutDefault(size_t width, size_t height) :
				width(width),
				height(height) {

				aabox.yMin = 0;
				aabox.xMin = 0;

				aabox.yMax = height;
				aabox.xMax = width;
			}

			void set(const Location& location, const Cell& cell){
				if (cells.size() == 0) {
					aabox.xMin = aabox.xMax = location.x;
					aabox.yMin = aabox.yMax = location.y;
				}
				else if (cells.size() > 0) {
					aabox.addLocation(location);
				}

				auto it = cells.find(location);

				if (it != cells.end()) {
					cells[location] = cell;
				}
				else {
					cells.insert(CellMap::value_type(location, cell));
				}
			}

			void set(int32_t x, int32_t y, const Cell& cell){
				set(Location(x, y), cell);
			}

			void setToNull(int32_t x, int32_t y){
				setToNull(Location(x, y));
			}

			void setToNull(const Location& location) {
				auto it = cells.find(location);

				if (it != cells.end()) {
					cells.erase(it);
				}
			}

			Cell* find(const Location& location) {
				auto it = cells.find(location);

				if (it == cells.end()) {
					return NULL;
				}

				return &it->second;
			}

			const Cell* find(const Location& location) const {
				auto it = cells.find(location);

				if (it == cells.end()) {
					return NULL;
				}

				return &it->second;
			}

			const Cell* find(int32_t x, int32_t y) const {
				return find(Location(x, y));
			}
		};

		struct AbstractGrid {

		};

		template <typename T>
		struct Grid {

			typedef T Cell;

			Cell* cells;
			size_t width;
			size_t height;
			int32_t length;

			AABox aabox;

			Grid(size_t width, size_t height) :
				width(width),
				height(height) {

				length = width * height;

				aabox.yMin = 0;
				aabox.xMin = 0;

				aabox.yMax = height;
				aabox.xMax = width;

				cells = new Cell[length];
			}

			~Grid() {
				delete[] cells;
			}

			inline bool in(size_t x, size_t y) const {
				return x >= 0 && x < width && y >= 0 && y < height;
			}

			inline bool in(const Location& l) const {
				return l.x >= 0 && l.x < width && l.y >= 0 && l.y < height;
			}

			inline Cell* at(size_t x, size_t y){
				return cells + (x + (y * width));
			}

			inline Cell* at(const Location& l){
				return cells + (l.x + (l.y * width));
			}

			inline const Cell* at(size_t x, size_t y) const {
				return cells + (x + (y * width));
			}

			inline const Cell* at(const Location& l) const {
				return cells + (l.x + (l.y * width));
			}


			void queryFillRect(int32_t x, int32_t y, int32_t w, int32_t h, Callback callback) {
				Cell* c;
				int32_t xMax = x + w;
				int32_t yMax = y + h;

				xMax = (xMax < width) ? xMax : width;
				yMax = (yMax < height) ? yMax : height;

				int32_t xMin;
				int32_t yMin;

				for (xMin = (x >= 0) ? x : 0; xMin < xMax; xMin++) {
					for (yMin = (y >= 0) ? y : 0; yMin < yMax; yMin++) {
						callback(xMin, yMin);
					}
				}
			}

			void queryStrokeRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t b, Callback callback) {
				queryFillRect(x, y, w, b, callback);
				queryFillRect(x, y + (h - b), w, b, callback);
				queryFillRect(x, y + b, b, h - (2 * b), callback);
				queryFillRect(x + (w - b), y + b, b, h - (2 * b), callback);
			}

			void queryRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t b, Callback fillCallback, Callback strokeCallback) {
				queryStrokeRect(x, y, w, h, b, strokeCallback);

				int32_t fw = w - (b * 2);
				int32_t fh = h - (b * 2);

				if (fw > 0 && fh > 0) {
					queryFillRect(x + b, y + b, fw, fh, fillCallback);
				}

			}
		};


		struct IsOpenCell {
			bool isOpen;
		};

		struct IsOpenGrid : public Grid < IsOpenCell > {

			IsOpenGrid(int32_t w, int32_t h) : Grid<IsOpenCell>(w, h) {
				size_t index;

				for (index = 0; index < length; index++) {
					cells[index].isOpen = false;
				}
			}

			bool isOpen(const Location& l) const {
				return !at(l)->isOpen;
			}

			bool isOpen(size_t x, size_t y) const {
				return !at(x, y)->isOpen;
			}
		};


	} /* namespace grid */
} /* namespace hope */

#endif /* HOPE_GRID_GRID_H */