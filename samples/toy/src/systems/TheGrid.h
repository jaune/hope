#ifndef HOPE_SAMPLES_TOY_system_TheGrid_H
#define HOPE_SAMPLES_TOY_system_TheGrid_H

#include "../TheGridSystem.h"

namespace systems {
	
	TheGridSystem* TheGrid() {
		static TheGridSystem* system = NULL;

		if (system == NULL) {
			system = new TheGridSystem();
		}

		return system;
	}

};

#endif /* HOPE_SAMPLES_TOY_system_TheGrid_H */