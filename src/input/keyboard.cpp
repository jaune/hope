#include "keyboard.h"

#include "../console.h"

namespace hope {
namespace input {
namespace keyboard {

	static Mapping* kActiveMapping = NULL;

	void enableMapping(Mapping* mapping) {
		kActiveMapping = mapping;
	}

	void disableMapping() {
		kActiveMapping = NULL;	
	}

	void updateKeyState(KeyCode code, bool isDown, bool isPressed) {
		if (kActiveMapping == NULL) {
			return;
		}

		if (!isDown && isPressed) {
			kActiveMapping->execute(code);
		}
	}

	void beginUpdateState() {
	}
	void endUpdateState() {
	}

} /* namespace keyboard */
} /* namespace input */
} /* namespace hope */