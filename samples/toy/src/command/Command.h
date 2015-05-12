#ifndef HOPE_SAMPLES_TOY_command_command_H
#define HOPE_SAMPLES_TOY_command_command_H

#include "./AddConstructionTask.h"
#include "./CancelConstructionTask.h"
#include "./SelectEntity.h"
#include "./StorageSetItemRequestQuantity.h"

#include <queue>

namespace command {
	typedef uint8_t CommandType;
	typedef uint8_t MappingId;

	const size_t MAPINNG_MAX = 1;

	struct Command {
		CommandType type;
		union {
			AddConstructionTask AddConstructionTask;
			CancelConstructionTask CancelConstructionTask;
			SelectEntity SelectEntity;
			StorageSetItemRequestQuantity StorageSetItemRequestQuantity;
		};
	};
	
	bool initialize();

	void trigger(const command::Command& command);
	
	template<typename T>
	void trigger(const T& command) { static_assert(false, "Missing command.") }

	bool pool(command::Command& command);

	MappingId createMapping();
	void destroyMapping(MappingId mapping);
	void activeMapping(MappingId mapping);
	void disableMapping();
	void dispatch();

	template <typename T>
	void bind(void(*function)(const T&)) { static_assert(false, "Missing command."); }

	template <typename T>
	void unbind() { static_assert(false, "Missing command."); }
	
	const CommandType ADD_CONSTRUCTION_TASK = 0x1;
	
	template<> void trigger<AddConstructionTask>(const AddConstructionTask& command);
	template<> void bind<AddConstructionTask>(void(*function)(const AddConstructionTask&));
	template<> void unbind<AddConstructionTask>();

	const CommandType CANCEL_CONSTRUCTION_TASK = 0x2;
	
	template<> void trigger<CancelConstructionTask>(const CancelConstructionTask& command);
	template<> void bind<CancelConstructionTask>(void(*function)(const CancelConstructionTask&));
	template<> void unbind<CancelConstructionTask>();

	const CommandType SELECT_ENTITY = 0x3;
	
	template<> void trigger<SelectEntity>(const SelectEntity& command);
	template<> void bind<SelectEntity>(void(*function)(const SelectEntity&));
	template<> void unbind<SelectEntity>();

	const CommandType STORAGE_SET_ITEM_REQUEST_QUANTITY = 0x4;
	
	template<> void trigger<StorageSetItemRequestQuantity>(const StorageSetItemRequestQuantity& command);
	template<> void bind<StorageSetItemRequestQuantity>(void(*function)(const StorageSetItemRequestQuantity&));
	template<> void unbind<StorageSetItemRequestQuantity>();

}

#endif /* HOPE_SAMPLES_TOY_command_command_H */