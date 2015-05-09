#ifndef HOPE_SAMPLES_TOY_command_CancelConstructionTask_H
#define HOPE_SAMPLES_TOY_command_CancelConstructionTask_H

#include "../types.h"

namespace command {

	struct CancelConstructionTask {
		int x;
		int y;
		
		int width;
		int height;
	};

}

#endif /* HOPE_SAMPLES_TOY_command_CancelConstructionTask_H */