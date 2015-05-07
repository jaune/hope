#ifndef HOPE_SAMGLES_AGENT_ACTION_H
#define HOPE_SAMGLES_AGENT_ACTION_H

#include "resource.h"

struct Location {
	float x, y;
};

enum ActionType {
	IDLE_ACTION = 0,
	GOTO_ACTION,
	GOTO_DEPOSIT_ACTION,
	SLEEP_ON_GROUND,
	CONSUME_ACTION
};

const char* toString(ActionType type);

struct ExtractAction {
	float quantity;
};

struct GoToAction{
	Location location;
};

struct ConsumeAction {
	ResourceType type;
};

struct GoToDepositAction {
	ResourceType type;
};

struct Action {
	ActionType type;

	Action() : type(IDLE_ACTION) {}

	union {
		GoToAction GoToAction;
		GoToDepositAction GoToDepositAction;
		ExtractAction ExtractAction;
		ConsumeAction ConsumeAction;
	};
};

#endif /* HOPE_SAMGLES_AGENT_ACTION_H */