#ifndef HOPE_SAMPLES_TOY_LOGIC_ACTION_OPTIONS_H
#define HOPE_SAMPLES_TOY_LOGIC_ACTION_OPTIONS_H

{{#actions}}
#include "./{{{h_path}}}"
{{/actions}}

namespace logic {
	namespace action {

{{#actions}}
		const static action::Type {{define_name}} = {{define_value}};
{{/actions}}

{{#actions}}
		const static char* {{ define_name }}__STRING = "{{define_name}}";
{{/actions}}

		union Options {
{{#actions}}
			{{name}}::Options {{define_name}};
{{/actions}}
		};

		union State {
{{#actions}}
			{{name}}::State {{define_name}};
{{/actions}}
		};

	}
}

#endif /* HOPE_SAMPLES_TOY_LOGIC_ACTION_OPTIONS_H */