#ifndef HOPE_SAMPLES_TOY_LOGIC_PLAN_STATUS_H
#define HOPE_SAMPLES_TOY_LOGIC_PLAN_STATUS_H
namespace logic {
	namespace plan {
		enum Status {
			NONE = 0,
			SUCCESS,
			FAILURE,
			IN_PROGRESS
		};
	}
}
#endif /* HOPE_SAMPLES_TOY_LOGIC_PLAN_STATUS_H */