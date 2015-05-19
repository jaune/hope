#ifndef HOPE_SAMPLES_TOY_LOGIC_STORAGE_H
#define HOPE_SAMPLES_TOY_LOGIC_STORAGE_H

#include "../types.h"
#include "./location.h"

#include "../logic/plan/extract.h"
#include "../logic/plan/store.h"

namespace logic {
namespace storage {
	
	EntityId create(const hope::grid::Location& location) {
		EntityId id = Entities::create();

		Components::attach<LocationComponent>(id)->position.set(location);
		Components::attach<ItemBagComponent>(id);
		Components::attach<StorageComponent>(id);

		Components::attach<TileIndexComponent>(id)->index = (5 * 16) + 0;

		return id;
	}

	void findInArea(EntityId storage_id, ComponentMask mask, std::vector<EntityId>& result){
		auto location_c = Components::get<LocationComponent>(storage_id);

		std::vector<EntityId> candidates;
		hope::grid::AABox box;

		int32_t size = 50;
		int32_t size_2 = size / 2;

		box.setX(location_c->position.x - size_2, location_c->position.x + size_2);
		box.setY(location_c->position.y - size_2, location_c->position.y + size_2);

		logic::location::findAtLocation(box, candidates);

		for (auto it = candidates.begin(); it != candidates.end(); ++it) {
			if (Entities::testComponentMask(*it, mask)) {
				result.push_back(*it);
			}
		}
	}

	bool tryAssignBestRequestMachine(EntityId storage_id, EntityId agent_id){
		auto bag_c = Components::get<ItemBagComponent>(storage_id);
		auto storage_c = Components::get<StorageComponent>(storage_id);

		std::vector<EntityId> candidates;
		
		findInArea(storage_id, MachineComponent::COMPONENT_MASK, candidates);

		for (auto it = candidates.begin(); it != candidates.end(); ++it) {
			auto machine_c = Components::get<MachineComponent>(*it);
			if (machine_c->output.getTotalQuantity() > 0) {
				for (auto item : machine_c->output.items) {
					plan::store::assign(agent_id, storage_id, *it, item.first);
				}
				return true;
			}
		}
		return false;
	}

	EntityId tryAssignBestRequestDeposit(EntityId storage_id, EntityId agent_id) {
		auto storage_c = Components::get<StorageComponent>(storage_id);
		auto bag_c = Components::get<ItemBagComponent>(storage_id);

		std::vector<EntityId> candidates;

		findInArea(storage_id, DepositComponent::COMPONENT_MASK, candidates);

		for (auto it = candidates.begin(); it != candidates.end(); ++it) {
			auto deposit_c = Components::get<DepositComponent>(*it);
			if (deposit_c->getItemQuantity(0) > 0){
				ItemQuantity q = bag_c->items.getItemQuantity(deposit_c->item_id);
				ItemQuantity r = storage_c->request_quantities.getItemQuantity(deposit_c->item_id);

				if (q < r) {
					logic::plan::extract::assign(agent_id, storage_id, *it);
					return true;
				}
			}
		}
		return false;
	}



}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_STORAGE_H */