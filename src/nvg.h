#ifndef HOPE_NANOVG_H
#define HOPE_NANOVG_H

#include <GLES2/gl2.h>
#include <Box2D/Box2D.h>
#include <nanovg.h>

namespace hope {
namespace nanovg {

	bool initialize();
	void release();

	void beginFrame();
	void endFrame();

	void beginFramebuffer();
	void endFramebuffer();
	void renderFramebuffer();

	NVGcontext* getContext();

	void loadFont(const char* asset_identifier, const char* font_name);

} /* namespace nanovg */
} /* namespace hope */

void nvgDrawStrokeCircle(const b2Vec2& center, float radius, const b2Color& color);
void nvgDrawFillCircle(const b2Vec2& center, float32 radius, const b2Color& color);
void nvgBeginStackTextRight();
void nvgBeginStackTextLeft();
void nvgStackText(const char* format, ...);
void nvgText(float x, float y, const char* format, ...);
void nvgDrawStrokeLine(const b2Vec2& src, const b2Vec2& dst, const b2Color& color);
void nvgDrawAABB(const b2AABB& aabb);
void nvgDrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

#endif /* HOPE_CORE_H */