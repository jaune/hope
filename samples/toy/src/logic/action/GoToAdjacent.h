#ifndef HOPE_SAMPLES_TOY_LOGIC_ACTION_GoToAdjacent_H
#define HOPE_SAMPLES_TOY_LOGIC_ACTION_GoToAdjacent_H

#include "./types.h"

namespace logic {
	namespace action {
		namespace GoToAdjacent {

			struct Options {
				EntityId to_id;
			};

			struct State {
				PathId path_id;
			};

			logic::action::Status process(EntityId actor_id, logic::action::Status status, const Options& options, State& state);
		}
	}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_ACTION_GoToAdjacent_H */
