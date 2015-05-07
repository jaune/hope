#ifndef OPENGLES2_WRAPPER_H
#define OPENGLES2_WRAPPER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>

#ifdef __cplusplus
extern "C" {
#endif

	void opengles2_wrapper_load (void);
	void opengles2_wrapper_unload (void);


#ifdef __cplusplus
}
#endif

#endif /* OPENGLES2_WRAPPER_H */