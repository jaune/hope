#ifndef HOPE_SAMPLES_TOY_LOGIC_ACTION_ACTION_H
#define HOPE_SAMPLES_TOY_LOGIC_ACTION_ACTION_H

#include "./types.h"
#include "./options_generated.h"

namespace logic {
	namespace action {

		struct Action {
			Status status;
			Type type;

			Options options;
			State state;
		};

	};
};


#endif /* HOPE_SAMPLES_TOY_LOGIC_ACTION_ACTION_H */