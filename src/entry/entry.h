#ifndef HOPE_ENTRY_ENTRY_H
#define HOPE_ENTRY_ENTRY_H

#include <stddef.h>
#include <stdint.h>

namespace hope {
namespace entry {

	class Application {

	public:
		virtual void onInitialize(void) = 0;
		virtual void onRelease(void) = 0;


		virtual void onLoop(void) = 0;
		virtual void onResize(int32_t width, int32_t height) = 0;

		virtual void onGLInitialize(void) = 0;
		virtual void onGLRelease(void) = 0;
	};

	Application* createApplication();

}
}
    

#endif /* HOPE_ENTRY_ENTRY_H */