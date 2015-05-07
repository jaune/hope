#ifdef GL_ES
	precision highp float;
#endif

uniform sampler2D uTilesetSampler;
uniform sampler2D uAreaSampler;

uniform float uTileSize;
uniform float uAreaSize;

uniform float uTilesetSize;
uniform float uTilesetIndexMax;

varying vec2 vTextureCoord;

void main(void) {
	float tilesetIndexWidth = uTilesetSize / uTileSize;
	float i = texture2D(uAreaSampler, vTextureCoord.st).x * uTilesetIndexMax;
    float x = mod(i, tilesetIndexWidth);

	vec2 index = vec2(floor(x), (i - x) / tilesetIndexWidth) * uTileSize;

	gl_FragColor = texture2D(
		uTilesetSampler, 
		(mod((vTextureCoord.st * uAreaSize), uTileSize) + index) / uTilesetSize
	);


}
