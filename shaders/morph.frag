#ifdef GL_ES
precision mediump float;
#endif

uniform vec4 u_color;
uniform sampler2D u_texture;

varying vec2 v_texCoord;
varying vec4 v_normal;

void main(void)
{
    vec4 color = texture2D(u_texture, v_texCoord);
	gl_FragColor = u_color * color;
}
