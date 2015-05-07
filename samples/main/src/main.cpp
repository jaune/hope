#include "entry/entry.h"

#include <GLES2/gl2.h>



void SDL_Log(...) {}

static const char *vertex_shader_src =
"precision mediump float;\n"
"\n"
"attribute vec2 vtxcoord;\n"
"uniform mat4 projection;\n"
"\n"
"void main(void)\n"
"{\n"
"    gl_Position = projection * vec4(vtxcoord, 0.0, 1.0);\n"
"}\n"
;

static const char *fragment_shader_src =
"precision mediump float;\n"
"\n"
"uniform vec4 color;\n"
"\n"
"void main(void)\n"
"{\n"
"    gl_FragColor = color;\n"
"}\n"
;

static GLuint
build_shader(GLenum type, const char *source)
{
    GLuint id = glCreateShader(type);

    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    GLint result = GL_FALSE;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        char tmp[2048];
        glGetShaderInfoLog(id, sizeof(tmp), NULL, tmp);
        SDL_Log("%s shader compile error:\n====\n%s\n====\n",
                (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment", tmp);
    }

    return id;
}

static GLuint
build_program()
{
    GLuint id = glCreateProgram();

    GLuint vertex_shader_id = build_shader(GL_VERTEX_SHADER, vertex_shader_src);
    GLuint fragment_shader_id = build_shader(GL_FRAGMENT_SHADER, fragment_shader_src);

    glAttachShader(id, vertex_shader_id);
    glAttachShader(id, fragment_shader_id);

    glLinkProgram(id);
    GLint result = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
        char tmp[2048];
        glGetProgramInfoLog(id, sizeof(tmp), NULL, tmp);
        SDL_Log("Program link error:\n====\n%s\n====\n", tmp);
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return id;
}

namespace hope {

namespace entry {

    GLuint program;

    void onInitialize (void) {

    }
    void onRelease (void) {

    }

    void onLoop (void) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        int color_loc = glGetUniformLocation(program, "color");
        glUniform4f(color_loc, 0.1, 0.3, 0.7, 1.0);

        int vtxcoord_loc = glGetAttribLocation(program, "vtxcoord");
        glEnableVertexAttribArray(vtxcoord_loc);

        float d = 30, x = 30, y = 30;

        float vertices[] = {
            x - d, y - d,
            x + d, y - d,
            x - d, y + d,
            x + d, y + d,
        };

        glVertexAttribPointer(vtxcoord_loc, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDisableVertexAttribArray(vtxcoord_loc);

        glUseProgram(0);
    }

    void onResize(int width, int height) {
        glUseProgram(program);

        // Orthographic projection
        // https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
        float left = 0, right = width, bottom = height, top = 0;
        float nearVal = -1, farVal = +1;

        float tx = - (right + left) / (right - left);
        float ty = - (top + bottom) / (top - bottom);
        float tz = - (farVal + nearVal) / (farVal - nearVal);

        // Transposed
        float projection[] = {
            2.0 / (right - left), 0.0, 0.0, 0.0,
            0.0, 2.0 / (top - bottom), 0.0, 0.0,
            0.0, 0.0, -2.0 / (farVal - nearVal), 0.0,
            tx, ty, tz, 1.0,
        };

        int projection_loc = glGetUniformLocation(program, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection);

        glUseProgram(0);

		glViewport(0, 0, width, height);
    }

    void onGLInitialize() {
        glClearColor(0, 0, 0, 1);

        program = build_program();
    }

    void onGLRelease(void) {
    }

} /* namespace entry */

} /* namespace hope */
