#pragma once
#include <AquiosEngine/IDestructable.h>
#include <AquiosEngine/Renderer/Format.h>
#include <AquiosEngine/Renderer/CommandList.h>
#include <vector>

namespace Aquios
{
	struct InternalTextureHandle // you're gonna have to cast this into the platform specific kind, so you can get the actual type instead of a void*
	{
		virtual ~InternalTextureHandle() = default;
	};

	class Texture : public IDestructable
	{
	public:
		enum class Type { Texture2D, Cubemap, Texture3D };

		virtual void SetData(void* data, size_t size, int mipLevel = 0) = 0;
		virtual void Bind(CommandList* list, int slot) = 0;
		virtual InternalTextureHandle* GetInternalHandle() = 0;

		virtual void Init() = 0;

		virtual void Release() = 0;

		const Type& GetType() { return m_TextureType; }
		const Format& GetFormat() { return m_Format; }
		const size_t& GetWidth() { return m_Width; }
		const size_t& GetHeight() { return m_Height; }
		const size_t& GetSize() { return m_TextureSize; }

		Texture(Type type, Format format, size_t width, size_t height)
			: m_TextureType(type), m_Format(format), m_Width(width), m_Height(height) {
		}

		virtual ~Texture() = default;
	protected:
		Type m_TextureType;
		Format m_Format;
		size_t m_Width, m_Height;
		size_t m_TextureSize;
	};
}