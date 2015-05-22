#ifndef HOPE_SAMPLES_TOY_LOGIC_ACTION_OPTIONS_H
#define HOPE_SAMPLES_TOY_LOGIC_ACTION_OPTIONS_H

#include "./GoToAdjacent.h"
#include "./Idle.h"
#include "./machine/OutputPick.h"
#include "./itembag/Give.h"
#include "./itembag/Pick.h"
#include "./deposit/Extract.h"
#include "./construction/Construct.h"

namespace logic {
	namespace action {

		const static action::Type GO_TO_ADJACENT = 0x1;
		const static action::Type IDLE = 0x2;
		const static action::Type MACHINE_OUTPUT_PICK = 0x3;
		const static action::Type ITEMBAG_GIVE = 0x4;
		const static action::Type ITEMBAG_PICK = 0x5;
		const static action::Type DEPOSIT_EXTRACT = 0x6;
		const static action::Type CONSTRUCTION_CONSTRUCT = 0x7;

		const static char* GO_TO_ADJACENT__STRING = "GO_TO_ADJACENT";
		const static char* IDLE__STRING = "IDLE";
		const static char* MACHINE_OUTPUT_PICK__STRING = "MACHINE_OUTPUT_PICK";
		const static char* ITEMBAG_GIVE__STRING = "ITEMBAG_GIVE";
		const static char* ITEMBAG_PICK__STRING = "ITEMBAG_PICK";
		const static char* DEPOSIT_EXTRACT__STRING = "DEPOSIT_EXTRACT";
		const static char* CONSTRUCTION_CONSTRUCT__STRING = "CONSTRUCTION_CONSTRUCT";

		union Options {
			GoToAdjacent::Options GO_TO_ADJACENT;
			Idle::Options IDLE;
			machine::OutputPick::Options MACHINE_OUTPUT_PICK;
			itembag::Give::Options ITEMBAG_GIVE;
			itembag::Pick::Options ITEMBAG_PICK;
			deposit::Extract::Options DEPOSIT_EXTRACT;
			construction::Construct::Options CONSTRUCTION_CONSTRUCT;
		};

		union State {
			GoToAdjacent::State GO_TO_ADJACENT;
			Idle::State IDLE;
			machine::OutputPick::State MACHINE_OUTPUT_PICK;
			itembag::Give::State ITEMBAG_GIVE;
			itembag::Pick::State ITEMBAG_PICK;
			deposit::Extract::State DEPOSIT_EXTRACT;
			construction::Construct::State CONSTRUCTION_CONSTRUCT;
		};

	}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_ACTION_OPTIONS_H */