#ifndef HOPE_SAMPLES_TOY_LOGIC_MACHINE_H
#define HOPE_SAMPLES_TOY_LOGIC_MACHINE_H

#include "../types.h"
#include "./location.h"

namespace logic {
namespace machine {
	
	EntityId create(const hope::grid::Location& location, MachineType type, TileIndex tile) {
		EntityId id = Entities::create();

		Components::attach<LocationComponent>(id)->position.set(location);
		Components::attach<TileIndexComponent>(id)->index = tile;
		auto m = Components::attach<MachineComponent>(id);

		m->type = type;
		m->recipe_id = 0;
		m->duration = 0;

		m->input_max = 200;
		m->output_max = 200;

		return id;
	}


	void craft() {
		std::vector<EntityId> result;

		Entities::findByComponentMask(MachineComponent::COMPONENT_MASK, result);

		for (auto it = result.begin(); it != result.end(); ++it){
			EntityId machine_id = *it;
			auto machine_c = Components::get<MachineComponent>(machine_id);

			if (machine_c->recipe_id == 0){
				continue;
			}

			auto recipe = asset::CraftRecipeTable::get(machine_c->recipe_id);

			if (machine_c->duration == 0) {
				bool test = true;
				ItemQuantity output_total = machine_c->output.getTotalQuantity();

				for (auto item : *recipe->input()) {
					if (machine_c->input.getItemQuantity(item->item_id()) < item->quantity()){
						test = false;
					}
				}

				for (auto item : *recipe->output()) {
					output_total += item->quantity();
				}

				if (output_total > machine_c->output_max) {
					test = false;
				}

				if (test) {
					for (auto item : *recipe->input()) {
						machine_c->input.addItemQuantity(item->item_id(), -item->quantity());
						machine_c->inner.addItemQuantity(item->item_id(), item->quantity());
					}
					machine_c->duration++;
				}
				
			} else if (machine_c->duration >= recipe->duration()) {
				for (auto item : *recipe->output()) {
					machine_c->output.addItemQuantity(item->item_id(), item->quantity());
					machine_c->inner.items.clear();
				}
				machine_c->duration = 0;
			}
			else {
				machine_c->duration++;
			}
		}
	}

}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_MACHINE_H */