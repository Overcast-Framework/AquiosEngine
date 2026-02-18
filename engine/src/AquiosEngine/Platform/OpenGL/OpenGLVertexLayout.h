#pragma once
#include <AquiosEngine/Renderer/VertexLayout.h>
#include <AquiosEngine/Platform/OpenGL/Utils.h>

namespace Aquios::OpenGL
{
	class OpenGLVertexLayout : public VertexLayout
	{
	public:
		void AddAttribute(const VertexAttribute& attrib) override;
		void Build() override;
		void Release() override;

		const GLid& GetId() const { return m_VAOId; }

		void AssignBuffer(GPUBuffer* buf, uint32_t bindingIndex = 0, size_t stride = 0) override;
	private:
		GLid m_VAOId = 0;
	};
}