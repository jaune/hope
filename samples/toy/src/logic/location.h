#ifndef HOPE_SAMPLES_TOY_logic_Location_H
#define HOPE_SAMPLES_TOY_logic_Location_H

#include <grid/Location.h>
#include "../Components.h"

namespace logic {
	namespace location {

		void findAtLocation(const hope::grid::AABox& box, std::vector<EntityId>& result);

		EntityId findAtLocation(const hope::grid::Location& location);

	}
}


#endif /* HOPE_SAMPLES_TOY_entity_Location_H */