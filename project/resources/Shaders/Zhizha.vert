#version 430

layout (location = 0) in vec2 _vertexPos;

out vec2 vertexPos;

void main() {
    gl_Position = vec4(_vertexPos, 0, 1);
    vertexPos = _vertexPos;
}