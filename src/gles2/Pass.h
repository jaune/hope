#ifndef HOPE_GLES2_PASS_H
#define HOPE_GLES2_PASS_H

#include <console.h>
#include <asset/asset.h>
#include <vector>
#include <unordered_map>

#include <GLES2/gl2.h>
#include <mathfu/glsl_mappings.h>

#include "./VertexAttributeArray.h"

namespace hope {
namespace gles2 {

class Pass {

	GLuint createShaderFromSource(GLenum type, GLint lineCount, const GLchar* const * lines, const GLint* lineLengths) {
		GLuint shader = glCreateShader(type);

		if (shader == 0) {
			return 0;
		}

		glShaderSource(shader, lineCount, lines, lineLengths);

		glCompileShader(shader);

		GLint status = GL_TRUE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint maxLength = 0;
			GLint length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			GLchar* errorLog = new GLchar[maxLength];
			glGetShaderInfoLog(shader, maxLength, &length, errorLog);

			::hope::console::log("shader compile: %s", errorLog);

			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}



	GLuint createProgramFromShader(GLuint vertexShader, GLuint fragmentShader) {
		GLuint program = glCreateProgram();

		if (program == 0) {
			return 0;
		}


		if (fragmentShader == 0) {
			glDeleteProgram(program);
			return 0;
		}

		if (vertexShader == 0 || fragmentShader == 0) {
			glDeleteProgram(program);
			return 0;
		}

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		GLint status = GL_TRUE;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{

			GLint maxLength = 0;
			GLint length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			GLchar* errorLog = new GLchar[maxLength];
			glGetProgramInfoLog(program, maxLength, &length, errorLog);

			::hope::console::log("program link: %s", errorLog);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			glDeleteProgram(program);
			return 0;
		}

		return program;
	}


	GLuint createProgramFromAsset(const ::hope::asset::Asset& vertexShaderSource, const ::hope::asset::Asset& fragmentShaderSource) {
		if (vertexShaderSource.is_null() || fragmentShaderSource.is_null()) {
			return 0;
		}

		GLuint vertexShader = createShaderFromSource(GL_VERTEX_SHADER, 1, (const GLchar* const *)&vertexShaderSource.pointer, (const GLint*)&vertexShaderSource.size);
		GLuint fragmentShader = createShaderFromSource(GL_FRAGMENT_SHADER, 1, (const GLchar* const *)&fragmentShaderSource.pointer, (const GLint*)&fragmentShaderSource.size);

		if (vertexShader == 0 || fragmentShader == 0) {
			return 0;
		}

		return createProgramFromShader(vertexShader, fragmentShader);
	}

	GLuint createProgramFromSource(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource) {
		GLuint vertexShader = createShaderFromSource(GL_VERTEX_SHADER, 1, &vertexShaderSource, NULL);
		GLuint fragmentShader = createShaderFromSource(GL_FRAGMENT_SHADER, 1, &fragmentShaderSource, NULL);
		return createProgramFromShader(vertexShader, fragmentShader);
	}

	struct Texture {
		const char* name;
		GLint location;
		GLuint texture;
		GLuint unit;
	};

	struct Uniform1f {
		const char* name;
		GLint location;
		GLfloat value;
	};

	struct UniformMatrix4 {
		const char* name;
		GLint location;
		mathfu::mat4 value;
		GLboolean transpose;
	};
	
	typedef std::unordered_map<const char*, Uniform1f> Uniform1fMap;
	typedef std::unordered_map<const char*, UniformMatrix4> UniformMatrix4Map;

	GLuint program;
	std::vector<Texture> textures;
	VertexAttributeArray attributes;
	
	Uniform1fMap uniform1fMap;
	UniformMatrix4Map uniformMatrix4Map;

public:
	Pass()
		: program(0) {
	}

	void setProgram(const GLchar* vsource, const GLchar* fsource) {
		program = createProgramFromSource(vsource, fsource);
	}

	void create(const ::hope::asset::Asset& vertexShaderSource, const ::hope::asset::Asset& fragmentShaderSource) {
		program = createProgramFromAsset(vertexShaderSource, fragmentShaderSource);
	}

	void destroy() {
		glDeleteProgram(program);
	}

	void defineAttribute(const GLchar *name, GLint size, GLenum type, GLboolean normalized = GL_FALSE) {
		attributes.defineAttribute(name, size, type, normalized);
	}

	void uploadAttributes(const void* data, GLsizeiptr size) {
		attributes.create(program);
		attributes.upload(data, size);
	}	

	void setUniformMatrix4(const char* name, const mathfu::mat4& value, GLboolean transpose = GL_FALSE) {
		auto it = uniformMatrix4Map.find(name);
		if (it == uniformMatrix4Map.end()) {
			GLint location = glGetUniformLocation(program, name);
			if (location != -1) {
				UniformMatrix4 uniform;

				uniform.name = name;
				uniform.value = value;
				uniform.transpose = transpose;
				uniform.location = location;

				uniformMatrix4Map.insert(UniformMatrix4Map::value_type(name, uniform));
			}
		}
		else {
			it->second.value = value;
		}
	}

	void setUniform1f(const char* name, GLfloat value) {
		auto it = uniform1fMap.find(name);
		if (it == uniform1fMap.end()) {
			GLint location = glGetUniformLocation(program, name);
			if (location != -1) {
				Uniform1f uniform;

				uniform.name = name;
				uniform.value = value;
				uniform.location = location;

				uniform1fMap.insert(Uniform1fMap::value_type(name, uniform));
			}
		}
		else {
			it->second.value = value;
		}
	}

	void bindTexture(const char* name, GLuint texture) {
		GLint location = glGetUniformLocation(program, name);
		if (location == -1) {
			return;
		}

		Texture tex;

		tex.name = name;
		tex.location = glGetUniformLocation(program, name);
		tex.texture = texture;
		tex.unit = textures.size();

		textures.push_back(tex);
	}

	void drawArrays(GLenum mode, GLint first, GLsizei count) {
		glUseProgram(program);

		for (auto it = textures.begin(); it != textures.end(); ++it) {
			glUniform1i(it->location, it->unit);
			glActiveTexture(it->unit + GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, it->texture);
		}

		for (auto it = uniform1fMap.begin(); it != uniform1fMap.end(); ++it) {
			glUniform1f(it->second.location, it->second.value);
		}

		for (auto it = uniformMatrix4Map.begin(); it != uniformMatrix4Map.end(); ++it) {
			GLfloat* mat4 = &(it->second.value[0]);

			GLfloat v = it->second.value[0];

			glUniformMatrix4fv(it->second.location, 1, it->second.transpose, mat4);
		}

		attributes.bind();
		glDrawArrays(mode, first, count);
		attributes.unbind();
	}

};

} /* namespace gles2 */
} /* namespace hope */

#endif /* HOPE_GLES2_PASS_H */