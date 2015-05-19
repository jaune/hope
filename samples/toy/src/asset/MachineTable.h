#ifndef HOPE_SAMPLES_TOY_asset_MachineTable_H
#define HOPE_SAMPLES_TOY_asset_MachineTable_H

#include <asset/asset.h>
#include <map>
#include <unordered_map>
#include "./MachineTable_generated.h"

namespace asset {
	namespace MachineTable {

		typedef std::unordered_map<int32_t, const asset::fbs::Machine*> TableMap;
		
		TableMap gTableMap;
		const asset::fbs::MachineTable* gTable = NULL;

		void initialize(const char* identifier) {
			hope::asset::Asset asset = hope::asset::get(identifier);
			gTable = asset::fbs::GetMachineTable(asset.pointer);

			for (auto it = gTable->machines()->begin(); it != gTable->machines()->end(); ++it) {
				gTableMap.insert(TableMap::value_type(it->id(), *it));
			}
		}

		const asset::fbs::Machine* get(int32_t key) {
			return gTableMap[key];
		}

		const asset::fbs::MachineTable* all() {
			return gTable;
		}

	}
}

#endif /* HOPE_SAMPLES_TOY_asset_MachineTable_H */