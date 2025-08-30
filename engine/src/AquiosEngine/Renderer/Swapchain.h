#pragma once
#include <AquiosEngine/Renderer/CommandList.h>
#include <AquiosEngine/IDestructable.h>

namespace Aquios
{
	class Swapchain : public IDestructable
	{
	public:
		Swapchain(size_t width, size_t height) : m_Width(width), m_Height(height) {}

		virtual void Resize(CommandList* list, size_t n_Width, size_t n_Height) = 0;
		virtual void BindBackBuffer(CommandList* list) = 0;
		virtual void Present(CommandList* list) = 0;

		const size_t& GetWidth() { return m_Width; }
		const size_t& GetHeight() { return m_Height; }

		virtual void Release() = 0;
		virtual ~Swapchain() = default;
	private:
		size_t m_Width, m_Height;
	};
}