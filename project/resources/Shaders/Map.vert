#version 430

in vec2 _vertexPos;
in vec2 _texCoord;

uniform mat4 Transform;

out vec2 texCoord;

void main()
{
	gl_Position = Transform * vec4(_vertexPos, 0, 1.0);

	texCoord = _texCoord;
}