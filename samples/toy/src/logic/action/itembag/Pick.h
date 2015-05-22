#ifndef HOPE_SAMPLES_TOY_LOGIC_ACTION_ITEMBAG_PICK_H
#define HOPE_SAMPLES_TOY_LOGIC_ACTION_ITEMBAG_PICK_H

#include "../types.h"

namespace logic {
	namespace action {
		namespace itembag {
			namespace Pick {

				struct Options {
					EntityId from_id;
					ItemId item_id;
				};

				struct State {
				};

				logic::action::Status process(EntityId actor_id, const Options& options, State& state);

			}
		}
	}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_ACTION_ITEMBAG_PICK_H */