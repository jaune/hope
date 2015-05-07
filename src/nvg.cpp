#include "nvg.h"

#include "console.h"
#include "core/core.h"
#include "asset/asset.h"

#define NANOVG_GLES2_IMPLEMENTATION
#include <nanovg_gl.h>
#include <nanovg_gl_utils.h>

#include <cstdarg>

namespace hope {
namespace nanovg {

	class Module {
	public:
		NVGcontext* vg = NULL;
		NVGLUframebuffer* fb = NULL;

		float textOffset = 8;
		char textBuffer[256];

	public:
		static Module* getInstance() {
			static Module* instance = NULL;

			if (instance == NULL) {
				instance = new Module();
			}

			return instance;
		}

	public:
		bool initialize() {
			vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
			if (vg == NULL) {
				::hope::console::log("nvgCreateGLES2\n");
				return false;
			}

			int32_t winWidth = 1024, winHeight = 768;
			hope::core::getViewportSize(&winWidth, &winHeight);

			fb = nvgluCreateFramebuffer(vg, winWidth, winHeight, 0);
			if (fb == NULL) {
				nvgDeleteGLES2(vg);
				::hope::console::log("nvgluCreateFramebuffer\n");
				return false;
			}

			return true;
		}

		void release() {
			nvgluDeleteFramebuffer(vg, fb);
			nvgDeleteGLES2(vg);
		}

		void beginFramebuffer() {
			int32_t winWidth = 1024, winHeight = 768;
			hope::core::getViewportSize(&winWidth, &winHeight);

			nvgluBindFramebuffer(fb);
			glViewport(0, 0, winWidth, winHeight);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			nvgBeginFrame(vg, winWidth, winHeight, 1);

			nvgBeginPath(vg);
			nvgRect(vg, 0, 0, 500, 500);
			nvgFillColor(vg, nvgRGBA(255, 0, 255, 255));
			nvgFill(vg);

			nvgText(0, 0, "ADRIEN !!!!");
		}

		void endFramebuffer() {
			nvgEndFrame(vg);
			nvgluBindFramebuffer(NULL);
		}

		void renderFramebuffer() {
			hope::console::log("=>>>>>>>>>>>>> %d", fb->texture);

			NVGpaint img = nvgImagePattern(vg, 0, 0, 500, 500, 0, fb->image, 1.0f);

			nvgSave(vg);

			nvgBeginPath(vg);
			nvgRect(vg, 0, 0, 500, 500);
			nvgFillPaint(vg, img);
			nvgFill(vg);

			nvgRestore(vg);
		}

		void drawStrokeCircle(const b2Vec2& center, float radius, const b2Color& color) {
			int32_t winWidth, winHeight;

			hope::core::getViewportSize(&winWidth, &winHeight);

			nvgSave(vg);

			nvgBeginPath(vg);
			nvgCircle(vg, (winWidth / 2.0) + (center.x * 10.0f), (winHeight / 2.0) + (center.y * -10.0f), radius * 10.0f);
			nvgStrokeColor(vg, nvgRGBA(
				(uint8_t)(color.r * 255.0f),
				(uint8_t)(color.g * 255.0f),
				(uint8_t)(color.b * 255.0f),
				255));
			nvgStroke(vg);
			nvgRestore(vg);
		}

		void drawFillCircle(const b2Vec2& center, float radius, const b2Color& color) {
			int32_t winWidth, winHeight;

			hope::core::getViewportSize(&winWidth, &winHeight);

			nvgSave(vg);

			nvgBeginPath(vg);
			nvgCircle(vg, (winWidth / 2.0) + (center.x * 10.0f), (winHeight / 2.0) + (center.y * -10.0f), radius * 10.0f);
			nvgFillColor(vg, nvgRGBA(
				(uint8_t)(color.r * 255.0f),
				(uint8_t)(color.g * 255.0f),
				(uint8_t)(color.b * 255.0f),
				255));
			nvgFill(vg);
			nvgRestore(vg);
		}



		void drawStrokeLine(const b2Vec2& src, const b2Vec2& dst, const b2Color& color) {
			int32_t winWidth, winHeight, i;

			hope::core::getViewportSize(&winWidth, &winHeight);

			float_t xOffset = (winWidth / 2.0f), yOffset = (winHeight / 2.0f);

			nvgSave(vg);

			nvgBeginPath(vg);
			nvgMoveTo(vg,
				(src.x * 10.0f) + xOffset,
				(src.y * -10.0f) + yOffset
				);
			nvgLineTo(vg,
				(dst.x * 10.0f) + xOffset,
				(dst.y * -10.0f) + yOffset
				);
			nvgStrokeColor(vg, nvgRGBA(
				(uint8_t)(color.r * 255.0f),
				(uint8_t)(color.g * 255.0f),
				(uint8_t)(color.b * 255.0f),
				255));
			nvgStroke(vg);

			nvgRestore(vg);
		}
	
		void drawAABB(const b2AABB& aabb){
			int32_t winWidth, winHeight;

			hope::core::getViewportSize(&winWidth, &winHeight);

			float_t xOffset = (winWidth / 2.0f),
				yOffset = (winHeight / 2.0f);
			nvgSave(vg);

			float_t x = xOffset + (aabb.lowerBound.x * 10.0f),
				y = yOffset + (aabb.upperBound.y * -10.0f),
				w = (aabb.upperBound.x - aabb.lowerBound.x) * 10.0f,
				h = (aabb.upperBound.y - aabb.lowerBound.y) * 10.0f;

			nvgBeginPath(vg);
			nvgRect(vg, x, y, w, h);
			nvgStrokeColor(vg, nvgRGBA(255, 0, 255, 255));
			nvgStroke(vg);

			nvgRestore(vg);
		}

		void beginStackTextRight() {

			int32_t winWidth, winHeight;

			hope::core::getViewportSize(&winWidth, &winHeight);

			textOffset = 8;
			xTextOffset = winWidth - 8;
			nvgFontSize(vg, 22.0f);
			nvgFontFace(vg, "sans");
			nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
			nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
		}

		void beginStackTextLeft() {
			textOffset = 8;
			xTextOffset = 8;
			nvgFontSize(vg, 22.0f);
			nvgFontFace(vg, "sans");
			nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
			nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
		}

		float xTextOffset;

		void drawStackText(const char* format, va_list args) {
			vsprintf(textBuffer, format, args);
			nvgText(vg, xTextOffset, textOffset, textBuffer, NULL);
			textOffset += 20.0f;
		}

		void drawText(float x, float y, const char* format, va_list args) {
			vsprintf(textBuffer, format, args);
			nvgText(vg, x, y, textBuffer, NULL);
			textOffset += 20.0f;
		}

		void beginFrame() {
			int32_t winWidth = 1024, winHeight = 768;
			hope::core::getViewportSize(&winWidth, &winHeight);
			nvgBeginFrame(vg, winWidth, winHeight, 1);
		}

		void endFrame() {
			nvgEndFrame(vg);
		}

		void drawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

			int32_t winWidth, winHeight, i;

			hope::core::getViewportSize(&winWidth, &winHeight);

			float_t xOffset = (winWidth / 2.0f), yOffset = (winHeight / 2.0f);

			nvgSave(vg);

			nvgBeginPath(vg);

			for (i = 0; i < vertexCount; i++) {
				if (i == 0) {
					nvgMoveTo(vg,
						(vertices[i].x * 10.0f) + xOffset,
						(vertices[i].y * -10.0f) + yOffset
						);
				}
				else {
					nvgLineTo(vg,
						(vertices[i].x * 10.0f) + xOffset,
						(vertices[i].y * -10.0f) + yOffset
						);
				}

			}

			nvgClosePath(vg);

			nvgStrokeColor(vg, nvgRGBA(
				(uint8_t)(color.r * 255.0f),
				(uint8_t)(color.g * 255.0f),
				(uint8_t)(color.b * 255.0f),
				255));
			nvgStroke(vg);

			nvgRestore(vg);
		}

		void loadFont(const char* asset_identifier, const char* font_name) {
			::hope::asset::Asset asset = ::hope::asset::get(asset_identifier);
			int fontIcons = nvgCreateFontMem(vg, font_name, (unsigned char*)asset.pointer, asset.size, 0);
			if (fontIcons == -1) {
				::hope::console::log("Could not add font icons.\n");
			}
		}

	}; /* class Module */

	bool initialize() {
		return hope::nanovg::Module::getInstance()->initialize();
	}

	NVGcontext* getContext() {
		return hope::nanovg::Module::getInstance()->vg;
	}

	void release() {
		hope::nanovg::Module* module = hope::nanovg::Module::getInstance();

		module->release();
	}

	void beginFrame() {
		hope::nanovg::Module::getInstance()->beginFrame();
	}

	void endFrame() {
		hope::nanovg::Module::getInstance()->endFrame();
	}



	void beginFramebuffer() {
		hope::nanovg::Module::getInstance()->beginFramebuffer();
	}

	void endFramebuffer() {
		hope::nanovg::Module::getInstance()->endFramebuffer();
	}

	void renderFramebuffer() {
		hope::nanovg::Module::getInstance()->renderFramebuffer();
	}

	void loadFont(const char* asset_identifier, const char* font_name) {
		hope::nanovg::Module::getInstance()->loadFont(asset_identifier, font_name);
	}

} /* namespace nanovg */
} /* namespace hope */




void nvgDrawStrokeCircle(const b2Vec2& center, float radius, const b2Color& color) {
	hope::nanovg::Module::getInstance()->drawStrokeCircle(center, radius, color);
}

void nvgDrawFillCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
	hope::nanovg::Module::getInstance()->drawFillCircle(center, radius, color);
}

void nvgBeginStackTextRight() {
	hope::nanovg::Module::getInstance()->beginStackTextRight();
}

void nvgBeginStackTextLeft() {
	hope::nanovg::Module::getInstance()->beginStackTextLeft();
}


void nvgStackText(const char* format, ...) {
	va_list args;
	va_start(args, format);

	hope::nanovg::Module::getInstance()->drawStackText(format, args);

	va_end(args);
}

void nvgText(float x, float y, const char* format, ...) {
	va_list args;
	va_start(args, format);

	hope::nanovg::Module::getInstance()->drawText(x, y, format, args);

	va_end(args);
}


void nvgDrawStrokeLine(const b2Vec2& src, const b2Vec2& dst, const b2Color& color) {
	hope::nanovg::Module::getInstance()->drawStrokeLine(src, dst, color);
}

void nvgDrawAABB(const b2AABB& aabb){
	hope::nanovg::Module::getInstance()->drawAABB(aabb);
}

void nvgDrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
	hope::nanovg::Module::getInstance()->drawSolidPolygon(vertices, vertexCount, color);
}

