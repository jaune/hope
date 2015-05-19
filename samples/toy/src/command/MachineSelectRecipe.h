#ifndef HOPE_SAMPLES_TOY_command_MachineSelectRecipe_H
#define HOPE_SAMPLES_TOY_command_MachineSelectRecipe_H

#include "../types.h"

namespace command {

	struct MachineSelectRecipe {
		EntityId machine_id;
		CraftRecipeId recipe_id;
	};

}

#endif /* HOPE_SAMPLES_TOY_command_MachineSelectRecipe_H */