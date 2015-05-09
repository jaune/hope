#include "./Command.h"
#include <cassert>

namespace command {

	struct Mapping {
		bool alive;

{{#commands}}
		void(*{{name}}_function)(const {{name}}&);
{{/commands}}
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

{{#commands}}
		mapping.{{name}}_function = NULL;
{{/commands}}
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

{{#commands}}
	template<>
	void trigger<{{name}}>(const {{name}}& command) {
		command::Command c;
		c.type = {{define_name}};
		c.{{name}} = command;
		trigger(c);
	}

	template <>
	void bind<{{name}}>(void(*function)(const {{name}}&)) {
		gMappings[gActiveMapping - 1].{{name}}_function = function;
	}

	template <>
	void unbind<{{name}}>() {
		gMappings[gActiveMapping - 1].{{name}}_function = NULL;
	}
{{/commands}}

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
{{#commands}}
			case {{define_name}}:
				if (mapping.{{name}}_function != NULL) {
					mapping.{{name}}_function(command.{{name}});
				}
				break;
{{/commands}}
			}
		}
	}
}