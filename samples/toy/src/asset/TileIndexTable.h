#ifndef HOPE_SAMPLES_TOY_TileIndexTable_H
#define HOPE_SAMPLES_TOY_TileIndexTable_H

#include "./CellType.h"
#include "./TileIndexes_generated.h"

template <size_t SIZE>
struct TileIndexKey {
	CellType center;
	CellType neighbours[SIZE];
	uint32_t variant;

	TileIndexKey(CellType center) :
		center(center),
		variant(0) {
	}

	bool operator== (const TileIndexKey& other) const {
		if (center != other.center || variant != other.variant) {
			return false;
		}

		for (size_t i = 0; i < SIZE; i++) {
			if (neighbours[i] != other.neighbours[i]) {
				return false;
			}
		}

		return true;
	}
};

struct TileIndexKey4 : public TileIndexKey < 4 > {
	TileIndexKey4(CellType center, CellType top, CellType left, CellType bottom, CellType right) :
		TileIndexKey<4>(center) {

		neighbours[0] = top;
		neighbours[1] = left;
		neighbours[2] = bottom;
		neighbours[3] = right;
	}
};

struct TileIndexKey8 : public TileIndexKey < 8 > {
	TileIndexKey8(CellType center, CellType top, CellType topleft, CellType left, CellType leftbottom, CellType bottom, CellType bottomright, CellType right, CellType righttop) :
		TileIndexKey<8>(center) {

		neighbours[0] = top;
		neighbours[1] = topleft;
		neighbours[2] = left;
		neighbours[3] = leftbottom;
		neighbours[4] = bottom;
		neighbours[5] = bottomright;
		neighbours[6] = right;
		neighbours[7] = righttop;
	}
};

namespace std {
	template<>
	struct hash < TileIndexKey4 >
	{
		size_t operator()(const TileIndexKey4& key) const {
			return hope::crypto::crc32((uint8_t*)&key, sizeof(key));
		}
	};

	template<>
	struct hash < TileIndexKey8 >
	{
		size_t operator()(const TileIndexKey8& key) const {
			return hope::crypto::crc32((uint8_t*)&key, sizeof(key));
		}
	};
}

class TileIndexTable {

	typedef std::unordered_map<TileIndexKey4, uint8_t> Map4;
	typedef std::unordered_map<TileIndexKey8, uint8_t> Map8;

	Map4 indexes4;
	Map8 indexes8;

private:
	void set(CellType center, CellType top, CellType left, CellType bottom, CellType right, uint8_t index) {
		TileIndexKey4 key(center, top, left, bottom, right);

		indexes4.insert(Map4::value_type(key, index));
	}

	void set(CellType center, CellType top, CellType topleft, CellType left, CellType leftbottom, CellType bottom, CellType bottomright, CellType right, CellType righttop, uint8_t index) {
		TileIndexKey8 key(center, top, topleft, left, leftbottom, bottom, bottomright, right, righttop);

		indexes8.insert(Map8::value_type(key, index));
	}

public:
	uint8_t get(CellType center, CellType top, CellType left, CellType bottom, CellType right) {
		TileIndexKey4 key(center, top, left, bottom, right);

		auto it = indexes4.find(key);
		if (it == indexes4.end()) {
			return 0;
		}
		return it->second;

	}

	uint8_t get(CellType center, CellType top, CellType topleft, CellType left, CellType leftbottom, CellType bottom, CellType bottomright, CellType right, CellType righttop) {
		TileIndexKey8 key(center, top, topleft, left, leftbottom, bottom, bottomright, right, righttop);

		auto it = indexes8.find(key);
		if (it == indexes8.end()) {
			return get(center, top, left, bottom, right);
		}
		return it->second;
	}


	bool initializeFromAssets(const hope::asset::Asset& asset) {
		if (asset.is_null()) {
			return false;
		}

		const asset::fbs::TileIndexes *indexes = asset::fbs::GetTileIndexes(asset.pointer);

		for (auto it = indexes->indexes4()->begin(); it != indexes->indexes4()->end(); ++it) {
			set((CellType)it->center(),
				(CellType)it->top(), (CellType)it->right(), (CellType)it->bottom(), (CellType)it->left(),
				it->index());
		}

		for (auto it = indexes->indexes8()->begin(); it != indexes->indexes8()->end(); ++it) {
			set((CellType)it->center(),
				(CellType)it->top(), (CellType)it->topright(), (CellType)it->right(), (CellType)it->bottomright(), (CellType)it->bottom(), (CellType)it->bottomleft(), (CellType)it->left(), (CellType)it->topleft(),
				it->index());
		}

		return true;
	}
};

#endif /* HOPE_SAMPLES_TOY_TileIndexTable_H */