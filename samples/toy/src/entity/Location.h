#ifndef HOPE_SAMPLES_TOY_entity_Location_H
#define HOPE_SAMPLES_TOY_entity_Location_H

#include <grid/Location.h>
#include "../Components.h"

namespace entity {

	EntityId findAtLocation(const hope::grid::Location& location){
		std::vector<EntityId> result;

		Entities::findByComponentMask(LocationComponent::COMPONENT_MASK, result);

		if (result.empty()){
			return 0;
		}

		for (auto it = result.begin(); it != result.end(); ++it) {
			if (Components::get<LocationComponent>(*it)->position == location) {
				return *it;
			}
		}

		return 0;
	}

}


#endif /* HOPE_SAMPLES_TOY_entity_Location_H */