#version 460 core
#extension GL_ARB_gpu_shader_int64 : require
#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBitangent;
layout (location = 4) in vec2 aTexCoord;

struct Int_QuadInfo
{
	vec4 Color;
	mat4 MVP;
	sampler2D TextureHandle;
};

layout(std430, binding = 0) buffer QuadTransforms
{
    Int_QuadInfo info[];
};

out vec4 quadColor;
out vec2 texCoord;
out sampler2D textureHandle;

void main()
{
	Int_QuadInfo quadInfo = info[gl_InstanceID];
	quadColor = quadInfo.Color;
	texCoord = aTexCoord;
	textureHandle = quadInfo.TextureHandle;
	gl_Position	= quadInfo.MVP*vec4(aPos, 1);
}