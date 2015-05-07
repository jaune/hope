#include "entry.h"

#include "../input/mouse.h"
#include "../input/keyboard.h"
#include "../asset/asset.h"

#include <SDL2/SDL.h>
// #include <SDL2/SDL_opengles2.h>

#include "../opengles2_wrapper.h"

SDL_Window *window;
SDL_GLContext context;
int running = SDL_TRUE;

int a = SDL_SCANCODE_0;

static ::hope::entry::Application* kApplciation = NULL;

void do_loop() {

	hope::input::mouse::beginUpdateState();
	hope::input::keyboard::beginUpdateState();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP: {
			hope::input::mouse::updateButton(event.button.button, event.button.type == SDL_MOUSEBUTTONDOWN, event.button.state == SDL_PRESSED);
			hope::input::mouse::updatePosition(event.button.x, event.button.y);
			break;
		}

		case SDL_MOUSEWHEEL: {
			hope::input::mouse::updateScrollDelta(event.wheel.x, event.wheel.y);
			break;
		}

		case SDL_MOUSEMOTION: {
			hope::input::mouse::updatePosition(event.motion.x, event.motion.y);
			break;
		}

		case SDL_KEYDOWN:
		case SDL_KEYUP: {
			hope::input::keyboard::updateKeyState(event.key.keysym.scancode, event.key.repeat != 0, event.key.state == SDL_PRESSED);
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
            break;
        }
    }

	hope::input::mouse::endUpdateState();
	hope::input::keyboard::endUpdateState();
    
    kApplciation->onLoop();
}

void assets_unload() {

}



extern C_LINKAGE int main(int argc, char *argv[]) {
	kApplciation = ::hope::entry::createApplication();

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL_Init failed: %s\n", SDL_GetError());
		return 1;
	}
	

	::hope::asset::load();

	kApplciation->onInitialize();

	int w_width = 1024, w_height = 768;

	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2) != 0) {
		SDL_Log("SDL_GL_SetAttribute SDL_GL_CONTEXT_MAJOR_VERSION failed: %s\n", SDL_GetError());
		return 1;
	}
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) != 0) {
		SDL_Log("SDL_GL_SetAttribute SDL_GL_CONTEXT_MINOR_VERSION failed: %s\n", SDL_GetError());
		return 1;
	}

	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES) != 0) {
		SDL_Log("SDL_GL_SetAttribute SDL_GL_CONTEXT_PROFILE_MASK failed: %s\n", SDL_GetError());
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

	opengles2_wrapper_load();

	kApplciation->onGLInitialize();

	kApplciation->onResize(w_width, w_height);

	while (running == SDL_TRUE) {
		do_loop();
		SDL_GL_SwapWindow(window);
	}

	kApplciation->onGLRelease();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);

	kApplciation->onRelease();

	SDL_Quit();

	delete kApplciation;

	return 0;
}


