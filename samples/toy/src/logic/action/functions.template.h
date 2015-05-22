#ifndef HOPE_SAMPLES_TOY_LOGIC_ACTION_FUNCTIONS_H
#define HOPE_SAMPLES_TOY_LOGIC_ACTION_FUNCTIONS_H

#include "./action.h"

namespace logic {
	namespace action {

		template<typename T>
		Action create(const T& options) { static_assert(false, "Missing action"); }

		{{#actions}}
		template<>
		Action create<{{name}}::Options>(const {{name}}::Options& options);
		{{/actions}}

		void process(EntityId actor_id, Action& a);
	}
}


#endif /* HOPE_SAMPLES_TOY_LOGIC_ACTION_FUNCTIONS_H */