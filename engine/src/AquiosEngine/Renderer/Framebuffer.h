#pragma once
#include <AquiosEngine/IDestructable.h>
#include <AquiosEngine/Renderer/Texture.h>
#include <AquiosEngine/Renderer/CommandList.h>
#include <vector>

namespace Aquios
{
	class Framebuffer : public IDestructable
	{
	public:
		enum class Type { Draw, Read };
		
		virtual void ChangeType(Type newType) = 0;
		virtual Texture* GetPresentableImage() = 0;
		virtual void Bind(CommandList* cmdList) = 0;

		const Type& GetType() { return FramebufferType; }
		const std::vector<Texture*>& GetColorAttachments() const { return ColorAttachments; }
		const Texture* GetDSAttachment() const { return DepthStencilAttachment; }

		Framebuffer(Type type, const std::vector<Texture*>& colorAttachments, Texture* depthStencil)
			: FramebufferType(type), ColorAttachments(colorAttachments), DepthStencilAttachment(depthStencil) {
		}

		virtual void Release() = 0;
		virtual ~Framebuffer() = 0;
	private:
		Type FramebufferType;
		std::vector<Texture*> ColorAttachments;
		Texture* DepthStencilAttachment;
	};
}