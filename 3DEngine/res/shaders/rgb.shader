#shader vertex
#version 110
uniform mat4 MVP;
attribute vec3 v_pos;
attribute vec2 v_uv;
attribute vec3 v_normal;
varying vec3 f_normal;
varying vec2 f_uv;
varying vec3 f_col;
void main()
{
	gl_Position = MVP * vec4(v_pos, 1.0);
	f_normal = v_normal;
	f_uv = v_uv;
	f_col = vec3(abs(v_normal.x), abs(v_normal.y), abs(v_normal.z));
}

#shader fragment
#version 110
varying vec3 f_normal;
varying vec3 f_col;
uniform float opacity;
void main()
{
	gl_FragColor = vec4(f_col, opacity);
}