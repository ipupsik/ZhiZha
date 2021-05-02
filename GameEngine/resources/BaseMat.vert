#version 430

in vec3 vertexpos;

void main()
{
	gl_Position = vec4(vertexpos, 1.0);
}