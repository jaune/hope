#ifndef HOPE_GLES2_FRAMEBUFFER_H
#define HOPE_GLES2_FRAMEBUFFER_H

#include "./Pass.h"

namespace hope {
	namespace gles2 {

		class Framebuffer {

			int width;
			int height;

			GLuint fbo;
			GLuint rbo;
			GLuint texture;

			mathfu::mat4 uOrthoMatrix;

			hope::gles2::Pass pass;

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



		public:
			Framebuffer() :
				fbo(0),
				rbo(0),
				texture(0) {
			}

			bool initialize(int w, int h) {

				width = w;
				height = h;

				GLint defaultFBO;
				GLint defaultRBO;

				glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
				glGetIntegerv(GL_RENDERBUFFER_BINDING, &defaultRBO);


				texture = createTexture(w, h, NULL);

				// frame buffer object
				glGenFramebuffers(1, &fbo);
				glBindFramebuffer(GL_FRAMEBUFFER, fbo);

				// render buffer object
				glGenRenderbuffers(1, &rbo);
				glBindRenderbuffer(GL_RENDERBUFFER, rbo);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, w, h);

				// combine all
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
					glDeleteFramebuffers(1, &fbo);
					glDeleteRenderbuffers(1, &rbo);
					return false;
				}

				glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
				glBindRenderbuffer(GL_RENDERBUFFER, defaultRBO);

				float data[] = {
					w / 2, h / 2, 1.0, 1.0,
					-w / 2, h / 2, 0.0, 1.0,
					w / 2, -h / 2, 1.0, 0.0,
					-w / 2, -h / 2, 0.0, 0.0
				};

				pass.setProgram("\
precision highp float; \
attribute vec2 aVertexPosition; \
attribute vec2 aTextureCoord; \
\
uniform mat4 uViewportMatrix; \
varying vec2 vTextureCoord; \
\
void main(void) { \
vTextureCoord = aTextureCoord; \
gl_Position = uViewportMatrix * vec4(aVertexPosition, 0.0, 1.0); \
}", "\
precision highp float; \
varying vec2 vTextureCoord; \
uniform sampler2D tTexture; \
\
void main(){ \
gl_FragColor = texture2D(tTexture, vTextureCoord); \
} \
");


				pass.defineAttribute("aVertexPosition", 2, GL_FLOAT);
				pass.defineAttribute("aTextureCoord", 2, GL_FLOAT);


				pass.uploadAttributes(data, sizeof(data));

				pass.bindTexture("tTexture", texture);

				resize(w, h);

				return true;
			}

			void updateViewportMatrix() {
				pass.setUniformMatrix4("uViewportMatrix", uOrthoMatrix);
			}

			void resize(int32_t winWidth, int32_t winHeight){
				uOrthoMatrix = mathfu::mat4::Ortho(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2, -1.0f, 1.0f);
				updateViewportMatrix();
			}

			void release(){
				if (fbo != 0)
					glDeleteFramebuffers(1, &fbo);
				if (rbo != 0)
					glDeleteRenderbuffers(1, &rbo);
			}

			void begin() {
				glBindFramebuffer(GL_FRAMEBUFFER, fbo);
				glViewport(0, 0, width, height);
			}

			void end(){
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			void render() {
				pass.drawArrays(GL_TRIANGLE_STRIP, 0, 4);
			}

		};

	}
}

#endif /* HOPE_GLES2_FRAMEBUFFER_H */