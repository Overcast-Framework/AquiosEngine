#include "aqpch.h"
#include "Material.h"
#include <AquiosEngine/Application.h>

void Aquios::Material::SetTextureInSlot(uint32_t slot, Texture* texture)
{
    m_Textures[slot] = texture;
}

void Aquios::Material::SetBaseColor(glm::vec4 color)
{
    this->m_UBStruct->m_BaseColor = color;
    this->MarkDirty();
}

void Aquios::Material::SetRoughness(float roughness)
{
    this->m_UBStruct->m_Roughness = roughness;
    this->MarkDirty();
}

void Aquios::Material::Use(CommandList* list)
{
    AQ_CORE_ASSERT(this->m_UBStruct != nullptr, "No material struct specified. You must call SetUBStruct on a material to set a material struct.");

    for (uint32_t i = 0; i < 16; ++i)
        if (m_Textures[i]) m_Textures[i]->Bind(list, i);

    this->m_Pipeline->Bind(list);
    this->m_MaterialUB->BindBase(list);
}

void Aquios::Material::Update()
{
    if (m_UBStruct && m_IsUBStructDirty)
    {
        auto renderer = Aquios::Application::Get().GetActiveWindow().GetRenderer();
        this->m_MaterialUB->UploadData(this->m_UBStruct, this->m_UBStructSize);
        m_IsUBStructDirty = false;
    }
}

void Aquios::Material::SetUBStruct(MaterialUB* ubStruct, size_t structSize)
{
    this->m_UBStruct = ubStruct;
    if (structSize != m_UBStructSize)
    {
        if (m_MaterialUB)
            m_MaterialUB->Free();

        auto renderer = Aquios::Application::Get().GetActiveWindow().GetRenderer();
        this->m_MaterialUB = renderer->CreateGPUBuffer(GPUBuffer::Type::StorageBlock, structSize);
        m_UBStructSize = structSize;
    }
    this->MarkDirty();
}

Aquios::MaterialUB* Aquios::Material::GetUBStruct()
{
    return this->m_UBStruct;
}

void Aquios::Material::MarkDirty()
{
    this->m_IsUBStructDirty = true;
}

void Aquios::Material::Release()
{
    this->m_MaterialUB->Free();
    this->m_Pipeline->Release();
    delete this->m_UBStruct;
}

void Aquios::Material::Initialize()
{
    
}
