#shader vertex
#version 330
uniform mat4 MVP;
attribute vec3 v_pos;
attribute vec2 v_uv;
attribute vec3 v_normal;
varying vec3 f_normal;
varying vec2 f_uv;
void main()
{
	gl_Position = MVP * vec4(v_pos, 1.0);
	f_uv = v_uv;
	f_normal = v_normal;
}

#shader fragment
#version 330
varying vec2 f_uv;
uniform sampler2D u_Texture;
void main()
{
	gl_FragColor = texture(u_Texture, f_uv);
}