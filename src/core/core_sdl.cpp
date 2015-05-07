#include "core.h"

#include <SDL2/SDL.h>

namespace hope {
namespace core {


  uint32_t getTicks (void) {
    return SDL_GetTicks();
  }

  void getViewportSize(int32_t *w, int32_t *h) {
	  SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), w, h);
  }




} /* namespace core */
} /* namespace hope */