#pragma once
#include <AquiosEngine/Renderer/GPUBuffer.h>

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

    struct BindBufferCmd {
        GPUBuffer* buffer;
    };
}