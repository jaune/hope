#ifndef HOPE_SAMPLES_TOY_command_AddConstructionTask_H
#define HOPE_SAMPLES_TOY_command_AddConstructionTask_H

#include "../types.h"

namespace command {

	struct AddConstructionTask {
		int x;
		int y;
		
		int width;
		int height;

		int  fill_recipe_id;
		int  stroke_width;
		int  stroke_recipe_id;
	};

}

#endif /* HOPE_SAMPLES_TOY_command_AddConstructionTask_H */