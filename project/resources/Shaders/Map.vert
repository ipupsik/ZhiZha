#version 430

layout (location = 0) in vec2 _vertexPos;
layout (location = 1) in vec2 _texCoord;

layout (location = 0) uniform mat4 Transform;

out vec2 texCoord;

void main()
{
	gl_Position = Transform * vec4(_vertexPos, 0, 1.0);

	texCoord = _texCoord;
}