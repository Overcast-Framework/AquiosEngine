#version 460 core

layout(std430, binding = 2) buffer BatchedColor
{
    vec4 BaseColors[2000];
};

flat in int instanceId;
out vec4 FragColor;

void main()
{
    FragColor = BaseColors[instanceId];
}