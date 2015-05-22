#include "./functions_generated.h"

#include <cassert>

namespace logic {
	namespace action {

		{{#actions}}
		template<>
		Action create<{{name}}::Options>(const {{name}}::Options& options) {
			Action a;

			a.status = Status::NONE;
			a.type = {{define_name}};
			a.options.{{define_name}} = options;
			return a;
		}

		{{/actions}}

		void process(EntityId actor_id, Action& a) {
			assert(a.status != Status::FAILURE);
			assert(a.status != Status::SUCCESS);			

			switch (a.type) {
{{#actions}}
			case {{define_name}}:
				a.status = {{name}}::process(actor_id, a.options.{{define_name}}, a.state.{{define_name}});
				break;
{{/actions}}
			default:
				break;
			}
		}
	}
}

