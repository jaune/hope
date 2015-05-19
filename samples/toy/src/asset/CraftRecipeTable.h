#ifndef HOPE_SAMPLES_TOY_asset_CraftRecipeTable_H
#define HOPE_SAMPLES_TOY_asset_CraftRecipeTable_H

#include <asset/asset.h>
#include <map>
#include <unordered_map>
#include "./CraftRecipeTable_generated.h"

namespace asset {
	namespace CraftRecipeTable {

		typedef std::unordered_map<int32_t, const asset::fbs::CraftRecipe*> TableMap;
		
		TableMap gTableMap;
		const asset::fbs::CraftRecipeTable* gTable = NULL;

		void initialize(const char* identifier) {
			hope::asset::Asset asset = hope::asset::get(identifier);
			gTable = asset::fbs::GetCraftRecipeTable(asset.pointer);

			for (auto it = gTable->recipes()->begin(); it != gTable->recipes()->end(); ++it) {
				gTableMap.insert(TableMap::value_type(it->id(), *it));
			}
		}

		const asset::fbs::CraftRecipe* get(int32_t key) {
			return gTableMap[key];
		}

		const asset::fbs::CraftRecipeTable* all() {
			return gTable;
		}

	}
}

#endif /* HOPE_SAMPLES_TOY_asset_CraftRecipeTable_H */