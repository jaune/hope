#include "entry/entry.h"

#include <GLES2/gl2.h>
#define NANOVG_GLES2_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h>

#include "nanovg/demo.h"

#include "core/core.h"
#include "console.h"
#include "input/mouse.h"


NVGcontext* vg = NULL;
DemoData data;

unsigned int lastTime = 0, currentTime;

namespace hope {

namespace entry {

    void onInitialize (void) {
    }

	void onRelease (void) {
    }

    void onLoop (void) {
		int32_t mx = 0, my = 0;
        int32_t winWidth = 1024, winHeight = 768;
        float pxRatio;
        int blowup = 0;

		hope::input::mouse::getPosition(&mx, &my);
		hope::core::getViewportSize(&winWidth, &winHeight);
        
        pxRatio = 1;

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);


        nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

		currentTime = hope::core::getTicks();

        renderDemo(vg, (float)mx, (float)my, winWidth, winHeight, (double)currentTime / (double)1000, blowup, &data);

        lastTime = currentTime;

        nvgEndFrame(vg);
    }

    void onResize(int width, int height) {
		glViewport(0, 0, width, height);
    }

    void onGLInitialize() {
        vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
        //vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        if (vg == NULL) {
            ::hope::console::log("nvgCreateGLES2\n");
            exit (42);
        }

        if (loadDemoData(vg, &data) == -1) {
			::hope::console::log("loadDemoData\n");
        }
    }

    void onGLRelease(void) {
        freeDemoData(vg, &data);
        nvgDeleteGLES2(vg);
    }

} /* namespace entry */

} /* namespace hope */



