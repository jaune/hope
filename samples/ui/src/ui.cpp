#include "./Application.h"

namespace hope {
namespace entry {

	hope::entry::Application* createApplication() {
		return new ::Application();
	}

} /* namespace entry */
} /* namespace hope */

