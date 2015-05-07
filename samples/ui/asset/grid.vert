#ifdef GL_ES
	precision highp float;
#endif

attribute vec2 aVertexPosition;
attribute vec2 aTextureCoord;

uniform mat4 uViewportMatrix;

varying vec2 vTextureCoord;

void main(void) {
	vTextureCoord = aTextureCoord;
	gl_Position = uViewportMatrix * vec4(aVertexPosition, 0.0, 1.0);
}