#include "./GoToAdjacent.h"

#include "../../Components.h"

#include "../path.h"

namespace logic {
	namespace action {
		namespace GoToAdjacent {
			logic::action::Status process(EntityId actor_id, logic::action::Status status, const Options& options, State& state) {

				if (status == Status::NONE){

					auto path_id = logic::path::create(actor_id, options.to_id);

					if (path_id == 0) {
						return logic::action::FAILURE;
					}

					state.path_id = path_id;
				}

				if (!logic::path::next(state.path_id)){
					logic::path::destroy(state.path_id);
					return logic::action::FAILURE;
				}

				auto dataLocation = Components::get<LocationComponent>(actor_id);

				dataLocation->position = logic::path::current(state.path_id);
				
				if (logic::path::empty(state.path_id)){
					logic::path::destroy(state.path_id);
					state.path_id = 0;
					return logic::action::SUCCESS;
				}
				
				return logic::action::IN_PROGRESS;
			}

		}
	}
}
