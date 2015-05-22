#ifndef HOPE_SAMPLES_TOY_LOGIC_ACTION_TYPES_H
#define HOPE_SAMPLES_TOY_LOGIC_ACTION_TYPES_H

#include "../../types.h"

namespace logic {
	namespace action {

		enum Status {
			NONE,
			IN_PROGRESS,
			SUCCESS,
			FAILURE
		};

		typedef uint8_t Type;
	};
};

#endif /* HOPE_SAMPLES_TOY_LOGIC_ACTION_TYPES_H */