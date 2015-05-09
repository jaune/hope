#ifndef HOPE_INPUT_MOUSE_H
#define HOPE_INPUT_MOUSE_H

#include <stdint.h>

namespace hope {
namespace input {
namespace mouse {

	enum ButtonIndex{
		BOUTON_LEFT = 1,
		BOUTON_RIGHT = 3,
		BOUTON_MIDDLE = 2
	};



	struct ScrollState {
		int32_t deltaX;
		int32_t deltaY;
	};
	
	struct DragState {
		enum Status {
			NONE = 0,
			START,
			MOVE,
			END
		};

		Status status;

		int32_t deltaX;
		int32_t deltaY;

		int32_t startX;
		int32_t startY;
	};

	struct ButtonState {
		bool down;

		bool just_down;
		bool just_up;

		DragState drag;
	};

	struct MouseState {
		int32_t x;
		int32_t y;

		ScrollState scroll;
		ButtonState buttons[256];
	};

	const MouseState& getMouseState();

	void getPosition(int32_t *x, int32_t *y);

	void beginUpdateState();
	void endUpdateState();
	void updatePosition(int32_t x, int32_t y);
	void updateButton(size_t buttonIndex, bool isDown, bool isPressed);
	void updateScrollDelta(int32_t x, int32_t y);

} /* namespace mouse */
} /* namespace input */
} /* namespace hope */

#endif /* HOPE_INPUT_MOUSE_H */