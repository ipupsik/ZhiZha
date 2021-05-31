#version 430

layout(location = 1) uniform sampler2D tex0;

in vec2 texCoord;

out vec4 diffuseColor;

void main()
{
    diffuseColor = texture2D(tex0, 1 - texCoord);
    diffuseColor.xyz *= diffuseColor.xyz * 2.0f;
}