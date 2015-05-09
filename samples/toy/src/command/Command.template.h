#ifndef HOPE_SAMPLES_TOY_command_command_H
#define HOPE_SAMPLES_TOY_command_command_H

{{#commands}}
#include "./{{name}}.h"
{{/commands}}

#include <queue>

namespace command {
	typedef uint8_t CommandType;
	typedef uint8_t MappingId;

	const size_t MAPINNG_MAX = 1;

	struct Command {
		CommandType type;
		union {
{{#commands}}
			{{name}} {{name}};
{{/commands}}
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
	
{{#commands}}
	const CommandType {{define_name}} = {{define_value}};
	
	template<> void trigger<{{name}}>(const {{name}}& command);
	template<> void bind<{{name}}>(void(*function)(const {{name}}&));
	template<> void unbind<{{name}}>();

{{/commands}}
}

#endif /* HOPE_SAMPLES_TOY_command_command_H */