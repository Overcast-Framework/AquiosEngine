#include "aqpch.h"
#include "Shader.h"

#include <AquiosEngine/Renderer/CommandList.h>

void Aquios::Shader::SetUniformBuffer(CommandList* list, uint32_t index, GPUBuffer* buffer)
{
	list->Record(Commands::SetShaderUniformBufferCmd(buffer, index, this));
}

void Aquios::Shader::SetStorageBuffer(CommandList* list, uint32_t index, GPUBuffer* buffer)
{
	list->Record(Commands::LambdaCmd(
		[this, index]() {
			this->m_Bindings.insert({ index, { index, GPUBuffer::Type::StorageBlock, "SB" }});
		}
	));
	list->Record(Commands::SetShaderStorageBlockCmd(buffer, index, this));
}