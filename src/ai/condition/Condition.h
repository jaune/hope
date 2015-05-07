#ifndef HOPE_AI_CONDITION_CONDITION_H
#define HOPE_AI_CONDITION_CONDITION_H

#include "../../crypto/crypto.h"

namespace hope {
namespace ai {
namespace condition {

	struct ConditionType {
		size_t parametersSize;
	};

	struct Condition {
		const ConditionType* type;
		void* parametersData;

		bool operator==(const Condition &other) const {
			return (type == other.type) && (strncmp((char *)parametersData, (char *)&other.parametersData, sizeof(type->parametersSize)) == 0);
		}
	};
	
} /* namespace condition */
} /* namespace ai */
} /* namespace hope */


namespace std {

	template <>
	struct hash<::hope::ai::condition::Condition>
	{
		std::size_t operator()(const ::hope::ai::condition::Condition& effect) const {
			return ::hope::crypto::crc32((unsigned char*)&effect, sizeof(::hope::ai::condition::Condition));
		}
	};

}

#endif /* HOPE_AI_CONDITION_CONDITION_H */