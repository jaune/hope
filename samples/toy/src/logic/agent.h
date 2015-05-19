#ifndef HOPE_SAMPLES_TOY_LOGIC_AGENT_H
#define HOPE_SAMPLES_TOY_LOGIC_AGENT_H

#include "../types.h"
#include "./location.h"

namespace logic {
namespace agent {

	EntityId create(const char* label, const hope::grid::Location& location) {
		EntityId id = Entities::create();

		Components::attach<LocationComponent>(id)->position.set(location);
		Components::attach<ItemBagComponent>(id);
		Components::attach<AgentComponent>(id)->label = label;
		Components::attach<LaborComponent>(id)->labor = 1000;

		Components::attach<TileIndexComponent>(id)->index = 253;

		return id;
	}

};
};

#endif /* HOPE_SAMPLES_TOY_LOGIC_AGENT_H */