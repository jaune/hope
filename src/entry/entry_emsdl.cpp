#include "entry.h"

#include "../input/mouse.h"
#include "../asset/asset.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#include <emscripten.h>

SDL_Window *window;
SDL_GLContext context;
int running = SDL_TRUE;

void do_loop () {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                SDL_Log("SDL_MOUSEBUTTONDOWN\n");
            break;
			case SDL_MOUSEMOTION: {
				hope::input::mouse::SampleData data;

				data.x = event.motion.x;
				data.y = event.motion.y;

				hope::input::mouse::updateSample(data);

				break;
			}
            case SDL_WINDOWEVENT:
                SDL_Log("SDL_WINDOWEVENT\n");
                switch (event.window.event) {
                     case SDL_WINDOWEVENT_RESIZED:
                     SDL_Log("SDL_WINDOWEVENT_RESIZED\n");
                     if (context) {
                        // resize (event.window.data1, event.window.data2)
                     }
                    break;
                }
            break;
            case SDL_QUIT:
                running = SDL_FALSE;
                emscripten_cancel_main_loop();
            break;
        }
    }

    ::hope::entry::onLoop();
}

void do_nothing () { }

extern C_LINKAGE int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL_Init failed: %s\n", SDL_GetError());
		return 1;
	}

    ::hope::entry::onInitialize();

	emscripten_set_main_loop(do_nothing, 0, 0);

	::hope::asset::load();

	int w_width = 1024, w_height = 768;

	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2) != 0) {
		SDL_Log("SDL_GL_SetAttribute SDL_GL_CONTEXT_MAJOR_VERSION failed: %s\n", SDL_GetError());
		return 1;
	}
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) != 0) {
		SDL_Log("SDL_GL_SetAttribute SDL_GL_CONTEXT_MINOR_VERSION failed: %s\n", SDL_GetError());
		return 1;
	}

	if (SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1) != 0) {
		SDL_Log("SDL_GL_SetAttribute SDL_GL_STENCIL_SIZE failed: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w_width, w_height, SDL_WINDOW_OPENGL);
	if (!window) {
		SDL_Log("SDL_CreateWindow failed: %s\n", SDL_GetError());
		return 1;
	}

	context = SDL_GL_CreateContext(window);
	if (!context) {
		SDL_Log("SDL_GL_CreateContext failed: %s\n", SDL_GetError());
	}

    ::hope::entry::onGLInitialize();

    ::hope::entry::onResize(w_width, w_height);

    emscripten_cancel_main_loop();
	emscripten_set_main_loop(do_loop, 0, 1);

    ::hope::entry::onGLRelease();

    SDL_GL_DeleteContext(context);  
    SDL_DestroyWindow(window);

    ::hope::entry::onRelease();

    SDL_Quit();

    return 0;
}



