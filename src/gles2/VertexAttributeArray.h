#ifndef HOPE_GLES2_VERTEXATTRIBUTEARRAY_H
#define HOPE_GLES2_VERTEXATTRIBUTEARRAY_H

#include <vector>
#include <GLES2/gl2.h>

namespace hope {
namespace gles2 {


class VertexAttributeArray {

	struct Item {
		const GLchar * name;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLint location;
		GLsizei offset;
	};

	std::vector<Item> items;
	GLsizei stride;
	GLuint buffer;

public:
	VertexAttributeArray() : buffer(0), stride(0) {
	}

	void defineAttribute(const GLchar *name, GLint size, GLenum type, GLboolean normalized = GL_FALSE) {
		Item item;

		item.size = size;
		item.type = type;
		item.normalized = normalized;
		item.name = name;
		item.location = 0;
		item.offset = 0;

		switch (type)
		{
		case GL_FLOAT: {
			item.offset = size * sizeof(GLfloat);
			break;
		}
		case GL_BYTE: {
			item.offset = size * sizeof(GLbyte);
			break;
		}
		case GL_UNSIGNED_BYTE: {
			item.offset = size * sizeof(GLubyte);
			break;
		}
		case GL_INT: {
			item.offset = size * sizeof(GLint);
			break;
		}
		case GL_UNSIGNED_INT: {
			item.offset = size * sizeof(GLuint);
			break;
		}
		default:
			break;
		}

		stride += item.offset;

		items.push_back(item);
	}

	void unbind() {
		for (auto it = items.begin(); it != items.end(); ++it) {
			glDisableVertexAttribArray(it->location);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void bind() {
		for (auto it = items.begin(); it != items.end(); ++it) {
			glEnableVertexAttribArray(it->location);
		}

		glBindBuffer(GL_ARRAY_BUFFER, buffer);

		GLsizei offset = 0;

		for (auto it = items.begin(); it != items.end(); ++it) {

			glVertexAttribPointer(
				it->location, it->size, it->type,
				it->normalized,
				stride,
				(GLvoid*)(offset));

			offset += it->offset;
		}
	}

	void upload(const void* data, GLsizeiptr size) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void create(GLuint program) {
		if (buffer != 0) {
			return;
		}
		glGenBuffers(1, &buffer);

		for (auto it = items.begin(); it != items.end(); ++it) {
			it->location = glGetAttribLocation(program, it->name);
		}
	}

	void destroy() {
		glDeleteBuffers(1, &buffer);
	}
};


} /* namespace gles2 */
} /* namespace hope */



#endif /* HOPE_GLES2_VERTEXATTRIBUTEARRAY_H */