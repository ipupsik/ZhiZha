#version 430

layout (location = 0) uniform sampler2D tex0;

in vec2 vertexPos;

out vec4 _diffuseColor;

void main() {
    _diffuseColor = texture2D(tex0, vertexPos);
}