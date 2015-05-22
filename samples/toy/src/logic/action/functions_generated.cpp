#include "./functions_generated.h"
#include <cassert>

namespace logic {
	namespace action {

		template<>
		Action create<GoToAdjacent::Options>(const GoToAdjacent::Options& options) {
			Action a;

			a.status = Status::NONE;
			a.type = GO_TO_ADJACENT;
			a.options.GO_TO_ADJACENT = options;
			return a;
		}

		template<>
		Action create<Idle::Options>(const Idle::Options& options) {
			Action a;

			a.status = Status::NONE;
			a.type = IDLE;
			a.options.IDLE = options;
			return a;
		}

		template<>
		Action create<machine::OutputPick::Options>(const machine::OutputPick::Options& options) {
			Action a;

			a.status = Status::NONE;
			a.type = MACHINE_OUTPUT_PICK;
			a.options.MACHINE_OUTPUT_PICK = options;
			return a;
		}

		template<>
		Action create<itembag::Give::Options>(const itembag::Give::Options& options) {
			Action a;

			a.status = Status::NONE;
			a.type = ITEMBAG_GIVE;
			a.options.ITEMBAG_GIVE = options;
			return a;
		}

		template<>
		Action create<itembag::Pick::Options>(const itembag::Pick::Options& options) {
			Action a;

			a.status = Status::NONE;
			a.type = ITEMBAG_PICK;
			a.options.ITEMBAG_PICK = options;
			return a;
		}

		template<>
		Action create<deposit::Extract::Options>(const deposit::Extract::Options& options) {
			Action a;

			a.status = Status::NONE;
			a.type = DEPOSIT_EXTRACT;
			a.options.DEPOSIT_EXTRACT = options;
			return a;
		}

		template<>
		Action create<construction::Construct::Options>(const construction::Construct::Options& options) {
			Action a;

			a.status = Status::NONE;
			a.type = CONSTRUCTION_CONSTRUCT;
			a.options.CONSTRUCTION_CONSTRUCT = options;
			return a;
		}


		void process(EntityId actor_id, Action& a) {
			assert(a.status != Status::FAILURE);
			assert(a.status != Status::SUCCESS);			

			switch (a.type) {
			case GO_TO_ADJACENT:
				a.status = GoToAdjacent::process(actor_id, a.status, a.options.GO_TO_ADJACENT, a.state.GO_TO_ADJACENT);
				break;
			case IDLE:
				a.status = Idle::process(actor_id, a.options.IDLE, a.state.IDLE);
				break;
			case MACHINE_OUTPUT_PICK:
				a.status = machine::OutputPick::process(actor_id, a.options.MACHINE_OUTPUT_PICK, a.state.MACHINE_OUTPUT_PICK);
				break;
			case ITEMBAG_GIVE:
				a.status = itembag::Give::process(actor_id, a.options.ITEMBAG_GIVE, a.state.ITEMBAG_GIVE);
				break;
			case ITEMBAG_PICK:
				a.status = itembag::Pick::process(actor_id, a.options.ITEMBAG_PICK, a.state.ITEMBAG_PICK);
				break;
			case DEPOSIT_EXTRACT:
				a.status = deposit::Extract::process(actor_id, a.options.DEPOSIT_EXTRACT, a.state.DEPOSIT_EXTRACT);
				break;
			case CONSTRUCTION_CONSTRUCT:
				a.status = construction::Construct::process(actor_id, a.options.CONSTRUCTION_CONSTRUCT, a.state.CONSTRUCTION_CONSTRUCT);
				break;
			default:
				break;
			}
		}
	}
}

