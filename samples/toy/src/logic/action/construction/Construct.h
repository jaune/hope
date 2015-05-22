#ifndef HOPE_SAMPLES_TOY_logic_action_construction_construct_H
#define HOPE_SAMPLES_TOY_logic_action_construction_construct_H

#include "../types.h"

namespace logic {
	namespace action {
		namespace construction {
			namespace Construct {

				struct Options {
					EntityId task_id;
				};

				struct State {
				};

				logic::action::Status process(EntityId actor_id, const Options& options, State& state);
			}
		}
	}
}

#endif /* HOPE_SAMPLES_TOY_logic_action_construction_construct_H */
