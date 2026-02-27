#include "aqpch.h"
#include "OpenGLTexture.h"
#include "Utils.h"
#include <AquiosEngine/Application.h>

GLint textype_to_gl(Aquios::Texture::Type type)
{
    switch (type)
    {
    case Aquios::Texture::Type::Texture2D:
        return GL_TEXTURE_2D;
    case Aquios::Texture::Type::Texture3D:
        return GL_TEXTURE_3D;
    case Aquios::Texture::Type::Cubemap:
        return GL_TEXTURE_CUBE_MAP;
    }

    AQ_CORE_ASSERT(false, "Unknown texture type");
    return 0;
}

void Aquios::OpenGL::OpenGLTexture::SetData(void* data, size_t size, int mipLevel)
{
    auto format = format_to_gli(m_Format);

    GLint width = 0;
    glGetTextureLevelParameteriv(m_TextureId, 0, GL_TEXTURE_WIDTH, &width);
    AQ_CORE_ASSERT(width != 0, "Texture storage not allocated before SetData");

    switch (m_TextureType)
    {
    case Texture::Type::Texture2D:
    {
        glTextureSubImage2D(m_TextureId, mipLevel, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);
        
        break;
    }
    case Texture::Type::Texture3D:
    {

        break;
    }
    case Texture::Type::Cubemap:
    {
        // fuck these for now
        break;
    }
    }

    m_TextureSize = size;
}

void Aquios::OpenGL::OpenGLTexture::Bind(CommandList* list, int slot)
{

}

Aquios::InternalTextureHandle* Aquios::OpenGL::OpenGLTexture::GetInternalHandle()
{
    return new OpenGLInternalTexHandle(this->m_TextureId);
}

void Aquios::OpenGL::OpenGLTexture::Release()
{
    auto renderer = Aquios::Application::Get().GetWindow().GetRenderer();
    renderer->Stats.TotalTexMem -= m_TextureSize;

    glMakeTextureHandleNonResidentARB(m_TextureHandle);
    glDeleteTextures(1, &m_TextureId);
}

void Aquios::OpenGL::OpenGLTexture::MakeResident()
{
    m_TextureHandle = glGetTextureHandleARB(m_TextureId);
    glMakeTextureHandleResidentARB(m_TextureHandle);
}

void Aquios::OpenGL::OpenGLTexture::Init()
{
    glCreateTextures(textype_to_gl(m_TextureType), 1, &m_TextureId);
    auto format = format_to_gl(m_Format);

    switch (m_TextureType)
    {
    case Texture::Type::Texture2D:
    {
        glTextureStorage2D(m_TextureId, 1, format, m_Width, m_Height);
        //std::vector<uint8_t> dummy(m_Width * m_Height * 4, 255);
        //glClearTexImage(m_TextureId, 0, GL_RGBA, GL_UNSIGNED_BYTE, dummy.data());
        glTextureParameteri(m_TextureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_TextureId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        break;
    }
    case Texture::Type::Texture3D:
    {

        break;
    }
    case Texture::Type::Cubemap:
    {
        // fuck these for now
        break;
    }
    }
}
