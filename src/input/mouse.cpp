#include "mouse.h"

namespace hope {
namespace input {
namespace mouse {

MouseState gState;
MouseState gLastState;
bool gFirstUpdate = true;


void getPosition(int32_t *x, int32_t *y) {
	*x = gState.x;
	*y = gState.y;
}

const MouseState& getMouseState() {
	return gState;
}

void beginUpdateState() {
	gState.scroll.deltaX = 0;
	gState.scroll.deltaY = 0;

	for (size_t i = 0; i < 256; i++) {
		gState.buttons[i].just_down = false;
		gState.buttons[i].just_up = false;
	}
}

void updateButton(size_t buttonIndex, bool isJustDown, bool isPress) {
	gState.buttons[buttonIndex].down = isPress;

	if (isJustDown) {
		gState.buttons[buttonIndex].just_down = true;
	}
	else {
		gState.buttons[buttonIndex].just_up = true;
	}
	
}

void endUpdateState() {
	if (!gFirstUpdate){
		for (size_t i = 0; i < 256; i++) {
			ButtonState& b = gState.buttons[i];

			if (b.drag.status == DragState::NONE) {
				if (!b.just_down && b.down && (gLastState.x != gState.x || gLastState.y != gState.y)) {
					b.drag.status = DragState::START;
					b.drag.startX = gLastState.x;
					b.drag.startY = gLastState.y;
				}
			}
			else {
				if (b.down) {
					b.drag.deltaX = gState.x - b.drag.startX;
					b.drag.deltaY = gState.y - b.drag.startY;
					b.drag.status = DragState::MOVE;
				}
				else if (b.just_up) {
					b.drag.status = DragState::END;
				}
				else if (b.drag.status == DragState::END){
					b.drag.status = DragState::NONE;
				}
			}			
		}

	}
	else {
		for (size_t i = 0; i < 256; i++) {
			gState.buttons[i].drag.status = DragState::NONE;
		}
	}
	

	gLastState = gState;

	if (gFirstUpdate) {
		gFirstUpdate = false;
	}
}

void updatePosition(int32_t x, int32_t y) {
	gState.x = x;
	gState.y = y;
}

void updateScrollDelta(int32_t x, int32_t y) {
	gState.scroll.deltaX = x;
	gState.scroll.deltaY = y;
}


} /* namespace mouse */
} /* namespace input */
} /* namespace hope */