namespace logic {
namespace action {
namespace machine {

namespace input {
	namespace give {
		struct Action {
		};

		void attach(EntityId actor_id, EntityId machine_id, ItemId item) {
		}
	}
}

namespace output {
	namespace take {
		struct Action {
		};

		void attach(EntityId actor_id, EntityId machine_id, ItemId item) {
			logic::action::Action a;

			a.machine_output_pick =;

			logic::action::attach(actor_id, a);
		}

		void process(const Action& action) {
		}
	}
}

}
}
}

::action::machine::output::pick::attach