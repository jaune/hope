#include "./StepTable.h"

namespace hope {
namespace ai {
namespace plan {

StepIndex StepTable::add(const Step& action) {
	Step* newAction = new Step(action);

	newAction->index = steps.size();

	steps.push_back(newAction);

	for (auto effectIt = newAction->effects.begin(); effectIt != newAction->effects.end(); ++effectIt) {
		steps_by_need.insert(StepByNeedMap::value_type(effectIt->type, newAction));
	}

	for (auto condIt = newAction->postconditions.begin(); condIt != newAction->postconditions.end(); ++condIt) {
		steps_by_postconditions.insert(StepByConditionMap::value_type((*condIt), newAction));
	}

	for (auto condIt = newAction->preconditions.begin(); condIt != newAction->preconditions.end(); ++condIt) {
		steps_by_preconditions.insert(StepByConditionMap::value_type((*condIt), newAction));
	}

	return newAction->index;
}


			
void StepTable::findWithAllPostcondition(std::vector<const Step *>& result, const std::vector<const condition::Condition*>& conditions) const {
	std::vector<const Step *> candidates;
	auto condIt = conditions.begin();
	bool test;

	if (condIt != conditions.end()) {
		findWithPostcondition(candidates, (*condIt));
	}

	for (auto candidateIt = candidates.begin(); candidateIt != candidates.end(); ++candidateIt) {
		test = true;

		for (auto condIt = conditions.begin(); condIt != conditions.end(); ++condIt) {
			test = test && (*candidateIt)->hasPostcondition(*condIt);
		}

		if (test) {
			result.push_back((*candidateIt));
		}
	}
}
			


void StepTable::findWithPostcondition(std::vector<const Step *>& actions, const condition::Condition* condition) const {
	auto range = steps_by_postconditions.equal_range(condition);

	for (auto it = range.first; it != range.second; ++it) {
		actions.push_back(it->second);
	}
}

void StepTable::findWithAllPrecondition(std::vector<const Step *>& result, const std::vector<const condition::Condition*>& conditions) const {
	std::vector<const Step *> candidates;
	auto condIt = conditions.begin();
	bool test;

	if (condIt != conditions.end()) {
		findWithPrecondition(candidates, (*condIt));
	}

	for (auto candidateIt = candidates.begin(); candidateIt != candidates.end(); ++candidateIt) {
		test = true;

		for (auto condIt = conditions.begin(); condIt != conditions.end(); ++condIt) {
			test = test && (*candidateIt)->hasPrecondition(*condIt);
		}

		if (test) {
			result.push_back((*candidateIt));
		}
	}
}

void StepTable::findWithPrecondition(std::vector<const Step *>& actions, const condition::Condition* condition) const {
	auto range = steps_by_preconditions.equal_range(condition);

	for (auto it = range.first; it != range.second; ++it) {
		actions.push_back(it->second);
	}
}

void StepTable::find(std::vector<const Step *>& actions, NeedType type) const {
	auto range = steps_by_need.equal_range(type);

	for (auto it = range.first; it != range.second; ++it) {
		actions.push_back(it->second);
	}
}


} /* namespace plan */
} /* namespace ai */
} /* namespace hope */
