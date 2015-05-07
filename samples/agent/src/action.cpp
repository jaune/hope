#include "action.h"

const char* toString(ActionType type) {
	switch (type) {
	case ActionType::IDLE_ACTION: return "IDLE_ACTION";
	case ActionType::GOTO_ACTION: return "GOTO_ACTION";
	case ActionType::GOTO_DEPOSIT_ACTION: return "GOTO_DEPOSIT_ACTION";
	case ActionType::CONSUME_ACTION: return "CONSUME_ACTION";
	case ActionType::SLEEP_ON_GROUND: return "SLEEP_ON_GROUND";
	default: return "<unknown>";
	}
}

