#include "opengles2_wrapper.h"


#if defined(_MSC_VER) && _MSC_VER >= 1400
#pragma warning(disable:4273)   // suppress even more warnings about dllexport
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef void (GL_APIENTRYP __type_glActiveTexture)(GLenum texture);
typedef void (GL_APIENTRYP __type_glAttachShader)(GLuint program, GLuint shader);
typedef void (GL_APIENTRYP __type_glBindAttribLocation)(GLuint program, GLuint index, const GLchar* name);
typedef void (GL_APIENTRYP __type_glBindBuffer)(GLenum target, GLuint buffer);
typedef void (GL_APIENTRYP __type_glBindFramebuffer)(GLenum target, GLuint framebuffer);
typedef void (GL_APIENTRYP __type_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
typedef void (GL_APIENTRYP __type_glBindTexture)(GLenum target, GLuint texture);
typedef void (GL_APIENTRYP __type_glBlendColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void (GL_APIENTRYP __type_glBlendEquation)(GLenum mode);
typedef void (GL_APIENTRYP __type_glBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);
typedef void (GL_APIENTRYP __type_glBlendFunc)(GLenum sfactor, GLenum dfactor);
typedef void (GL_APIENTRYP __type_glBlendFuncSeparate)(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (GL_APIENTRYP __type_glBufferData)(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
typedef void (GL_APIENTRYP __type_glBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
typedef GLenum (GL_APIENTRYP __type_glCheckFramebufferStatus)(GLenum target);
typedef void (GL_APIENTRYP __type_glClear)(GLbitfield mask);
typedef void (GL_APIENTRYP __type_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void (GL_APIENTRYP __type_glClearDepthf)(GLclampf depth);
typedef void (GL_APIENTRYP __type_glClearStencil)(GLint s);
typedef void (GL_APIENTRYP __type_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (GL_APIENTRYP __type_glCompileShader)(GLuint shader);
typedef void (GL_APIENTRYP __type_glCompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
typedef void (GL_APIENTRYP __type_glCompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
typedef void (GL_APIENTRYP __type_glCopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (GL_APIENTRYP __type_glCopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef GLuint (GL_APIENTRYP __type_glCreateProgram)(void);
typedef GLuint (GL_APIENTRYP __type_glCreateShader)(GLenum type);
typedef void (GL_APIENTRYP __type_glCullFace)(GLenum mode);
typedef void (GL_APIENTRYP __type_glDeleteBuffers)(GLsizei n, const GLuint* buffers);
typedef void (GL_APIENTRYP __type_glDeleteFramebuffers)(GLsizei n, const GLuint* framebuffers);
typedef void (GL_APIENTRYP __type_glDeleteProgram)(GLuint program);
typedef void (GL_APIENTRYP __type_glDeleteRenderbuffers)(GLsizei n, const GLuint* renderbuffers);
typedef void (GL_APIENTRYP __type_glDeleteShader)(GLuint shader);
typedef void (GL_APIENTRYP __type_glDeleteTextures)(GLsizei n, const GLuint* textures);
typedef void (GL_APIENTRYP __type_glDepthFunc)(GLenum func);
typedef void (GL_APIENTRYP __type_glDepthMask)(GLboolean flag);
typedef void (GL_APIENTRYP __type_glDepthRangef)(GLclampf zNear, GLclampf zFar);
typedef void (GL_APIENTRYP __type_glDetachShader)(GLuint program, GLuint shader);
typedef void (GL_APIENTRYP __type_glDisable)(GLenum cap);
typedef void (GL_APIENTRYP __type_glDisableVertexAttribArray)(GLuint index);
typedef void (GL_APIENTRYP __type_glDrawArrays)(GLenum mode, GLint first, GLsizei count);
typedef void (GL_APIENTRYP __type_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
typedef void (GL_APIENTRYP __type_glEnable)(GLenum cap);
typedef void (GL_APIENTRYP __type_glEnableVertexAttribArray)(GLuint index);
typedef void (GL_APIENTRYP __type_glFinish)(void);
typedef void (GL_APIENTRYP __type_glFlush)(void);
typedef void (GL_APIENTRYP __type_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (GL_APIENTRYP __type_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GL_APIENTRYP __type_glFrontFace)(GLenum mode);
typedef void (GL_APIENTRYP __type_glGenBuffers)(GLsizei n, GLuint* buffers);
typedef void (GL_APIENTRYP __type_glGenerateMipmap)(GLenum target);
typedef void (GL_APIENTRYP __type_glGenFramebuffers)(GLsizei n, GLuint* framebuffers);
typedef void (GL_APIENTRYP __type_glGenRenderbuffers)(GLsizei n, GLuint* renderbuffers);
typedef void (GL_APIENTRYP __type_glGenTextures)(GLsizei n, GLuint* textures);
typedef void (GL_APIENTRYP __type_glGetActiveAttrib)(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
typedef void (GL_APIENTRYP __type_glGetActiveUniform)(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
typedef void (GL_APIENTRYP __type_glGetAttachedShaders)(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
typedef int (GL_APIENTRYP __type_glGetAttribLocation)(GLuint program, const GLchar* name);
typedef void (GL_APIENTRYP __type_glGetBooleanv)(GLenum pname, GLboolean* params);
typedef void (GL_APIENTRYP __type_glGetBufferParameteriv)(GLenum target, GLenum pname, GLint* params);
typedef GLenum (GL_APIENTRYP __type_glGetError)(void);
typedef void (GL_APIENTRYP __type_glGetFloatv)(GLenum pname, GLfloat* params);
typedef void (GL_APIENTRYP __type_glGetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint* params);
typedef void (GL_APIENTRYP __type_glGetIntegerv)(GLenum pname, GLint* params);
typedef void (GL_APIENTRYP __type_glGetProgramiv)(GLuint program, GLenum pname, GLint* params);
typedef void (GL_APIENTRYP __type_glGetProgramInfoLog)(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
typedef void (GL_APIENTRYP __type_glGetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint* params);
typedef void (GL_APIENTRYP __type_glGetShaderiv)(GLuint shader, GLenum pname, GLint* params);
typedef void (GL_APIENTRYP __type_glGetShaderInfoLog)(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
typedef void (GL_APIENTRYP __type_glGetShaderPrecisionFormat)(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
typedef void (GL_APIENTRYP __type_glGetShaderSource)(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);
typedef const GLubyte* (GL_APIENTRYP __type_glGetString)(GLenum name);
typedef void (GL_APIENTRYP __type_glGetTexParameterfv)(GLenum target, GLenum pname, GLfloat* params);
typedef void (GL_APIENTRYP __type_glGetTexParameteriv)(GLenum target, GLenum pname, GLint* params);
typedef void (GL_APIENTRYP __type_glGetUniformfv)(GLuint program, GLint location, GLfloat* params);
typedef void (GL_APIENTRYP __type_glGetUniformiv)(GLuint program, GLint location, GLint* params);
typedef int (GL_APIENTRYP __type_glGetUniformLocation)(GLuint program, const GLchar* name);
typedef void (GL_APIENTRYP __type_glGetVertexAttribfv)(GLuint index, GLenum pname, GLfloat* params);
typedef void (GL_APIENTRYP __type_glGetVertexAttribiv)(GLuint index, GLenum pname, GLint* params);
typedef void (GL_APIENTRYP __type_glGetVertexAttribPointerv)(GLuint index, GLenum pname, GLvoid** pointer);
typedef void (GL_APIENTRYP __type_glHint)(GLenum target, GLenum mode);
typedef GLboolean (GL_APIENTRYP __type_glIsBuffer)(GLuint buffer);
typedef GLboolean (GL_APIENTRYP __type_glIsEnabled)(GLenum cap);
typedef GLboolean (GL_APIENTRYP __type_glIsFramebuffer)(GLuint framebuffer);
typedef GLboolean (GL_APIENTRYP __type_glIsProgram)(GLuint program);
typedef GLboolean (GL_APIENTRYP __type_glIsRenderbuffer)(GLuint renderbuffer);
typedef GLboolean (GL_APIENTRYP __type_glIsShader)(GLuint shader);
typedef GLboolean (GL_APIENTRYP __type_glIsTexture)(GLuint texture);
typedef void (GL_APIENTRYP __type_glLineWidth)(GLfloat width);
typedef void (GL_APIENTRYP __type_glLinkProgram)(GLuint program);
typedef void (GL_APIENTRYP __type_glPixelStorei)(GLenum pname, GLint param);
typedef void (GL_APIENTRYP __type_glPolygonOffset)(GLfloat factor, GLfloat units);
typedef void (GL_APIENTRYP __type_glReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);
typedef void (GL_APIENTRYP __type_glReleaseShaderCompiler)(void);
typedef void (GL_APIENTRYP __type_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GL_APIENTRYP __type_glSampleCoverage)(GLclampf value, GLboolean invert);
typedef void (GL_APIENTRYP __type_glScissor)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GL_APIENTRYP __type_glShaderBinary)(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length);
typedef void (GL_APIENTRYP __type_glShaderSource)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
typedef void (GL_APIENTRYP __type_glStencilFunc)(GLenum func, GLint ref, GLuint mask);
typedef void (GL_APIENTRYP __type_glStencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (GL_APIENTRYP __type_glStencilMask)(GLuint mask);
typedef void (GL_APIENTRYP __type_glStencilMaskSeparate)(GLenum face, GLuint mask);
typedef void (GL_APIENTRYP __type_glStencilOp)(GLenum fail, GLenum zfail, GLenum zpass);
typedef void (GL_APIENTRYP __type_glStencilOpSeparate)(GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
typedef void (GL_APIENTRYP __type_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
typedef void (GL_APIENTRYP __type_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
typedef void (GL_APIENTRYP __type_glTexParameterfv)(GLenum target, GLenum pname, const GLfloat* params);
typedef void (GL_APIENTRYP __type_glTexParameteri)(GLenum target, GLenum pname, GLint param);
typedef void (GL_APIENTRYP __type_glTexParameteriv)(GLenum target, GLenum pname, const GLint* params);
typedef void (GL_APIENTRYP __type_glTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
typedef void (GL_APIENTRYP __type_glUniform1f)(GLint location, GLfloat x);
typedef void (GL_APIENTRYP __type_glUniform1fv)(GLint location, GLsizei count, const GLfloat* v);
typedef void (GL_APIENTRYP __type_glUniform1i)(GLint location, GLint x);
typedef void (GL_APIENTRYP __type_glUniform1iv)(GLint location, GLsizei count, const GLint* v);
typedef void (GL_APIENTRYP __type_glUniform2f)(GLint location, GLfloat x, GLfloat y);
typedef void (GL_APIENTRYP __type_glUniform2fv)(GLint location, GLsizei count, const GLfloat* v);
typedef void (GL_APIENTRYP __type_glUniform2i)(GLint location, GLint x, GLint y);
typedef void (GL_APIENTRYP __type_glUniform2iv)(GLint location, GLsizei count, const GLint* v);
typedef void (GL_APIENTRYP __type_glUniform3f)(GLint location, GLfloat x, GLfloat y, GLfloat z);
typedef void (GL_APIENTRYP __type_glUniform3fv)(GLint location, GLsizei count, const GLfloat* v);
typedef void (GL_APIENTRYP __type_glUniform3i)(GLint location, GLint x, GLint y, GLint z);
typedef void (GL_APIENTRYP __type_glUniform3iv)(GLint location, GLsizei count, const GLint* v);
typedef void (GL_APIENTRYP __type_glUniform4f)(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GL_APIENTRYP __type_glUniform4fv)(GLint location, GLsizei count, const GLfloat* v);
typedef void (GL_APIENTRYP __type_glUniform4i)(GLint location, GLint x, GLint y, GLint z, GLint w);
typedef void (GL_APIENTRYP __type_glUniform4iv)(GLint location, GLsizei count, const GLint* v);
typedef void (GL_APIENTRYP __type_glUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GL_APIENTRYP __type_glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GL_APIENTRYP __type_glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (GL_APIENTRYP __type_glUseProgram)(GLuint program);
typedef void (GL_APIENTRYP __type_glValidateProgram)(GLuint program);
typedef void (GL_APIENTRYP __type_glVertexAttrib1f)(GLuint indx, GLfloat x);
typedef void (GL_APIENTRYP __type_glVertexAttrib1fv)(GLuint indx, const GLfloat* values);
typedef void (GL_APIENTRYP __type_glVertexAttrib2f)(GLuint indx, GLfloat x, GLfloat y);
typedef void (GL_APIENTRYP __type_glVertexAttrib2fv)(GLuint indx, const GLfloat* values);
typedef void (GL_APIENTRYP __type_glVertexAttrib3f)(GLuint indx, GLfloat x, GLfloat y, GLfloat z);
typedef void (GL_APIENTRYP __type_glVertexAttrib3fv)(GLuint indx, const GLfloat* values);
typedef void (GL_APIENTRYP __type_glVertexAttrib4f)(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GL_APIENTRYP __type_glVertexAttrib4fv)(GLuint indx, const GLfloat* values);
typedef void (GL_APIENTRYP __type_glVertexAttribPointer)(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
typedef void (GL_APIENTRYP __type_glViewport)(GLint x, GLint y, GLsizei width, GLsizei height);








__type_glActiveTexture __function_glActiveTexture = NULL;
__type_glAttachShader __function_glAttachShader = NULL;
__type_glBindAttribLocation __function_glBindAttribLocation = NULL;
__type_glBindBuffer __function_glBindBuffer = NULL;
__type_glBindFramebuffer __function_glBindFramebuffer = NULL;
__type_glBindRenderbuffer __function_glBindRenderbuffer = NULL;
__type_glBindTexture __function_glBindTexture = NULL;
__type_glBlendColor __function_glBlendColor = NULL;
__type_glBlendEquation __function_glBlendEquation = NULL;
__type_glBlendEquationSeparate __function_glBlendEquationSeparate = NULL;
__type_glBlendFunc __function_glBlendFunc = NULL;
__type_glBlendFuncSeparate __function_glBlendFuncSeparate = NULL;
__type_glBufferData __function_glBufferData = NULL;
__type_glBufferSubData __function_glBufferSubData = NULL;
__type_glCheckFramebufferStatus __function_glCheckFramebufferStatus = NULL;
__type_glClear __function_glClear = NULL;
__type_glClearColor __function_glClearColor = NULL;
__type_glClearDepthf __function_glClearDepthf = NULL;
__type_glClearStencil __function_glClearStencil = NULL;
__type_glColorMask __function_glColorMask = NULL;
__type_glCompileShader __function_glCompileShader = NULL;
__type_glCompressedTexImage2D __function_glCompressedTexImage2D = NULL;
__type_glCompressedTexSubImage2D __function_glCompressedTexSubImage2D = NULL;
__type_glCopyTexImage2D __function_glCopyTexImage2D = NULL;
__type_glCopyTexSubImage2D __function_glCopyTexSubImage2D = NULL;
__type_glCreateProgram __function_glCreateProgram = NULL;
__type_glCreateShader __function_glCreateShader = NULL;
__type_glCullFace __function_glCullFace = NULL;
__type_glDeleteBuffers __function_glDeleteBuffers = NULL;
__type_glDeleteFramebuffers __function_glDeleteFramebuffers = NULL;
__type_glDeleteProgram __function_glDeleteProgram = NULL;
__type_glDeleteRenderbuffers __function_glDeleteRenderbuffers = NULL;
__type_glDeleteShader __function_glDeleteShader = NULL;
__type_glDeleteTextures __function_glDeleteTextures = NULL;
__type_glDepthFunc __function_glDepthFunc = NULL;
__type_glDepthMask __function_glDepthMask = NULL;
__type_glDepthRangef __function_glDepthRangef = NULL;
__type_glDetachShader __function_glDetachShader = NULL;
__type_glDisable __function_glDisable = NULL;
__type_glDisableVertexAttribArray __function_glDisableVertexAttribArray = NULL;
__type_glDrawArrays __function_glDrawArrays = NULL;
__type_glDrawElements __function_glDrawElements = NULL;
__type_glEnable __function_glEnable = NULL;
__type_glEnableVertexAttribArray __function_glEnableVertexAttribArray = NULL;
__type_glFinish __function_glFinish = NULL;
__type_glFlush __function_glFlush = NULL;
__type_glFramebufferRenderbuffer __function_glFramebufferRenderbuffer = NULL;
__type_glFramebufferTexture2D __function_glFramebufferTexture2D = NULL;
__type_glFrontFace __function_glFrontFace = NULL;
__type_glGenBuffers __function_glGenBuffers = NULL;
__type_glGenerateMipmap __function_glGenerateMipmap = NULL;
__type_glGenFramebuffers __function_glGenFramebuffers = NULL;
__type_glGenRenderbuffers __function_glGenRenderbuffers = NULL;
__type_glGenTextures __function_glGenTextures = NULL;
__type_glGetActiveAttrib __function_glGetActiveAttrib = NULL;
__type_glGetActiveUniform __function_glGetActiveUniform = NULL;
__type_glGetAttachedShaders __function_glGetAttachedShaders = NULL;
__type_glGetAttribLocation __function_glGetAttribLocation = NULL;
__type_glGetBooleanv __function_glGetBooleanv = NULL;
__type_glGetBufferParameteriv __function_glGetBufferParameteriv = NULL;
__type_glGetError __function_glGetError = NULL;
__type_glGetFloatv __function_glGetFloatv = NULL;
__type_glGetFramebufferAttachmentParameteriv __function_glGetFramebufferAttachmentParameteriv = NULL;
__type_glGetIntegerv __function_glGetIntegerv = NULL;
__type_glGetProgramiv __function_glGetProgramiv = NULL;
__type_glGetProgramInfoLog __function_glGetProgramInfoLog = NULL;
__type_glGetRenderbufferParameteriv __function_glGetRenderbufferParameteriv = NULL;
__type_glGetShaderiv __function_glGetShaderiv = NULL;
__type_glGetShaderInfoLog __function_glGetShaderInfoLog = NULL;
__type_glGetShaderPrecisionFormat __function_glGetShaderPrecisionFormat = NULL;
__type_glGetShaderSource __function_glGetShaderSource = NULL;
__type_glGetString __function_glGetString = NULL;
__type_glGetTexParameterfv __function_glGetTexParameterfv = NULL;
__type_glGetTexParameteriv __function_glGetTexParameteriv = NULL;
__type_glGetUniformfv __function_glGetUniformfv = NULL;
__type_glGetUniformiv __function_glGetUniformiv = NULL;
__type_glGetUniformLocation __function_glGetUniformLocation = NULL;
__type_glGetVertexAttribfv __function_glGetVertexAttribfv = NULL;
__type_glGetVertexAttribiv __function_glGetVertexAttribiv = NULL;
__type_glGetVertexAttribPointerv __function_glGetVertexAttribPointerv = NULL;
__type_glHint __function_glHint = NULL;
__type_glIsBuffer __function_glIsBuffer = NULL;
__type_glIsEnabled __function_glIsEnabled = NULL;
__type_glIsFramebuffer __function_glIsFramebuffer = NULL;
__type_glIsProgram __function_glIsProgram = NULL;
__type_glIsRenderbuffer __function_glIsRenderbuffer = NULL;
__type_glIsShader __function_glIsShader = NULL;
__type_glIsTexture __function_glIsTexture = NULL;
__type_glLineWidth __function_glLineWidth = NULL;
__type_glLinkProgram __function_glLinkProgram = NULL;
__type_glPixelStorei __function_glPixelStorei = NULL;
__type_glPolygonOffset __function_glPolygonOffset = NULL;
__type_glReadPixels __function_glReadPixels = NULL;
__type_glReleaseShaderCompiler __function_glReleaseShaderCompiler = NULL;
__type_glRenderbufferStorage __function_glRenderbufferStorage = NULL;
__type_glSampleCoverage __function_glSampleCoverage = NULL;
__type_glScissor __function_glScissor = NULL;
__type_glShaderBinary __function_glShaderBinary = NULL;
__type_glShaderSource __function_glShaderSource = NULL;
__type_glStencilFunc __function_glStencilFunc = NULL;
__type_glStencilFuncSeparate __function_glStencilFuncSeparate = NULL;
__type_glStencilMask __function_glStencilMask = NULL;
__type_glStencilMaskSeparate __function_glStencilMaskSeparate = NULL;
__type_glStencilOp __function_glStencilOp = NULL;
__type_glStencilOpSeparate __function_glStencilOpSeparate = NULL;
__type_glTexImage2D __function_glTexImage2D = NULL;
__type_glTexParameterf __function_glTexParameterf = NULL;
__type_glTexParameterfv __function_glTexParameterfv = NULL;
__type_glTexParameteri __function_glTexParameteri = NULL;
__type_glTexParameteriv __function_glTexParameteriv = NULL;
__type_glTexSubImage2D __function_glTexSubImage2D = NULL;
__type_glUniform1f __function_glUniform1f = NULL;
__type_glUniform1fv __function_glUniform1fv = NULL;
__type_glUniform1i __function_glUniform1i = NULL;
__type_glUniform1iv __function_glUniform1iv = NULL;
__type_glUniform2f __function_glUniform2f = NULL;
__type_glUniform2fv __function_glUniform2fv = NULL;
__type_glUniform2i __function_glUniform2i = NULL;
__type_glUniform2iv __function_glUniform2iv = NULL;
__type_glUniform3f __function_glUniform3f = NULL;
__type_glUniform3fv __function_glUniform3fv = NULL;
__type_glUniform3i __function_glUniform3i = NULL;
__type_glUniform3iv __function_glUniform3iv = NULL;
__type_glUniform4f __function_glUniform4f = NULL;
__type_glUniform4fv __function_glUniform4fv = NULL;
__type_glUniform4i __function_glUniform4i = NULL;
__type_glUniform4iv __function_glUniform4iv = NULL;
__type_glUniformMatrix2fv __function_glUniformMatrix2fv = NULL;
__type_glUniformMatrix3fv __function_glUniformMatrix3fv = NULL;
__type_glUniformMatrix4fv __function_glUniformMatrix4fv = NULL;
__type_glUseProgram __function_glUseProgram = NULL;
__type_glValidateProgram __function_glValidateProgram = NULL;
__type_glVertexAttrib1f __function_glVertexAttrib1f = NULL;
__type_glVertexAttrib1fv __function_glVertexAttrib1fv = NULL;
__type_glVertexAttrib2f __function_glVertexAttrib2f = NULL;
__type_glVertexAttrib2fv __function_glVertexAttrib2fv = NULL;
__type_glVertexAttrib3f __function_glVertexAttrib3f = NULL;
__type_glVertexAttrib3fv __function_glVertexAttrib3fv = NULL;
__type_glVertexAttrib4f __function_glVertexAttrib4f = NULL;
__type_glVertexAttrib4fv __function_glVertexAttrib4fv = NULL;
__type_glVertexAttribPointer __function_glVertexAttribPointer = NULL;
__type_glViewport __function_glViewport = NULL;








void GL_APIENTRY glActiveTexture(GLenum texture) {  __function_glActiveTexture(texture); }
void GL_APIENTRY glAttachShader(GLuint program, GLuint shader) {  __function_glAttachShader(program, shader); }
void GL_APIENTRY glBindAttribLocation(GLuint program, GLuint index, const GLchar* name) {  __function_glBindAttribLocation(program, index, name); }
void GL_APIENTRY glBindBuffer(GLenum target, GLuint buffer) {  __function_glBindBuffer(target, buffer); }
void GL_APIENTRY glBindFramebuffer(GLenum target, GLuint framebuffer) {  __function_glBindFramebuffer(target, framebuffer); }
void GL_APIENTRY glBindRenderbuffer(GLenum target, GLuint renderbuffer) {  __function_glBindRenderbuffer(target, renderbuffer); }
void GL_APIENTRY glBindTexture(GLenum target, GLuint texture) {  __function_glBindTexture(target, texture); }
void GL_APIENTRY glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {  __function_glBlendColor(red, green, blue, alpha); }
void GL_APIENTRY glBlendEquation(GLenum mode) {  __function_glBlendEquation(mode); }
void GL_APIENTRY glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {  __function_glBlendEquationSeparate(modeRGB, modeAlpha); }
void GL_APIENTRY glBlendFunc(GLenum sfactor, GLenum dfactor) {  __function_glBlendFunc(sfactor, dfactor); }
void GL_APIENTRY glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {  __function_glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha); }
void GL_APIENTRY glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) {  __function_glBufferData(target, size, data, usage); }
void GL_APIENTRY glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data) {  __function_glBufferSubData(target, offset, size, data); }
GLenum GL_APIENTRY glCheckFramebufferStatus(GLenum target) { return __function_glCheckFramebufferStatus(target); }
void GL_APIENTRY glClear(GLbitfield mask) {  __function_glClear(mask); }
void GL_APIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {  __function_glClearColor(red, green, blue, alpha); }
void GL_APIENTRY glClearDepthf(GLclampf depth) {  __function_glClearDepthf(depth); }
void GL_APIENTRY glClearStencil(GLint s) {  __function_glClearStencil(s); }
void GL_APIENTRY glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {  __function_glColorMask(red, green, blue, alpha); }
void GL_APIENTRY glCompileShader(GLuint shader) {  __function_glCompileShader(shader); }
void GL_APIENTRY glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data) {  __function_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data); }
void GL_APIENTRY glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data) {  __function_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data); }
void GL_APIENTRY glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {  __function_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border); }
void GL_APIENTRY glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {  __function_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height); }
GLuint GL_APIENTRY glCreateProgram(void) { return __function_glCreateProgram(); }
GLuint GL_APIENTRY glCreateShader(GLenum type) { return __function_glCreateShader(type); }
void GL_APIENTRY glCullFace(GLenum mode) {  __function_glCullFace(mode); }
void GL_APIENTRY glDeleteBuffers(GLsizei n, const GLuint* buffers) {  __function_glDeleteBuffers(n, buffers); }
void GL_APIENTRY glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers) {  __function_glDeleteFramebuffers(n, framebuffers); }
void GL_APIENTRY glDeleteProgram(GLuint program) {  __function_glDeleteProgram(program); }
void GL_APIENTRY glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers) {  __function_glDeleteRenderbuffers(n, renderbuffers); }
void GL_APIENTRY glDeleteShader(GLuint shader) {  __function_glDeleteShader(shader); }
void GL_APIENTRY glDeleteTextures(GLsizei n, const GLuint* textures) {  __function_glDeleteTextures(n, textures); }
void GL_APIENTRY glDepthFunc(GLenum func) {  __function_glDepthFunc(func); }
void GL_APIENTRY glDepthMask(GLboolean flag) {  __function_glDepthMask(flag); }
void GL_APIENTRY glDepthRangef(GLclampf zNear, GLclampf zFar) {  __function_glDepthRangef(zNear, zFar); }
void GL_APIENTRY glDetachShader(GLuint program, GLuint shader) {  __function_glDetachShader(program, shader); }
void GL_APIENTRY glDisable(GLenum cap) {  __function_glDisable(cap); }
void GL_APIENTRY glDisableVertexAttribArray(GLuint index) {  __function_glDisableVertexAttribArray(index); }
void GL_APIENTRY glDrawArrays(GLenum mode, GLint first, GLsizei count) {  __function_glDrawArrays(mode, first, count); }
void GL_APIENTRY glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) {  __function_glDrawElements(mode, count, type, indices); }
void GL_APIENTRY glEnable(GLenum cap) {  __function_glEnable(cap); }
void GL_APIENTRY glEnableVertexAttribArray(GLuint index) {  __function_glEnableVertexAttribArray(index); }
void GL_APIENTRY glFinish(void) {  __function_glFinish(); }
void GL_APIENTRY glFlush(void) {  __function_glFlush(); }
void GL_APIENTRY glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {  __function_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer); }
void GL_APIENTRY glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {  __function_glFramebufferTexture2D(target, attachment, textarget, texture, level); }
void GL_APIENTRY glFrontFace(GLenum mode) {  __function_glFrontFace(mode); }
void GL_APIENTRY glGenBuffers(GLsizei n, GLuint* buffers) {  __function_glGenBuffers(n, buffers); }
void GL_APIENTRY glGenerateMipmap(GLenum target) {  __function_glGenerateMipmap(target); }
void GL_APIENTRY glGenFramebuffers(GLsizei n, GLuint* framebuffers) {  __function_glGenFramebuffers(n, framebuffers); }
void GL_APIENTRY glGenRenderbuffers(GLsizei n, GLuint* renderbuffers) {  __function_glGenRenderbuffers(n, renderbuffers); }
void GL_APIENTRY glGenTextures(GLsizei n, GLuint* textures) {  __function_glGenTextures(n, textures); }
void GL_APIENTRY glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) {  __function_glGetActiveAttrib(program, index, bufsize, length, size, type, name); }
void GL_APIENTRY glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) {  __function_glGetActiveUniform(program, index, bufsize, length, size, type, name); }
void GL_APIENTRY glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders) {  __function_glGetAttachedShaders(program, maxcount, count, shaders); }
int GL_APIENTRY glGetAttribLocation(GLuint program, const GLchar* name) { return __function_glGetAttribLocation(program, name); }
void GL_APIENTRY glGetBooleanv(GLenum pname, GLboolean* params) {  __function_glGetBooleanv(pname, params); }
void GL_APIENTRY glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params) {  __function_glGetBufferParameteriv(target, pname, params); }
GLenum GL_APIENTRY glGetError(void) { return __function_glGetError(); }
void GL_APIENTRY glGetFloatv(GLenum pname, GLfloat* params) {  __function_glGetFloatv(pname, params); }
void GL_APIENTRY glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params) {  __function_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params); }
void GL_APIENTRY glGetIntegerv(GLenum pname, GLint* params) {  __function_glGetIntegerv(pname, params); }
void GL_APIENTRY glGetProgramiv(GLuint program, GLenum pname, GLint* params) {  __function_glGetProgramiv(program, pname, params); }
void GL_APIENTRY glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog) {  __function_glGetProgramInfoLog(program, bufsize, length, infolog); }
void GL_APIENTRY glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params) {  __function_glGetRenderbufferParameteriv(target, pname, params); }
void GL_APIENTRY glGetShaderiv(GLuint shader, GLenum pname, GLint* params) {  __function_glGetShaderiv(shader, pname, params); }
void GL_APIENTRY glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog) {  __function_glGetShaderInfoLog(shader, bufsize, length, infolog); }
void GL_APIENTRY glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision) {  __function_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision); }
void GL_APIENTRY glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source) {  __function_glGetShaderSource(shader, bufsize, length, source); }
const GLubyte* GL_APIENTRY glGetString(GLenum name) { return __function_glGetString(name); }
void GL_APIENTRY glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params) {  __function_glGetTexParameterfv(target, pname, params); }
void GL_APIENTRY glGetTexParameteriv(GLenum target, GLenum pname, GLint* params) {  __function_glGetTexParameteriv(target, pname, params); }
void GL_APIENTRY glGetUniformfv(GLuint program, GLint location, GLfloat* params) {  __function_glGetUniformfv(program, location, params); }
void GL_APIENTRY glGetUniformiv(GLuint program, GLint location, GLint* params) {  __function_glGetUniformiv(program, location, params); }
int GL_APIENTRY glGetUniformLocation(GLuint program, const GLchar* name) { return __function_glGetUniformLocation(program, name); }
void GL_APIENTRY glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params) {  __function_glGetVertexAttribfv(index, pname, params); }
void GL_APIENTRY glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params) {  __function_glGetVertexAttribiv(index, pname, params); }
void GL_APIENTRY glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer) {  __function_glGetVertexAttribPointerv(index, pname, pointer); }
void GL_APIENTRY glHint(GLenum target, GLenum mode) {  __function_glHint(target, mode); }
GLboolean GL_APIENTRY glIsBuffer(GLuint buffer) { return __function_glIsBuffer(buffer); }
GLboolean GL_APIENTRY glIsEnabled(GLenum cap) { return __function_glIsEnabled(cap); }
GLboolean GL_APIENTRY glIsFramebuffer(GLuint framebuffer) { return __function_glIsFramebuffer(framebuffer); }
GLboolean GL_APIENTRY glIsProgram(GLuint program) { return __function_glIsProgram(program); }
GLboolean GL_APIENTRY glIsRenderbuffer(GLuint renderbuffer) { return __function_glIsRenderbuffer(renderbuffer); }
GLboolean GL_APIENTRY glIsShader(GLuint shader) { return __function_glIsShader(shader); }
GLboolean GL_APIENTRY glIsTexture(GLuint texture) { return __function_glIsTexture(texture); }
void GL_APIENTRY glLineWidth(GLfloat width) {  __function_glLineWidth(width); }
void GL_APIENTRY glLinkProgram(GLuint program) {  __function_glLinkProgram(program); }
void GL_APIENTRY glPixelStorei(GLenum pname, GLint param) {  __function_glPixelStorei(pname, param); }
void GL_APIENTRY glPolygonOffset(GLfloat factor, GLfloat units) {  __function_glPolygonOffset(factor, units); }
void GL_APIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels) {  __function_glReadPixels(x, y, width, height, format, type, pixels); }
void GL_APIENTRY glReleaseShaderCompiler(void) {  __function_glReleaseShaderCompiler(); }
void GL_APIENTRY glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {  __function_glRenderbufferStorage(target, internalformat, width, height); }
void GL_APIENTRY glSampleCoverage(GLclampf value, GLboolean invert) {  __function_glSampleCoverage(value, invert); }
void GL_APIENTRY glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {  __function_glScissor(x, y, width, height); }
void GL_APIENTRY glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length) {  __function_glShaderBinary(n, shaders, binaryformat, binary, length); }
void GL_APIENTRY glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length) {  __function_glShaderSource(shader, count, string, length); }
void GL_APIENTRY glStencilFunc(GLenum func, GLint ref, GLuint mask) {  __function_glStencilFunc(func, ref, mask); }
void GL_APIENTRY glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {  __function_glStencilFuncSeparate(face, func, ref, mask); }
void GL_APIENTRY glStencilMask(GLuint mask) {  __function_glStencilMask(mask); }
void GL_APIENTRY glStencilMaskSeparate(GLenum face, GLuint mask) {  __function_glStencilMaskSeparate(face, mask); }
void GL_APIENTRY glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {  __function_glStencilOp(fail, zfail, zpass); }
void GL_APIENTRY glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass) {  __function_glStencilOpSeparate(face, fail, zfail, zpass); }
void GL_APIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels) {  __function_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels); }
void GL_APIENTRY glTexParameterf(GLenum target, GLenum pname, GLfloat param) {  __function_glTexParameterf(target, pname, param); }
void GL_APIENTRY glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params) {  __function_glTexParameterfv(target, pname, params); }
void GL_APIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param) {  __function_glTexParameteri(target, pname, param); }
void GL_APIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint* params) {  __function_glTexParameteriv(target, pname, params); }
void GL_APIENTRY glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels) {  __function_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels); }
void GL_APIENTRY glUniform1f(GLint location, GLfloat x) {  __function_glUniform1f(location, x); }
void GL_APIENTRY glUniform1fv(GLint location, GLsizei count, const GLfloat* v) {  __function_glUniform1fv(location, count, v); }
void GL_APIENTRY glUniform1i(GLint location, GLint x) {  __function_glUniform1i(location, x); }
void GL_APIENTRY glUniform1iv(GLint location, GLsizei count, const GLint* v) {  __function_glUniform1iv(location, count, v); }
void GL_APIENTRY glUniform2f(GLint location, GLfloat x, GLfloat y) {  __function_glUniform2f(location, x, y); }
void GL_APIENTRY glUniform2fv(GLint location, GLsizei count, const GLfloat* v) {  __function_glUniform2fv(location, count, v); }
void GL_APIENTRY glUniform2i(GLint location, GLint x, GLint y) {  __function_glUniform2i(location, x, y); }
void GL_APIENTRY glUniform2iv(GLint location, GLsizei count, const GLint* v) {  __function_glUniform2iv(location, count, v); }
void GL_APIENTRY glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z) {  __function_glUniform3f(location, x, y, z); }
void GL_APIENTRY glUniform3fv(GLint location, GLsizei count, const GLfloat* v) {  __function_glUniform3fv(location, count, v); }
void GL_APIENTRY glUniform3i(GLint location, GLint x, GLint y, GLint z) {  __function_glUniform3i(location, x, y, z); }
void GL_APIENTRY glUniform3iv(GLint location, GLsizei count, const GLint* v) {  __function_glUniform3iv(location, count, v); }
void GL_APIENTRY glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {  __function_glUniform4f(location, x, y, z, w); }
void GL_APIENTRY glUniform4fv(GLint location, GLsizei count, const GLfloat* v) {  __function_glUniform4fv(location, count, v); }
void GL_APIENTRY glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w) {  __function_glUniform4i(location, x, y, z, w); }
void GL_APIENTRY glUniform4iv(GLint location, GLsizei count, const GLint* v) {  __function_glUniform4iv(location, count, v); }
void GL_APIENTRY glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {  __function_glUniformMatrix2fv(location, count, transpose, value); }
void GL_APIENTRY glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {  __function_glUniformMatrix3fv(location, count, transpose, value); }
void GL_APIENTRY glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {  __function_glUniformMatrix4fv(location, count, transpose, value); }
void GL_APIENTRY glUseProgram(GLuint program) {  __function_glUseProgram(program); }
void GL_APIENTRY glValidateProgram(GLuint program) {  __function_glValidateProgram(program); }
void GL_APIENTRY glVertexAttrib1f(GLuint indx, GLfloat x) {  __function_glVertexAttrib1f(indx, x); }
void GL_APIENTRY glVertexAttrib1fv(GLuint indx, const GLfloat* values) {  __function_glVertexAttrib1fv(indx, values); }
void GL_APIENTRY glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y) {  __function_glVertexAttrib2f(indx, x, y); }
void GL_APIENTRY glVertexAttrib2fv(GLuint indx, const GLfloat* values) {  __function_glVertexAttrib2fv(indx, values); }
void GL_APIENTRY glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z) {  __function_glVertexAttrib3f(indx, x, y, z); }
void GL_APIENTRY glVertexAttrib3fv(GLuint indx, const GLfloat* values) {  __function_glVertexAttrib3fv(indx, values); }
void GL_APIENTRY glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {  __function_glVertexAttrib4f(indx, x, y, z, w); }
void GL_APIENTRY glVertexAttrib4fv(GLuint indx, const GLfloat* values) {  __function_glVertexAttrib4fv(indx, values); }
void GL_APIENTRY glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr) {  __function_glVertexAttribPointer(indx, size, type, normalized, stride, ptr); }
void GL_APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {  __function_glViewport(x, y, width, height); }








void opengles2_wrapper_load () {
    __function_glActiveTexture = (__type_glActiveTexture) SDL_GL_GetProcAddress("glActiveTexture");
    __function_glAttachShader = (__type_glAttachShader) SDL_GL_GetProcAddress("glAttachShader");
    __function_glBindAttribLocation = (__type_glBindAttribLocation) SDL_GL_GetProcAddress("glBindAttribLocation");
    __function_glBindBuffer = (__type_glBindBuffer) SDL_GL_GetProcAddress("glBindBuffer");
    __function_glBindFramebuffer = (__type_glBindFramebuffer) SDL_GL_GetProcAddress("glBindFramebuffer");
    __function_glBindRenderbuffer = (__type_glBindRenderbuffer) SDL_GL_GetProcAddress("glBindRenderbuffer");
    __function_glBindTexture = (__type_glBindTexture) SDL_GL_GetProcAddress("glBindTexture");
    __function_glBlendColor = (__type_glBlendColor) SDL_GL_GetProcAddress("glBlendColor");
    __function_glBlendEquation = (__type_glBlendEquation) SDL_GL_GetProcAddress("glBlendEquation");
    __function_glBlendEquationSeparate = (__type_glBlendEquationSeparate) SDL_GL_GetProcAddress("glBlendEquationSeparate");
    __function_glBlendFunc = (__type_glBlendFunc) SDL_GL_GetProcAddress("glBlendFunc");
    __function_glBlendFuncSeparate = (__type_glBlendFuncSeparate) SDL_GL_GetProcAddress("glBlendFuncSeparate");
    __function_glBufferData = (__type_glBufferData) SDL_GL_GetProcAddress("glBufferData");
    __function_glBufferSubData = (__type_glBufferSubData) SDL_GL_GetProcAddress("glBufferSubData");
    __function_glCheckFramebufferStatus = (__type_glCheckFramebufferStatus) SDL_GL_GetProcAddress("glCheckFramebufferStatus");
    __function_glClear = (__type_glClear) SDL_GL_GetProcAddress("glClear");
    __function_glClearColor = (__type_glClearColor) SDL_GL_GetProcAddress("glClearColor");
    __function_glClearDepthf = (__type_glClearDepthf) SDL_GL_GetProcAddress("glClearDepthf");
    __function_glClearStencil = (__type_glClearStencil) SDL_GL_GetProcAddress("glClearStencil");
    __function_glColorMask = (__type_glColorMask) SDL_GL_GetProcAddress("glColorMask");
    __function_glCompileShader = (__type_glCompileShader) SDL_GL_GetProcAddress("glCompileShader");
    __function_glCompressedTexImage2D = (__type_glCompressedTexImage2D) SDL_GL_GetProcAddress("glCompressedTexImage2D");
    __function_glCompressedTexSubImage2D = (__type_glCompressedTexSubImage2D) SDL_GL_GetProcAddress("glCompressedTexSubImage2D");
    __function_glCopyTexImage2D = (__type_glCopyTexImage2D) SDL_GL_GetProcAddress("glCopyTexImage2D");
    __function_glCopyTexSubImage2D = (__type_glCopyTexSubImage2D) SDL_GL_GetProcAddress("glCopyTexSubImage2D");
    __function_glCreateProgram = (__type_glCreateProgram) SDL_GL_GetProcAddress("glCreateProgram");
    __function_glCreateShader = (__type_glCreateShader) SDL_GL_GetProcAddress("glCreateShader");
    __function_glCullFace = (__type_glCullFace) SDL_GL_GetProcAddress("glCullFace");
    __function_glDeleteBuffers = (__type_glDeleteBuffers) SDL_GL_GetProcAddress("glDeleteBuffers");
    __function_glDeleteFramebuffers = (__type_glDeleteFramebuffers) SDL_GL_GetProcAddress("glDeleteFramebuffers");
    __function_glDeleteProgram = (__type_glDeleteProgram) SDL_GL_GetProcAddress("glDeleteProgram");
    __function_glDeleteRenderbuffers = (__type_glDeleteRenderbuffers) SDL_GL_GetProcAddress("glDeleteRenderbuffers");
    __function_glDeleteShader = (__type_glDeleteShader) SDL_GL_GetProcAddress("glDeleteShader");
    __function_glDeleteTextures = (__type_glDeleteTextures) SDL_GL_GetProcAddress("glDeleteTextures");
    __function_glDepthFunc = (__type_glDepthFunc) SDL_GL_GetProcAddress("glDepthFunc");
    __function_glDepthMask = (__type_glDepthMask) SDL_GL_GetProcAddress("glDepthMask");
    __function_glDepthRangef = (__type_glDepthRangef) SDL_GL_GetProcAddress("glDepthRangef");
    __function_glDetachShader = (__type_glDetachShader) SDL_GL_GetProcAddress("glDetachShader");
    __function_glDisable = (__type_glDisable) SDL_GL_GetProcAddress("glDisable");
    __function_glDisableVertexAttribArray = (__type_glDisableVertexAttribArray) SDL_GL_GetProcAddress("glDisableVertexAttribArray");
    __function_glDrawArrays = (__type_glDrawArrays) SDL_GL_GetProcAddress("glDrawArrays");
    __function_glDrawElements = (__type_glDrawElements) SDL_GL_GetProcAddress("glDrawElements");
    __function_glEnable = (__type_glEnable) SDL_GL_GetProcAddress("glEnable");
    __function_glEnableVertexAttribArray = (__type_glEnableVertexAttribArray) SDL_GL_GetProcAddress("glEnableVertexAttribArray");
    __function_glFinish = (__type_glFinish) SDL_GL_GetProcAddress("glFinish");
    __function_glFlush = (__type_glFlush) SDL_GL_GetProcAddress("glFlush");
    __function_glFramebufferRenderbuffer = (__type_glFramebufferRenderbuffer) SDL_GL_GetProcAddress("glFramebufferRenderbuffer");
    __function_glFramebufferTexture2D = (__type_glFramebufferTexture2D) SDL_GL_GetProcAddress("glFramebufferTexture2D");
    __function_glFrontFace = (__type_glFrontFace) SDL_GL_GetProcAddress("glFrontFace");
    __function_glGenBuffers = (__type_glGenBuffers) SDL_GL_GetProcAddress("glGenBuffers");
    __function_glGenerateMipmap = (__type_glGenerateMipmap) SDL_GL_GetProcAddress("glGenerateMipmap");
    __function_glGenFramebuffers = (__type_glGenFramebuffers) SDL_GL_GetProcAddress("glGenFramebuffers");
    __function_glGenRenderbuffers = (__type_glGenRenderbuffers) SDL_GL_GetProcAddress("glGenRenderbuffers");
    __function_glGenTextures = (__type_glGenTextures) SDL_GL_GetProcAddress("glGenTextures");
    __function_glGetActiveAttrib = (__type_glGetActiveAttrib) SDL_GL_GetProcAddress("glGetActiveAttrib");
    __function_glGetActiveUniform = (__type_glGetActiveUniform) SDL_GL_GetProcAddress("glGetActiveUniform");
    __function_glGetAttachedShaders = (__type_glGetAttachedShaders) SDL_GL_GetProcAddress("glGetAttachedShaders");
    __function_glGetAttribLocation = (__type_glGetAttribLocation) SDL_GL_GetProcAddress("glGetAttribLocation");
    __function_glGetBooleanv = (__type_glGetBooleanv) SDL_GL_GetProcAddress("glGetBooleanv");
    __function_glGetBufferParameteriv = (__type_glGetBufferParameteriv) SDL_GL_GetProcAddress("glGetBufferParameteriv");
    __function_glGetError = (__type_glGetError) SDL_GL_GetProcAddress("glGetError");
    __function_glGetFloatv = (__type_glGetFloatv) SDL_GL_GetProcAddress("glGetFloatv");
    __function_glGetFramebufferAttachmentParameteriv = (__type_glGetFramebufferAttachmentParameteriv) SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
    __function_glGetIntegerv = (__type_glGetIntegerv) SDL_GL_GetProcAddress("glGetIntegerv");
    __function_glGetProgramiv = (__type_glGetProgramiv) SDL_GL_GetProcAddress("glGetProgramiv");
    __function_glGetProgramInfoLog = (__type_glGetProgramInfoLog) SDL_GL_GetProcAddress("glGetProgramInfoLog");
    __function_glGetRenderbufferParameteriv = (__type_glGetRenderbufferParameteriv) SDL_GL_GetProcAddress("glGetRenderbufferParameteriv");
    __function_glGetShaderiv = (__type_glGetShaderiv) SDL_GL_GetProcAddress("glGetShaderiv");
    __function_glGetShaderInfoLog = (__type_glGetShaderInfoLog) SDL_GL_GetProcAddress("glGetShaderInfoLog");
    __function_glGetShaderPrecisionFormat = (__type_glGetShaderPrecisionFormat) SDL_GL_GetProcAddress("glGetShaderPrecisionFormat");
    __function_glGetShaderSource = (__type_glGetShaderSource) SDL_GL_GetProcAddress("glGetShaderSource");
    __function_glGetString = (__type_glGetString) SDL_GL_GetProcAddress("glGetString");
    __function_glGetTexParameterfv = (__type_glGetTexParameterfv) SDL_GL_GetProcAddress("glGetTexParameterfv");
    __function_glGetTexParameteriv = (__type_glGetTexParameteriv) SDL_GL_GetProcAddress("glGetTexParameteriv");
    __function_glGetUniformfv = (__type_glGetUniformfv) SDL_GL_GetProcAddress("glGetUniformfv");
    __function_glGetUniformiv = (__type_glGetUniformiv) SDL_GL_GetProcAddress("glGetUniformiv");
    __function_glGetUniformLocation = (__type_glGetUniformLocation) SDL_GL_GetProcAddress("glGetUniformLocation");
    __function_glGetVertexAttribfv = (__type_glGetVertexAttribfv) SDL_GL_GetProcAddress("glGetVertexAttribfv");
    __function_glGetVertexAttribiv = (__type_glGetVertexAttribiv) SDL_GL_GetProcAddress("glGetVertexAttribiv");
    __function_glGetVertexAttribPointerv = (__type_glGetVertexAttribPointerv) SDL_GL_GetProcAddress("glGetVertexAttribPointerv");
    __function_glHint = (__type_glHint) SDL_GL_GetProcAddress("glHint");
    __function_glIsBuffer = (__type_glIsBuffer) SDL_GL_GetProcAddress("glIsBuffer");
    __function_glIsEnabled = (__type_glIsEnabled) SDL_GL_GetProcAddress("glIsEnabled");
    __function_glIsFramebuffer = (__type_glIsFramebuffer) SDL_GL_GetProcAddress("glIsFramebuffer");
    __function_glIsProgram = (__type_glIsProgram) SDL_GL_GetProcAddress("glIsProgram");
    __function_glIsRenderbuffer = (__type_glIsRenderbuffer) SDL_GL_GetProcAddress("glIsRenderbuffer");
    __function_glIsShader = (__type_glIsShader) SDL_GL_GetProcAddress("glIsShader");
    __function_glIsTexture = (__type_glIsTexture) SDL_GL_GetProcAddress("glIsTexture");
    __function_glLineWidth = (__type_glLineWidth) SDL_GL_GetProcAddress("glLineWidth");
    __function_glLinkProgram = (__type_glLinkProgram) SDL_GL_GetProcAddress("glLinkProgram");
    __function_glPixelStorei = (__type_glPixelStorei) SDL_GL_GetProcAddress("glPixelStorei");
    __function_glPolygonOffset = (__type_glPolygonOffset) SDL_GL_GetProcAddress("glPolygonOffset");
    __function_glReadPixels = (__type_glReadPixels) SDL_GL_GetProcAddress("glReadPixels");
    __function_glReleaseShaderCompiler = (__type_glReleaseShaderCompiler) SDL_GL_GetProcAddress("glReleaseShaderCompiler");
    __function_glRenderbufferStorage = (__type_glRenderbufferStorage) SDL_GL_GetProcAddress("glRenderbufferStorage");
    __function_glSampleCoverage = (__type_glSampleCoverage) SDL_GL_GetProcAddress("glSampleCoverage");
    __function_glScissor = (__type_glScissor) SDL_GL_GetProcAddress("glScissor");
    __function_glShaderBinary = (__type_glShaderBinary) SDL_GL_GetProcAddress("glShaderBinary");
    __function_glShaderSource = (__type_glShaderSource) SDL_GL_GetProcAddress("glShaderSource");
    __function_glStencilFunc = (__type_glStencilFunc) SDL_GL_GetProcAddress("glStencilFunc");
    __function_glStencilFuncSeparate = (__type_glStencilFuncSeparate) SDL_GL_GetProcAddress("glStencilFuncSeparate");
    __function_glStencilMask = (__type_glStencilMask) SDL_GL_GetProcAddress("glStencilMask");
    __function_glStencilMaskSeparate = (__type_glStencilMaskSeparate) SDL_GL_GetProcAddress("glStencilMaskSeparate");
    __function_glStencilOp = (__type_glStencilOp) SDL_GL_GetProcAddress("glStencilOp");
    __function_glStencilOpSeparate = (__type_glStencilOpSeparate) SDL_GL_GetProcAddress("glStencilOpSeparate");
    __function_glTexImage2D = (__type_glTexImage2D) SDL_GL_GetProcAddress("glTexImage2D");
    __function_glTexParameterf = (__type_glTexParameterf) SDL_GL_GetProcAddress("glTexParameterf");
    __function_glTexParameterfv = (__type_glTexParameterfv) SDL_GL_GetProcAddress("glTexParameterfv");
    __function_glTexParameteri = (__type_glTexParameteri) SDL_GL_GetProcAddress("glTexParameteri");
    __function_glTexParameteriv = (__type_glTexParameteriv) SDL_GL_GetProcAddress("glTexParameteriv");
    __function_glTexSubImage2D = (__type_glTexSubImage2D) SDL_GL_GetProcAddress("glTexSubImage2D");
    __function_glUniform1f = (__type_glUniform1f) SDL_GL_GetProcAddress("glUniform1f");
    __function_glUniform1fv = (__type_glUniform1fv) SDL_GL_GetProcAddress("glUniform1fv");
    __function_glUniform1i = (__type_glUniform1i) SDL_GL_GetProcAddress("glUniform1i");
    __function_glUniform1iv = (__type_glUniform1iv) SDL_GL_GetProcAddress("glUniform1iv");
    __function_glUniform2f = (__type_glUniform2f) SDL_GL_GetProcAddress("glUniform2f");
    __function_glUniform2fv = (__type_glUniform2fv) SDL_GL_GetProcAddress("glUniform2fv");
    __function_glUniform2i = (__type_glUniform2i) SDL_GL_GetProcAddress("glUniform2i");
    __function_glUniform2iv = (__type_glUniform2iv) SDL_GL_GetProcAddress("glUniform2iv");
    __function_glUniform3f = (__type_glUniform3f) SDL_GL_GetProcAddress("glUniform3f");
    __function_glUniform3fv = (__type_glUniform3fv) SDL_GL_GetProcAddress("glUniform3fv");
    __function_glUniform3i = (__type_glUniform3i) SDL_GL_GetProcAddress("glUniform3i");
    __function_glUniform3iv = (__type_glUniform3iv) SDL_GL_GetProcAddress("glUniform3iv");
    __function_glUniform4f = (__type_glUniform4f) SDL_GL_GetProcAddress("glUniform4f");
    __function_glUniform4fv = (__type_glUniform4fv) SDL_GL_GetProcAddress("glUniform4fv");
    __function_glUniform4i = (__type_glUniform4i) SDL_GL_GetProcAddress("glUniform4i");
    __function_glUniform4iv = (__type_glUniform4iv) SDL_GL_GetProcAddress("glUniform4iv");
    __function_glUniformMatrix2fv = (__type_glUniformMatrix2fv) SDL_GL_GetProcAddress("glUniformMatrix2fv");
    __function_glUniformMatrix3fv = (__type_glUniformMatrix3fv) SDL_GL_GetProcAddress("glUniformMatrix3fv");
    __function_glUniformMatrix4fv = (__type_glUniformMatrix4fv) SDL_GL_GetProcAddress("glUniformMatrix4fv");
    __function_glUseProgram = (__type_glUseProgram) SDL_GL_GetProcAddress("glUseProgram");
    __function_glValidateProgram = (__type_glValidateProgram) SDL_GL_GetProcAddress("glValidateProgram");
    __function_glVertexAttrib1f = (__type_glVertexAttrib1f) SDL_GL_GetProcAddress("glVertexAttrib1f");
    __function_glVertexAttrib1fv = (__type_glVertexAttrib1fv) SDL_GL_GetProcAddress("glVertexAttrib1fv");
    __function_glVertexAttrib2f = (__type_glVertexAttrib2f) SDL_GL_GetProcAddress("glVertexAttrib2f");
    __function_glVertexAttrib2fv = (__type_glVertexAttrib2fv) SDL_GL_GetProcAddress("glVertexAttrib2fv");
    __function_glVertexAttrib3f = (__type_glVertexAttrib3f) SDL_GL_GetProcAddress("glVertexAttrib3f");
    __function_glVertexAttrib3fv = (__type_glVertexAttrib3fv) SDL_GL_GetProcAddress("glVertexAttrib3fv");
    __function_glVertexAttrib4f = (__type_glVertexAttrib4f) SDL_GL_GetProcAddress("glVertexAttrib4f");
    __function_glVertexAttrib4fv = (__type_glVertexAttrib4fv) SDL_GL_GetProcAddress("glVertexAttrib4fv");
    __function_glVertexAttribPointer = (__type_glVertexAttribPointer) SDL_GL_GetProcAddress("glVertexAttribPointer");
    __function_glViewport = (__type_glViewport) SDL_GL_GetProcAddress("glViewport");
}







void opengles2_wrapper_unload () {
    __function_glActiveTexture = NULL;
    __function_glAttachShader = NULL;
    __function_glBindAttribLocation = NULL;
    __function_glBindBuffer = NULL;
    __function_glBindFramebuffer = NULL;
    __function_glBindRenderbuffer = NULL;
    __function_glBindTexture = NULL;
    __function_glBlendColor = NULL;
    __function_glBlendEquation = NULL;
    __function_glBlendEquationSeparate = NULL;
    __function_glBlendFunc = NULL;
    __function_glBlendFuncSeparate = NULL;
    __function_glBufferData = NULL;
    __function_glBufferSubData = NULL;
    __function_glCheckFramebufferStatus = NULL;
    __function_glClear = NULL;
    __function_glClearColor = NULL;
    __function_glClearDepthf = NULL;
    __function_glClearStencil = NULL;
    __function_glColorMask = NULL;
    __function_glCompileShader = NULL;
    __function_glCompressedTexImage2D = NULL;
    __function_glCompressedTexSubImage2D = NULL;
    __function_glCopyTexImage2D = NULL;
    __function_glCopyTexSubImage2D = NULL;
    __function_glCreateProgram = NULL;
    __function_glCreateShader = NULL;
    __function_glCullFace = NULL;
    __function_glDeleteBuffers = NULL;
    __function_glDeleteFramebuffers = NULL;
    __function_glDeleteProgram = NULL;
    __function_glDeleteRenderbuffers = NULL;
    __function_glDeleteShader = NULL;
    __function_glDeleteTextures = NULL;
    __function_glDepthFunc = NULL;
    __function_glDepthMask = NULL;
    __function_glDepthRangef = NULL;
    __function_glDetachShader = NULL;
    __function_glDisable = NULL;
    __function_glDisableVertexAttribArray = NULL;
    __function_glDrawArrays = NULL;
    __function_glDrawElements = NULL;
    __function_glEnable = NULL;
    __function_glEnableVertexAttribArray = NULL;
    __function_glFinish = NULL;
    __function_glFlush = NULL;
    __function_glFramebufferRenderbuffer = NULL;
    __function_glFramebufferTexture2D = NULL;
    __function_glFrontFace = NULL;
    __function_glGenBuffers = NULL;
    __function_glGenerateMipmap = NULL;
    __function_glGenFramebuffers = NULL;
    __function_glGenRenderbuffers = NULL;
    __function_glGenTextures = NULL;
    __function_glGetActiveAttrib = NULL;
    __function_glGetActiveUniform = NULL;
    __function_glGetAttachedShaders = NULL;
    __function_glGetAttribLocation = NULL;
    __function_glGetBooleanv = NULL;
    __function_glGetBufferParameteriv = NULL;
    __function_glGetError = NULL;
    __function_glGetFloatv = NULL;
    __function_glGetFramebufferAttachmentParameteriv = NULL;
    __function_glGetIntegerv = NULL;
    __function_glGetProgramiv = NULL;
    __function_glGetProgramInfoLog = NULL;
    __function_glGetRenderbufferParameteriv = NULL;
    __function_glGetShaderiv = NULL;
    __function_glGetShaderInfoLog = NULL;
    __function_glGetShaderPrecisionFormat = NULL;
    __function_glGetShaderSource = NULL;
    __function_glGetString = NULL;
    __function_glGetTexParameterfv = NULL;
    __function_glGetTexParameteriv = NULL;
    __function_glGetUniformfv = NULL;
    __function_glGetUniformiv = NULL;
    __function_glGetUniformLocation = NULL;
    __function_glGetVertexAttribfv = NULL;
    __function_glGetVertexAttribiv = NULL;
    __function_glGetVertexAttribPointerv = NULL;
    __function_glHint = NULL;
    __function_glIsBuffer = NULL;
    __function_glIsEnabled = NULL;
    __function_glIsFramebuffer = NULL;
    __function_glIsProgram = NULL;
    __function_glIsRenderbuffer = NULL;
    __function_glIsShader = NULL;
    __function_glIsTexture = NULL;
    __function_glLineWidth = NULL;
    __function_glLinkProgram = NULL;
    __function_glPixelStorei = NULL;
    __function_glPolygonOffset = NULL;
    __function_glReadPixels = NULL;
    __function_glReleaseShaderCompiler = NULL;
    __function_glRenderbufferStorage = NULL;
    __function_glSampleCoverage = NULL;
    __function_glScissor = NULL;
    __function_glShaderBinary = NULL;
    __function_glShaderSource = NULL;
    __function_glStencilFunc = NULL;
    __function_glStencilFuncSeparate = NULL;
    __function_glStencilMask = NULL;
    __function_glStencilMaskSeparate = NULL;
    __function_glStencilOp = NULL;
    __function_glStencilOpSeparate = NULL;
    __function_glTexImage2D = NULL;
    __function_glTexParameterf = NULL;
    __function_glTexParameterfv = NULL;
    __function_glTexParameteri = NULL;
    __function_glTexParameteriv = NULL;
    __function_glTexSubImage2D = NULL;
    __function_glUniform1f = NULL;
    __function_glUniform1fv = NULL;
    __function_glUniform1i = NULL;
    __function_glUniform1iv = NULL;
    __function_glUniform2f = NULL;
    __function_glUniform2fv = NULL;
    __function_glUniform2i = NULL;
    __function_glUniform2iv = NULL;
    __function_glUniform3f = NULL;
    __function_glUniform3fv = NULL;
    __function_glUniform3i = NULL;
    __function_glUniform3iv = NULL;
    __function_glUniform4f = NULL;
    __function_glUniform4fv = NULL;
    __function_glUniform4i = NULL;
    __function_glUniform4iv = NULL;
    __function_glUniformMatrix2fv = NULL;
    __function_glUniformMatrix3fv = NULL;
    __function_glUniformMatrix4fv = NULL;
    __function_glUseProgram = NULL;
    __function_glValidateProgram = NULL;
    __function_glVertexAttrib1f = NULL;
    __function_glVertexAttrib1fv = NULL;
    __function_glVertexAttrib2f = NULL;
    __function_glVertexAttrib2fv = NULL;
    __function_glVertexAttrib3f = NULL;
    __function_glVertexAttrib3fv = NULL;
    __function_glVertexAttrib4f = NULL;
    __function_glVertexAttrib4fv = NULL;
    __function_glVertexAttribPointer = NULL;
    __function_glViewport = NULL;
}

#ifdef __cplusplus
}
#endif