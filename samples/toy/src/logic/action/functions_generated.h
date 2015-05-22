#ifndef HOPE_SAMPLES_TOY_LOGIC_ACTION_FUNCTIONS_H
#define HOPE_SAMPLES_TOY_LOGIC_ACTION_FUNCTIONS_H

#include "./action.h"

namespace logic {
	namespace action {

		template<typename T>
		Action create(const T& options) { static_assert(false, "Missing action"); }

		template<>
		Action create<GoToAdjacent::Options>(const GoToAdjacent::Options& options);
		template<>
		Action create<Idle::Options>(const Idle::Options& options);
		template<>
		Action create<machine::OutputPick::Options>(const machine::OutputPick::Options& options);
		template<>
		Action create<itembag::Give::Options>(const itembag::Give::Options& options);
		template<>
		Action create<itembag::Pick::Options>(const itembag::Pick::Options& options);
		template<>
		Action create<deposit::Extract::Options>(const deposit::Extract::Options& options);
		template<>
		Action create<construction::Construct::Options>(const construction::Construct::Options& options);

		void process(EntityId actor_id, Action& a);
	}
}


#endif /* HOPE_SAMPLES_TOY_LOGIC_ACTION_FUNCTIONS_H */