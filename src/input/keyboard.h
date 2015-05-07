#ifndef HOPE_INPUT_keyboard_H
#define HOPE_INPUT_keyboard_H

#include <cstdint>
#include <unordered_map>

namespace hope {
namespace input {
namespace keyboard {

	typedef int16_t KeyCode;

	const KeyCode KEY_UNKNOWN = 0;
	const KeyCode KEY_A = 4;
	const KeyCode KEY_C = 6;
	const KeyCode KEY_D = 7;
	const KeyCode KEY_E = 8;
	const KeyCode KEY_Q = 20;
	const KeyCode KEY_R = 21;
	const KeyCode KEY_W = 26;
	const KeyCode KEY_Z = 29;
	

	struct Command { 
		virtual void execute() = 0;
	};

	class Mapping {

		typedef std::unordered_map<KeyCode, Command*> CommandMap;
		CommandMap commands;

	public:
		void bind(KeyCode code, Command* command) {
			commands.insert(CommandMap::value_type(code, command));
		}

		void execute(KeyCode code) {
			auto it = commands.find(code);
			
			if (it == commands.end()) {
				return;
			}
			it->second->execute();
		}
	};

	

	void enableMapping(Mapping* mapping);
	void disableMapping();

	void beginUpdateState();
	void endUpdateState();

	void updateKeyState(KeyCode code, bool isDown, bool isPressed);
	

} /* namespace keyboard */
} /* namespace input */
} /* namespace hope */

#endif /* HOPE_INPUT_keyboard_H */