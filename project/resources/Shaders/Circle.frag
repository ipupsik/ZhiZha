#version 430

layout (location = 1) uniform sampler2D tex0;

in vec2 texPos;

out vec4 _diffuseColor;

void main() {
    _diffuseColor = texture2D(tex0, texPos);
}