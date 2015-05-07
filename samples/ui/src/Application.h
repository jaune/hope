#ifndef HOPE_SAMPLES_UI_APPLICATION_H
#define HOPE_SAMPLES_UI_APPLICATION_H

#include <entry/entry.h>

class Application : public ::hope::entry::Application {


	void onInitialize(void);
	void onRelease(void);

	void onLoop(void);
	void onResize(int32_t width, int32_t height);

	void onGLInitialize(void);
	void onGLRelease(void);

};

#endif /* HOPE_SAMPLES_UI_APPLICATION_H */