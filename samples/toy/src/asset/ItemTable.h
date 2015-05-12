#ifndef HOPE_SAMPLES_TOY_asset_ItemTable_H
#define HOPE_SAMPLES_TOY_asset_ItemTable_H

#include <asset/asset.h>
#include <map>
#include <unordered_map>
#include "./ItemTable_generated.h"

namespace asset {
	namespace ItemTable {

		typedef std::unordered_map<int32_t, const asset::fbs::Item*> ItemTableMap;
		
		ItemTableMap gItemTableMap;
		const asset::fbs::ItemTable* gItemTable = NULL;

		void initialize(const char* identifier) {
			hope::asset::Asset asset_ItemTable = hope::asset::get(identifier);
			gItemTable = asset::fbs::GetItemTable(asset_ItemTable.pointer);

			for (auto it = gItemTable->items()->begin(); it != gItemTable->items()->end(); ++it) {
				gItemTableMap.insert(ItemTableMap::value_type(it->id(), *it));
			}
		}

		const asset::fbs::Item* get(int32_t key) {
			return gItemTableMap[key];
		}

		const asset::fbs::ItemTable* all() {
			return gItemTable;
		}

	}
}

#endif /* HOPE_SAMPLES_TOY_asset_ItemTable_H */