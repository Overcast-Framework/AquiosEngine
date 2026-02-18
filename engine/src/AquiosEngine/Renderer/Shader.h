#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <AquiosEngine/IDestructable.h>
#include <AquiosEngine/Renderer/GPUBuffer.h>

namespace Aquios
{
	enum class ShaderType
	{
		Vertex, Fragment,
		Compute, Geometry,
		Mesh, Hit, Miss
	};

	struct ShaderBufferBinding
	{
	public:
		uint32_t BindingIndex;
		GPUBuffer::Type Type;
		std::string Name; // for debugging
	};

	class Shader : public IDestructable
	{
	public:
		ShaderType Type;

		void SetUniformBuffer(CommandList* list, uint32_t index, GPUBuffer* buffer);
		void SetStorageBuffer(CommandList* list, uint32_t index, GPUBuffer* buffer);

		virtual ~Shader() = default;
	private:
		std::unordered_map<uint32_t, ShaderBufferBinding> m_Bindings;
	};
}