#version 430

layout (location = 0) uniform sampler2D tex0;

in vec2 vertexPos;

out vec4 _diffuseColor;

void main() {
    _diffuseColor = texture2D(tex0, gl_FragCoord.xy / 300.f);
    _diffuseColor *= 1.4f;
}