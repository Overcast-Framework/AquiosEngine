#include "aqpch.h"
#include "OpenGLTexture.h"
#include "Utils.h"

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
    auto format = format_to_gl(this->Format);
    switch (this->TextureType)
    {
    case Texture::Type::Texture2D:
    {
        glBindTexture(GL_TEXTURE_2D, this->m_TextureId);
        glTexImage2D(GL_TEXTURE_2D, mipLevel, format, this->Width, this->Height, 0, format, GL_UNSIGNED_BYTE, data);
        break;
    }
    case Texture::Type::Texture3D:
    {
        glBindTexture(GL_TEXTURE_3D, this->m_TextureId);
        glTexImage3D(GL_TEXTURE_3D, mipLevel, format, this->Width, this->Height, 0, 0, format, GL_UNSIGNED_BYTE, data);
        break;
    }
    case Texture::Type::Cubemap:
    {
        // fuck these for now
        break;
    }
    }
}

void Aquios::OpenGL::OpenGLTexture::Bind(CommandList* list, int slot)
{
    GLuint texId = this->m_TextureId;
    list->Record<Commands::LambdaCmd>(Commands::LambdaCmd([=]() {
        glActiveTexture(GL_TEXTURE0 + slot);
        switch (this->TextureType)
        {
        case Texture::Type::Texture2D:
        {
            glBindTexture(GL_TEXTURE_2D, this->m_TextureId);
            break;
        }
        case Texture::Type::Texture3D:
        {
            glBindTexture(GL_TEXTURE_3D, this->m_TextureId);
            break;
        }
        case Texture::Type::Cubemap:
        {
            glBindTexture(GL_TEXTURE_CUBE_MAP, texId);
            break;
        }
        }
        }
    ));
}

Aquios::InternalTextureHandle* Aquios::OpenGL::OpenGLTexture::GetInternalHandle()
{
    return new OpenGLInternalTexHandle(this->m_TextureId);
}

void Aquios::OpenGL::OpenGLTexture::Release()
{
    glDeleteTextures(1, &m_TextureId);
}

void Aquios::OpenGL::OpenGLTexture::Init()
{
    glCreateTextures(textype_to_gl(this->TextureType), 1, &m_TextureId);
    auto format = format_to_gl(this->Format);
    switch (this->TextureType)
    {
    case Texture::Type::Texture2D:
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, this->Width, this->Height, 0, format, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        break;
    }
    case Texture::Type::Texture3D:
    {
        glTexImage3D(GL_TEXTURE_3D, 0, format, this->Width, this->Height, 0, 0, format, GL_UNSIGNED_BYTE, nullptr);
        break;
    }
    case Texture::Type::Cubemap:
    {
        // fuck these for now
        break;
    }
    }
}
