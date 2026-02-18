#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBitangent;
layout (location = 4) in vec2 aTexCoord;

layout(std430, binding = 1) buffer QuadTransforms
{
    mat4 model[2000];
};

flat out int instanceId;

void main()
{
	instanceId = gl_InstanceID;
	gl_Position = model[gl_InstanceID]*vec4(aPos, 1);
}