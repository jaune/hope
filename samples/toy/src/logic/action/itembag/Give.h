#ifndef HOPE_SAMPLES_TOY_LOGIC_ACTION_ITEMBAG_GIVE_H
#define HOPE_SAMPLES_TOY_LOGIC_ACTION_ITEMBAG_GIVE_H

#include "../types.h"

namespace logic {
	namespace action {
		namespace itembag {
			namespace Give {

				struct Options {
					EntityId to_id;
					ItemId item_id;
				};

				struct State {
				};

				logic::action::Status process(EntityId actor_id, const Options& options, State& state);

			}
		}
	}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_ACTION_ITEMBAG_GIVE_H */