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

		const GLuint& GetTextureId() const { return m_TextureId; }
	private:
		GLuint m_TextureId = 0;
	};
}