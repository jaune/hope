#ifndef HOPE_SAMPLES_TOY_logic_action_deposit_Extract_H
#define HOPE_SAMPLES_TOY_logic_action_deposit_Extract_H

#include "../types.h"

namespace logic {
	namespace action {
		namespace deposit {
			namespace Extract {

				struct Options {
					EntityId from_id;
					DepositLevel from_level;
				};

				struct State {
				};

				logic::action::Status process(EntityId actor_id, const Options& options, State& state);
			}
		}
	}
}

#endif /* HOPE_SAMPLES_TOY_logic_action_deposit_Extract_H */
