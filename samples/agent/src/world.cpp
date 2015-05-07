#include "world.h"

Location World::findNearestDeposit(ResourceType type) const {
	size_t length = store_Deposit.pool_cursor;
	const Deposit* items = store_Deposit.pool;
	const Deposit* item = items;
	const Deposit* end = items + length;

	Location l;

	l.x = 0;
	l.y = 0;

	for (; item != end; item++) {
		if (item->type == type) {

			l.x = item->position.x;
			l.y = item->position.y;

			return l;
		}
	}

	return l;
}



const char* toString(GaugeType type) {
	switch (type) {
	case GaugeType::EAT: return "Eat";
	case GaugeType::DRINK: return "Drink";
	case GaugeType::SLEEP: return "Sleep";
	default: return "<unknown>";
	}
}
