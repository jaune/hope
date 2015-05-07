#ifndef HOPE_SAMGLES_TILE_APPLICATION_H
#define HOPE_SAMGLES_TILE_APPLICATION_H

#include <entry/entry.h>
#include "./TileRenderer.h"

class Application : public ::hope::entry::Application {


	void onInitialize(void);
	void onRelease(void);

	void onLoop(void);
	void onResize(int32_t width, int32_t height);

	void onGLInitialize(void);
	void onGLRelease(void);

	TileRenderer gridRenderer;
};

#endif /* HOPE_SAMGLES_TILE_APPLICATION_H */