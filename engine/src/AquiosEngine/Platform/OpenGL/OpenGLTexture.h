#pragma once
#include <glad/glad.h>
#include <AquiosEngine/Renderer/Texture.h>

namespace Aquios::OpenGL
{
	struct OpenGLInternalTexHandle : public InternalTextureHandle
	{
		GLuint Id;

		OpenGLInternalTexHandle(const GLuint& Id)
			: Id(Id)
		{
		}
	};

	class OpenGLTexture : public Texture
	{
	public:
		void SetData(void* data, size_t size, int mipLevel) override;
		void Bind(CommandList* list, int slot) override;

		InternalTextureHandle* GetInternalHandle() override;

		void Init() override;
		void Release() override;

		void MakeResident();

		OpenGLTexture(Type type, Format format, size_t width, size_t height)
			: Texture(type, format, width, height)  {
			Init();
		}

		const GLuint& GetTextureId() const { return m_TextureId; }
		const GLuint64& GetTextureHandle() const { return m_TextureHandle; }
	private:
		GLuint m_TextureId = 0;
		GLuint64 m_TextureHandle = 0;

		std::vector<uint8_t> m_CopiedData;
	};
}