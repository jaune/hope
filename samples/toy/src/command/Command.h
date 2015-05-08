#ifndef HOPE_SAMPLES_TOY_command_command_H
#define HOPE_SAMPLES_TOY_command_command_H

#include "./StorageSetItemRequestQuantity.h"
#include "./SetStorageId.h"

#include <queue>

namespace command {

	typedef uint8_t CommandType;
	typedef uint8_t MappingId;

	const size_t MAPINNG_MAX = 1;

	struct Mapping {
		bool alive;
		// generated ?!
		void(*StorageSetItemRequestQuantity_function)(const StorageSetItemRequestQuantity&);
		void(*SetStorageId_function)(const SetStorageId&);
		// generated ?!
	};


	MappingId gActiveMapping = 0;
	Mapping gMappings[MAPINNG_MAX];

	struct Command {
		CommandType type;
		union {
			// generated ?!
			StorageSetItemRequestQuantity StorageSetItemRequestQuantity;
			SetStorageId SetStorageId;
			// generated ?!
		};
	};

	std::queue<command::Command> commands;

	inline void trigger(const command::Command& command) { commands.push(command); }

	template<typename T>
	void trigger(const T& command) { static_assert(false, "Missing command.") }

	
	bool pool(command::Command& command) {
		if (commands.empty()){
			return false;
		}

		command = commands.front();
		commands.pop();

		return true;
	}

	// ----------------

	void clearMapping(Mapping& mapping) {
		gMappings[gActiveMapping - 1].alive = false;
		// generated ?!
		gMappings[gActiveMapping - 1].StorageSetItemRequestQuantity_function = NULL;
		gMappings[gActiveMapping - 1].SetStorageId_function = NULL;
		// generated ?!

	}

	bool initialize() {
		for (size_t i = 1; i < MAPINNG_MAX; ++i) {
			clearMapping(gMappings[i]);
		}

		return true;
	}

	// ----------------



	MappingId createMapping() {
		for (size_t i = 0; i < MAPINNG_MAX; ++i) {
			if (gMappings[i].alive == false) {
				return gActiveMapping = i + 1;
			}
		}
		return 0;
	}

	void destroyMapping(MappingId mapping) {
		clearMapping(gMappings[gActiveMapping - 1]);
	}	

	void activeMapping(MappingId mapping) {
		gActiveMapping = mapping;
	}

	void disableMapping() {
		gActiveMapping = 0;
	}

	template <typename T>
	void bind(void(*function)(const T&)) { static_assert(false, "Missing command."); }

	template <typename T>
	void unbind() { static_assert(false, "Missing command."); }

	// generated ?!
	const CommandType STORAGE_SET_ITEM_REQUEST_QUANTITY = 0x01;
	
	template<>
	void trigger<StorageSetItemRequestQuantity>(const StorageSetItemRequestQuantity& command) {
		command::Command c;
		c.type = STORAGE_SET_ITEM_REQUEST_QUANTITY;
		c.StorageSetItemRequestQuantity = command;
		trigger(c);
	}

	template <>
	void bind<StorageSetItemRequestQuantity>(void(*function)(const StorageSetItemRequestQuantity&)) {
		gMappings[gActiveMapping - 1].StorageSetItemRequestQuantity_function = function;
	}

	template <>
	void unbind<StorageSetItemRequestQuantity>() {
		gMappings[gActiveMapping - 1].StorageSetItemRequestQuantity_function = NULL;
	}
	// generated ?!
	
	// generated ?!
	const CommandType SET_STORAGE_ID = 0x02;

	template<>
	void trigger<SetStorageId>(const SetStorageId& command) {
		command::Command c;
		c.type = SET_STORAGE_ID;
		c.SetStorageId = command;
		trigger(c);
	}

	template <>
	void bind<SetStorageId>(void(*function)(const SetStorageId&)) {
		gMappings[gActiveMapping - 1].SetStorageId_function = function;
	}

	template <>
	void unbind<SetStorageId>() {
		gMappings[gActiveMapping - 1].SetStorageId_function = NULL;
	}
	// generated ?!

	


	// ----------------

	void dispatch() {
		if (gActiveMapping == 0) {
			return;
		}

		command::Command command;

		while (command::pool(command)) {
			switch (command.type) {
			// generated ?!
			case STORAGE_SET_ITEM_REQUEST_QUANTITY: 
				if (gMappings[gActiveMapping - 1].StorageSetItemRequestQuantity_function != NULL) {
					gMappings[gActiveMapping - 1].StorageSetItemRequestQuantity_function(command.StorageSetItemRequestQuantity);
				}
				break;

			case SET_STORAGE_ID:
				if (gMappings[gActiveMapping - 1].SetStorageId_function != NULL) {
					gMappings[gActiveMapping - 1].SetStorageId_function(command.SetStorageId);
				}
				break;
			
			// generated ?!
			}
		}
	}

	
}

#endif /* HOPE_SAMPLES_TOY_command_command_H */