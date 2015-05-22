#ifndef HOPE_SAMPLES_TOY_LOGIC_ACTION_Idle_H
#define HOPE_SAMPLES_TOY_LOGIC_ACTION_Idle_H

#include "./types.h"

namespace logic {
	namespace action {
		namespace Idle {

			struct Options {
			};

			struct State {
			};

			logic::action::Status process(EntityId actor_id, const Options& options, State& state);
		}
	}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_ACTION_Idle_H */
