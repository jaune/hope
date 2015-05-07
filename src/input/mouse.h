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

	class DragAndDrop {
		bool is_in_progress;

		::hope::input::mouse::ButtonIndex button_index;

		int32_t startX;
		int32_t startY;

		int32_t deltaX;
		int32_t deltaY;

	public:
		DragAndDrop(::hope::input::mouse::ButtonIndex button_index) :
			startX(0),
			startY(0),
			button_index(button_index),
			is_in_progress(false) {
		}

		enum Status {
			NONE,
			IN_PROGRESS,
			BEGIN,
			END
		};

		inline int32_t isInProgress() const {
			return is_in_progress;
		}

		inline int32_t getDeltaX() const {
			return deltaX;
		}

		inline int32_t getDeltaY() const {
			return deltaY;
		}

		Status process(const ::hope::input::mouse::MouseState& mouseSate) {
			if (!is_in_progress) {
				deltaX = 0;
				deltaY = 0;

				if (mouseSate.buttons[button_index].just_down) {
					is_in_progress = true;
					startX = mouseSate.x;
					startY = mouseSate.y;
					return BEGIN;
				}
			}
			else {
				deltaX = startX - mouseSate.x;
				deltaY = startY - mouseSate.y;

				if (mouseSate.buttons[button_index].just_up) {
					is_in_progress = false;
					return END;
				}
				else {
					return IN_PROGRESS;
				}
			}
			return NONE;
		}

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