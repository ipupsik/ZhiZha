#version 430

uniform mat4 Transform;

layout (location = 0) in vec2 _vertexPos;

out vec2 vertexPos;

void main() {
    gl_Position = Transform * vec4(_vertexPos, 0, 1);
    vertexPos = _vertexPos;
}