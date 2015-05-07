#include "console.h"

#include <SDL2/SDL.h>

namespace hope {
namespace console {

	void log(const char * format, ...) {
		va_list args;
		va_start(args, format);

		//SDL_Log(format, args);
		SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, format, args);

		va_end(args);
	}

} /* namespace console */
} /* namespace hope */