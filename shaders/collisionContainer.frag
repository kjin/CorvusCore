#ifdef GL_ES
precision mediump float;
#endif

uniform vec4 u_color;

varying vec4 v_normal;

void main(void)
{
	gl_FragColor = u_color * vec4(v_normal.xyz + vec3(.5,.5,.5), 0.5);
}
