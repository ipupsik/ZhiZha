#version 430

uniform mat4 Transform;

layout (location = 0) in vec2 _vertexPos;

layout (location = 1) in vec2 _texPos;

out vec2 texPos;

void main() {
    gl_Position = Transform * vec4(_vertexPos, 0, 1);
    texPos = _texPos;
}