#pragma once
#include <string>
#include <vector>
#include <AquiosEngine/IDestructable.h>
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

		virtual void Release() = 0;

		std::vector<VertexAttribute>& GetAttributes() { return m_Attributes; }

		void ClearAttributeList() { m_Attributes.clear(); } 

		VertexLayout();
		virtual ~VertexLayout() = default;
	private:
		std::vector<VertexAttribute> m_Attributes;
	};
}