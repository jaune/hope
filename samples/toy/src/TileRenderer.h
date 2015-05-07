#ifndef HOPE_SAMGLES_TILE_TileRENDERER_H
#define HOPE_SAMGLES_TILE_TileRENDERER_H

#include <gles2/Pass.h>
#include <webp/decode.h>

class TileRenderer {

	hope::gles2::Pass pass;
	mathfu::mat4 uOrthoMatrix;
	mathfu::mat4 uViewportMatrix;
	mathfu::mat4 uTranslationMatrix;
	
public:
	float zoomValue;
private:
	struct Image {

		uint8_t* data;
		int32_t width;
		int32_t height;

		Image(uint8_t* data, int32_t width, int32_t height) :
			data(data), width(width), height(height) {
		}

		~Image() {
			free(data);
		}
	};

	Image* loadImage(const char* identifier) {
		WebPBitstreamFeatures features;

		hope::asset::Asset image = hope::asset::get(identifier);

		const uint8_t* data = (uint8_t*)image.pointer;
		size_t data_size = image.size;

		VP8StatusCode code = WebPGetFeatures(data, data_size, &features);
		if (code != VP8_STATUS_OK) {
			return NULL;
		}

		uint8_t* ouput = WebPDecodeRGBA(data, data_size, NULL, NULL);

		return new Image(ouput, features.width, features.height);
	}

	GLuint createTexture(const Image& image) {
		GLuint texture;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}

	GLuint createTexture(GLsizei width, GLsizei height, const GLubyte* data) {
		GLuint texture;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}

	void updateViewportMatrix() {
		pass.setUniformMatrix4("uViewportMatrix", uOrthoMatrix * uTranslationMatrix * mathfu::mat4::FromScaleVector(mathfu::vec3(zoomValue, zoomValue, 1.0f)));
	}

	GLubyte* mappingData;
	GLsizei mappingWidth;
	GLsizei mappingHeight;
	GLsizei mappingDataLength;
	GLuint mappingTexture;

	Image* tilesetImage;


public:
	void set(int32_t x, int32_t y, uint8_t tileIndex){
		size_t index = (x + (y * mappingWidth)) * 4;

		if (index < 0 || index >= mappingDataLength) {
			return;
		}
		mappingData[index] = tileIndex;
	}

	void initialize(int32_t gridWidth, int32_t gridHeight, const char* imagePath, const char* vertShaderPath, const char* fragShaderPath) {
		uTranslationMatrix = mathfu::mat4::Identity();

		tilesetImage = loadImage(imagePath);

		GLuint tilesetTexture = createTexture(*tilesetImage);
		::hope::console::log("texture #%i", tilesetTexture);

		mappingWidth = gridWidth;
		mappingHeight = gridHeight;
		mappingDataLength = mappingWidth * mappingHeight * 4;
		mappingData = new GLubyte[mappingDataLength];

		memset(mappingData, 0x00, mappingDataLength);

		mappingTexture = createTexture(mappingWidth, mappingHeight, mappingData);

		::hope::console::log("texture #%i", mappingTexture);


		int32_t tile_size = 32;

		float w = mappingWidth * tile_size;
		float h = mappingHeight * tile_size;

		float data[] = {
			w / 2, h / 2, 1.0, 1.0,
			-w / 2, h / 2, 0.0, 1.0,
			w / 2, -h / 2, 1.0, 0.0,
			-w / 2, -h / 2, 0.0, 0.0
		};

		pass.create(::hope::asset::get(vertShaderPath), ::hope::asset::get(fragShaderPath));


		pass.defineAttribute("aVertexPosition", 2, GL_FLOAT);
		pass.defineAttribute("aTextureCoord", 2, GL_FLOAT);


		pass.uploadAttributes(data, sizeof(data));

		pass.setUniform1f("uTileSize", 32.0f);
		pass.setUniform1f("uTilesetSize", (float)(tilesetImage->width));
		pass.setUniform1f("uTilesetIndexMax", 256.0f);
		pass.bindTexture("uTilesetSampler", tilesetTexture);

		pass.setUniform1f("uAreaSize", w);
		pass.bindTexture("uAreaSampler", mappingTexture);
		
		zoomValue = 0.25;
	}

	void resize(int32_t winWidth, int32_t winHeight){
		uOrthoMatrix = mathfu::mat4::Ortho(-winWidth / 2, winWidth / 2, winHeight / 2, -winHeight / 2, -1.0f, 1.0f);
		updateViewportMatrix();
	}

	void commit(){
		glBindTexture(GL_TEXTURE_2D, mappingTexture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mappingWidth, mappingHeight, GL_RGBA, GL_UNSIGNED_BYTE, mappingData);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void render(){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		pass.drawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	
	void zoom(float delta){
		zoomValue += delta;

		if (zoomValue <= 0.07) {
			zoomValue = 0.07;
		}
		if (zoomValue >= 1.07) {
			zoomValue = 1.07;
		}

		updateViewportMatrix();
	}

	void translate(float x, float y) {
		uTranslationMatrix = mathfu::mat4::FromTranslationVector(mathfu::vec3(x, y, 0.f));
		updateViewportMatrix();
	}
		
	void release() {
		delete tilesetImage;
	}
};


#endif /* HOPE_SAMGLES_TILE_TileRENDERER_H */