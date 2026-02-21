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

		const Type& GetType() { return TextureType; }
		const Format& GetFormat() { return this->Format; }
		const size_t& GetWidth() { return Width; }
		const size_t& GetHeight() { return Height; }

		Texture(Type type, Format format, size_t width, size_t height)
			: TextureType(type), Format(format), Width(width), Height(height) {
			Init();
		}

		virtual ~Texture() = default;
	protected:
		Type TextureType;
		Format Format;
		size_t Width, Height;
	};
}