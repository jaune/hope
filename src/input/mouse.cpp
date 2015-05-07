#include "mouse.h"

namespace hope {
namespace input {
namespace mouse {

static MouseState kState;
static bool kFirstUpdate = true;

void getPosition(int32_t *x, int32_t *y) {
	*x = kState.x;
	*y = kState.y;
}

const MouseState& getMouseState() {
	return kState;
}

void beginUpdateState() {
	if (kFirstUpdate) {
		kFirstUpdate = false;
	}
	
	kState.scroll.deltaX = 0;
	kState.scroll.deltaY = 0;

	size_t i;

	for (i = 0; i < 256; i++) {
		kState.buttons[i].just_down = false;
		kState.buttons[i].just_up = false;
	}
	
}

void updateButton(size_t buttonIndex, bool isJustDown, bool isPress) {
	kState.buttons[buttonIndex].down = isPress;

	if (isJustDown) {
		kState.buttons[buttonIndex].just_down = true;
	}
	else {
		kState.buttons[buttonIndex].just_up = true;
	}
	
}

void endUpdateState() {

}

void updatePosition(int32_t x, int32_t y) {
	kState.x = x;
	kState.y = y;
}

void updateScrollDelta(int32_t x, int32_t y) {
	kState.scroll.deltaX = x;
	kState.scroll.deltaY = y;
}


} /* namespace mouse */
} /* namespace input */
} /* namespace hope */