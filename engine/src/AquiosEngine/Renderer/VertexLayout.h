#pragma once
#include <string>
#include <vector>
#include <AquiosEngine/IDestructable.h>
#include <AquiosEngine/Renderer/GPUBuffer.h>
#include "Format.h"

namespace Aquios
{
	struct VertexAttribute
	{
	public:
		std::string SemanticName;
		uint32_t SemanticIndex;
		Format AttribFormat;
		uint32_t Offset;
		int Stride;

		enum class InputRate { PerVertex, PerInstance } InputRate;
	};

	class VertexLayout : public IDestructable
	{
	public:
		virtual void AddAttribute(const VertexAttribute& attrib) = 0;
		virtual void Build() = 0;

		virtual void AssignBuffer(GPUBuffer* buf, uint32_t bindingIndex = 0, size_t stride = 0) = 0;

		virtual void Release() = 0;

		std::vector<VertexAttribute>& GetAttributes() { return m_Attributes; }

		void ClearAttributeList() { m_Attributes.clear(); } 

		virtual ~VertexLayout() = default;
	protected:
		std::vector<VertexAttribute> m_Attributes;
	};
}