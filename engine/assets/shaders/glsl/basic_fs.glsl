#version 460 core
#extension GL_ARB_gpu_shader_int64 : require
#extension GL_ARB_bindless_texture : require

in vec2 texCoord;
in vec4 quadColor;
out vec4 FragColor;
in sampler2D textureHandle;

void main()
{
    //float d = length(localPos);
    //float circle = 1.0 - smoothstep(0.48, 0.5, d);
    //FragColor = quadColor * circle;

    FragColor = texture(textureHandle, texCoord) * quadColor;
}