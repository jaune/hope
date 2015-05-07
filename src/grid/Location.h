#ifndef HOPE_GRID_LOCATION_H
#define HOPE_GRID_LOCATION_H

#include <cstdint>

namespace hope {
namespace grid {

	enum Direction {
		TOP,
		RIGHT,
		BOTTOM,
		LEFT
	};

struct Location {
	int32_t x, y;

	Location() : x(0), y(0) {
	}

	Location(int32_t x, int32_t y) : x(x), y(y) {
	}

	void set(int32_t x, int32_t y) {
		this->x = x;
		this->y = y;
	}

	void set(const Location& l) {
		x = l.x;
		y = l.y;
	}

	bool operator==(const Location& other) const{
		return (x == other.x) && (y == other.y);
	}

	bool operator!=(const Location& other) const{
		return (x != other.x) || (y != other.y);
	}

	float distance (const Location& other) const {
		return sqrtf(distanceSquare(other));
	}


	int32_t distanceSquare (const Location& other) const {
		int32_t d = (x - other.x) * (x - other.x);

		d += (y - other.y) * (y - other.y);

		return d;
	}

	inline Location getTopNeighbor() const {
		return Location(x, y + 1);
	}

	inline Location getRightNeighbor() const {
		return Location(x + 1, y);
	}

	inline Location getBottomNeighbor() const {
		return Location(x, y - 1);
	}

	inline Location getLeftNeighbor() const {
		return Location(x - 1, y);
	}

	void getTopNeighbor(Location& other) {
		other.set(x, y + 1);
	}

	void getRightNeighbor(Location& other) {
		other.set(x + 1, y);
	}

	void getBottomNeighbor(Location& other) {
		other.set(x, y - 1);
	}

	void getLeftNeighbor(Location& other) {
		other.set(x - 1, y);
	}

	void get4Neighbors(Location neighbors[4]) {
		getTopNeighbor(neighbors[0]);
		getRightNeighbor(neighbors[1]);
		getBottomNeighbor(neighbors[2]);
		getLeftNeighbor(neighbors[3]);
	}

};

} /* namespace grid */
} /* namespace hope */

namespace std {
	template <> struct hash<hope::grid::Location>
	{
		size_t operator()(const hope::grid::Location & value) const
		{
			return hash<int32_t>()(value.x) ^ (hash<int32_t>()(value.y) >> 1);
		}
	};
}

#endif /* HOPE_GRID_LOCATION_H */