#ifndef HOPE_SAMPLES_TOY_RESOURCE_ItemTable_H
#define HOPE_SAMPLES_TOY_RESOURCE_ItemTable_H

#include <asset/asset.h>
#include <map>
#include <unordered_map>
#include "../ItemTable_generated.h"

namespace resource {
	namespace ItemTable {

		typedef std::unordered_map<int32_t, const hope::samples::toy::fbs::Item*> ItemTableMap;
		
		ItemTableMap gItemTableMap;
		const hope::samples::toy::fbs::ItemTable* gItemTable = NULL;

		void initialize(const char* identifier) {
			hope::asset::Asset asset_ItemTable = hope::asset::get(identifier);
			gItemTable = hope::samples::toy::fbs::GetItemTable(asset_ItemTable.pointer);

			for (auto it = gItemTable->items()->begin(); it != gItemTable->items()->end(); ++it) {
				gItemTableMap.insert(ItemTableMap::value_type(it->id(), *it));
			}
		}

		const hope::samples::toy::fbs::Item* get(int32_t key) {
			return gItemTableMap[key];
		}

		const hope::samples::toy::fbs::ItemTable* all() {
			return gItemTable;
		}

	}
}

#endif /* HOPE_SAMPLES_TOY_RESOURCE_ItemTable_H */