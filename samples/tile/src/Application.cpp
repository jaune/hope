#include "Application.h"

#include <entry/entry.h>
#include <core/core.h>
#include <console.h>
#include <input/mouse.h>
#include <asset/asset.h>
#include <nvg.h>
#include <GLES2/gl2.h>


#include <grid/Grid.h>

#include <gles2/Framebuffer.h>

hope::gles2::Framebuffer fb;


enum ResourceCellType {
	IRON = 0,
	ALUMINUM,
	WATER,
	CARBON,
	SILICON
};

struct ResourceCell {
	int32_t x;
	int32_t y;

	ResourceCellType type;
	int32_t quantity;
};

typedef hope::grid::GridMapWithoutDefault<ResourceCell> ResourceGrid;

static ResourceGrid kResources(256, 256);

int32_t toTileIndex(const ResourceCell& cell) {
	int32_t base = 0;

	switch (cell.type) {
	case WATER: {
		base = (0 * 16) + 12;
		break;
	}
	case CARBON: {
		base = (1 * 16) + 12;
		break;
	}
	case SILICON: {
		base = (2 * 16) + 12;
		break;
	}
	case ALUMINUM: {
		base = (3 * 16) + 12;
		break;
	}
	case IRON: {
		base = (4 * 16) + 12;
		break;
	}
	}

	if (cell.quantity < 2000) {
		base += (cell.quantity / 500) - 1;
	}
	else {
		base += 3;
	}


	return base;
}



void Application::onInitialize(void) {

	ResourceCell c;

	srand(0xFF00FF);
		
	for (size_t i = 0; i < 1000; i++) {
		c.x = rand() % kResources.width;
		c.y = rand() % kResources.height;
		c.quantity = rand() % 2000 + 500;
		c.type = (ResourceCellType)(rand() % 5);

		kResources.set(c.x, c.y, c);
	}

}


void Application::onRelease(void) {
}

uint32_t lastTime = 0, currentTime, elaspsedTime;

float kZoom = 1.f;

void Application::onLoop(void) {
	const ::hope::input::mouse::MouseState& mouseSate = ::hope::input::mouse::getMouseState();

	int32_t winWidth = 1024, winHeight = 768;
	int blowup = 0;

	hope::core::getViewportSize(&winWidth, &winHeight);

	currentTime = hope::core::getTicks();

	elaspsedTime = currentTime - lastTime;

	lastTime = currentTime;

	// -------------------------- UPDATE

	gridRenderer.zoom((float)mouseSate.scroll.deltaY / 16.0f);

	// -------------------------- UPDATE

	float_t xCenter = winWidth / 2.0f;
	float_t yCenter = winHeight / 2.0f;

	float xMouse = (mouseSate.x - xCenter) / 10.f;
	float yMouse = (mouseSate.y - yCenter) / -10.f;

	if (mouseSate.buttons[1].down){
		fb.begin();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		gridRenderer.render();

		fb.end();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	::hope::nanovg::beginFrame();

	// ---------------------------- DRAW

	nvgBeginStackTextLeft(); {
		nvgStackText("scroll: %i ; %i (%f)", mouseSate.scroll.x, mouseSate.scroll.y, kZoom);
	}

	nvgBeginStackTextRight(); {
		
	}

	// ---------------------------- DRAW

	::hope::nanovg::endFrame();

	
	fb.render();
	
}

void Application::onResize(int width, int height) {
	glViewport(0, 0, width, height);

	gridRenderer.resize(width, height);
	fb.resize(width, height);
}


void Application::onGLInitialize() {
	if (!::hope::nanovg::initialize()) {
		exit(42);
	}

	

	::hope::nanovg::loadFont("Roboto-Regular.ttf", "sans");
		
	int32_t winWidth = 1024, winHeight = 768;
	hope::core::getViewportSize(&winWidth, &winHeight);

	fb.initialize(winWidth, winHeight);

	gridRenderer.initialize(kResources.width, kResources.height, "tiles.png(webp)", "grid.vert", "grid.frag");
	gridRenderer.resize(winWidth, winHeight);
	for (auto it = kResources.cells.begin(); it != kResources.cells.end(); ++it) {
		gridRenderer.set(it->second.x, it->second.y, toTileIndex(it->second));
	}
	gridRenderer.commit();
}

void Application::onGLRelease(void) {
	gridRenderer.release();
	::hope::nanovg::release();
}

