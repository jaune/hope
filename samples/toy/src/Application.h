#ifndef HOPE_SAMGLES_TOY_APPLICATION_H
#define HOPE_SAMGLES_TOY_APPLICATION_H

#include <entry/entry.h>
#include <input/keyboard.h>
#include <ai/System.h>
#include <world/Store.h>

#include "./TileRenderer.h"



class Application : public ::hope::entry::Application {

	struct Command : public ::hope::input::keyboard::Command {
		Application* application;

	public:
		Command(Application* application) :
			application(application) {
		}
	};

	struct BeginCancelConstructionCommand : public Command {
		BeginCancelConstructionCommand(Application* application) : Command(application) {}
		void execute();
	};

	struct BeginFloorConstructionCommand : public Command {
		BeginFloorConstructionCommand(Application* application) : Command(application) {}
		void execute();
	};

	struct BeginWallConstructionCommand : public Command {
		BeginWallConstructionCommand(Application* application) : Command(application) {}
		void execute();
	};

	struct BeginRoomConstructionCommand : public Command {
		BeginRoomConstructionCommand(Application* application) : Command(application) {}
		void execute();
	};

	

	template<class T>
	Command* createCommad(){
		return new T(static_cast<Application*>(this));
	}


	void onInitialize(void);
	void onRelease(void);

	void onLoop(void);
	void onResize(int32_t width, int32_t height);

	void onGLInitialize(void);
	void onGLRelease(void);
	
	void updateRenderer();
	void drawUI();
		
	template <typename T>
	void updateRenderer(const T *items, size_t length, uint8_t tileIndex)
	{
		const T* item = items;
		const T* end = items + length;

		for (; item != end; item++) {
			gridRenderer.set(item->position.x, item->position.y, tileIndex);
		}
	}

	TileRenderer gridRenderer;

	hope::input::keyboard::Mapping defaultMapping;
	hope::input::keyboard::Mapping constructMapping;


	
};

#endif /* HOPE_SAMGLES_TOY_APPLICATION_H */