#pragma once
#include <functional>

namespace Aquios {
    class Pipeline;
    class GPUBuffer;
    class Mesh;
    class Shader;
}

namespace Aquios::Commands
{
    struct ClearColorCmd {
        float r, g, b, a;
    };

    struct ClearCmd
    {
        struct ClearOptions
        {
            bool DepthBit = false;
            bool ColorBit = true;
        } clearOptions;
    };

    struct BindBufferBaseCmd
    {
        uint32_t bindPoint;
        GPUBuffer* buffer;

        BindBufferBaseCmd(const uint32_t& bindPoint, GPUBuffer* buffer)
            : bindPoint(bindPoint), buffer(buffer)
        {
        }
    };

    struct UploadBufferDataCmd {
        GPUBuffer* buffer;
        std::vector<uint8_t> data;
        size_t offset, size;

        UploadBufferDataCmd(GPUBuffer* buf, const void* src, size_t sz, size_t off)
            : buffer(buf), offset(off), size(sz), data((uint8_t*)src, (uint8_t*)src + sz) {
        }
    };

    struct SetShaderUniformBufferCmd {
        GPUBuffer* buffer;
        uint32_t index;
        Shader* shader;

        SetShaderUniformBufferCmd(GPUBuffer* buffer, const uint32_t& index, Shader* shader)
            : buffer(buffer), index(index), shader(shader)
        {
        }
    };

    struct BindPipelineCmd {
        Pipeline *pipeline;

        BindPipelineCmd(Pipeline* ppl)
            : pipeline(ppl)
        {
        }
    };
    
    struct SetShaderStorageBlockCmd {
        GPUBuffer* buffer;
        uint32_t index;
        Shader* shader;

        SetShaderStorageBlockCmd(GPUBuffer* buffer, const uint32_t& index, Shader* shader)
            : buffer(buffer), index(index), shader(shader)
        {
        }
    };

    struct DrawMeshCmd
    {
        Mesh* mesh;

        DrawMeshCmd(Mesh* m) 
            : mesh(m)
        {
        }
    };

    struct LambdaCmd
    {
        std::function<void()> Execute;

        LambdaCmd(const std::function<void()>& Execute)
            : Execute(Execute)
        {
        }
    };
}