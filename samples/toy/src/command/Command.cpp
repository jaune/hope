#include "./Command.h"
#include <cassert>

namespace command {

	struct Mapping {
		bool alive;

		void(*AddConstructionTask_function)(const AddConstructionTask&);
		void(*CancelConstructionTask_function)(const CancelConstructionTask&);
		void(*SelectEntity_function)(const SelectEntity&);
		void(*StorageSetItemRequestQuantity_function)(const StorageSetItemRequestQuantity&);
	};

	static MappingId gActiveMapping = 0;
	static Mapping gMappings[MAPINNG_MAX];
	static std::queue<command::Command> gCommandQueue;

	void trigger(const command::Command& command) {
		gCommandQueue.push(command);
	}

	bool pool(command::Command& command) {
		if (gCommandQueue.empty()){
			return false;
		}

		command = gCommandQueue.front();
		gCommandQueue.pop();

		return true;
	}

	void clearMapping(Mapping& mapping) {
		mapping.alive = false;

		mapping.AddConstructionTask_function = NULL;
		mapping.CancelConstructionTask_function = NULL;
		mapping.SelectEntity_function = NULL;
		mapping.StorageSetItemRequestQuantity_function = NULL;
	}

	bool initialize() {
		for (size_t i = 1; i < MAPINNG_MAX; ++i) {
			clearMapping(gMappings[i]);
		}
		return true;
	}
	
	MappingId createMapping() {
		for (size_t i = 0; i < MAPINNG_MAX; ++i) {
			if (gMappings[i].alive == false) {
				gMappings[i].alive = true;
				return gActiveMapping = i + 1;
			}
		}
		return 0;
	}

	void destroyMapping(MappingId mapping) {
		if (mapping == 0){
			return;
		}
		if (mapping == gActiveMapping) {
			disableMapping();
		}
		clearMapping(gMappings[mapping - 1]);
	}

	void activeMapping(MappingId mapping) {
		if (mapping == 0){
			return;
		}
		gActiveMapping = mapping;
	}

	void disableMapping() {
		gActiveMapping = 0;
	}

	template<>
	void trigger<AddConstructionTask>(const AddConstructionTask& command) {
		command::Command c;
		c.type = ADD_CONSTRUCTION_TASK;
		c.AddConstructionTask = command;
		trigger(c);
	}

	template <>
	void bind<AddConstructionTask>(void(*function)(const AddConstructionTask&)) {
		gMappings[gActiveMapping - 1].AddConstructionTask_function = function;
	}

	template <>
	void unbind<AddConstructionTask>() {
		gMappings[gActiveMapping - 1].AddConstructionTask_function = NULL;
	}
	template<>
	void trigger<CancelConstructionTask>(const CancelConstructionTask& command) {
		command::Command c;
		c.type = CANCEL_CONSTRUCTION_TASK;
		c.CancelConstructionTask = command;
		trigger(c);
	}

	template <>
	void bind<CancelConstructionTask>(void(*function)(const CancelConstructionTask&)) {
		gMappings[gActiveMapping - 1].CancelConstructionTask_function = function;
	}

	template <>
	void unbind<CancelConstructionTask>() {
		gMappings[gActiveMapping - 1].CancelConstructionTask_function = NULL;
	}
	template<>
	void trigger<SelectEntity>(const SelectEntity& command) {
		command::Command c;
		c.type = SELECT_ENTITY;
		c.SelectEntity = command;
		trigger(c);
	}

	template <>
	void bind<SelectEntity>(void(*function)(const SelectEntity&)) {
		gMappings[gActiveMapping - 1].SelectEntity_function = function;
	}

	template <>
	void unbind<SelectEntity>() {
		gMappings[gActiveMapping - 1].SelectEntity_function = NULL;
	}
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

	void dispatch() {
		if (gActiveMapping == 0) {
			return;
		}

		MappingId index = gActiveMapping - 1;
		const Mapping& mapping = gMappings[index];

		if (!mapping.alive) {
			return;
		}

		command::Command command;

		while (command::pool(command)) {
			switch (command.type) {
			case ADD_CONSTRUCTION_TASK:
				if (mapping.AddConstructionTask_function != NULL) {
					mapping.AddConstructionTask_function(command.AddConstructionTask);
				}
				break;
			case CANCEL_CONSTRUCTION_TASK:
				if (mapping.CancelConstructionTask_function != NULL) {
					mapping.CancelConstructionTask_function(command.CancelConstructionTask);
				}
				break;
			case SELECT_ENTITY:
				if (mapping.SelectEntity_function != NULL) {
					mapping.SelectEntity_function(command.SelectEntity);
				}
				break;
			case STORAGE_SET_ITEM_REQUEST_QUANTITY:
				if (mapping.StorageSetItemRequestQuantity_function != NULL) {
					mapping.StorageSetItemRequestQuantity_function(command.StorageSetItemRequestQuantity);
				}
				break;
			}
		}
	}
}