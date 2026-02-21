#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBitangent;
layout (location = 4) in vec2 aTexCoord;

struct Int_QuadInfo
{
	vec4 Color;
	mat4 MVP;
};

layout(std430, binding = 0) buffer QuadTransforms
{
    Int_QuadInfo info[];
};

out vec4 quadColor;

void main()
{
	Int_QuadInfo quadInfo = info[gl_InstanceID];
	quadColor = quadInfo.Color;
	gl_Position = quadInfo.MVP*vec4(aPos, 1);
}