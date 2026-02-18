#include "aqpch.h"
#include "Renderer.h"
#include <AquiosEngine/Window.h>

void Aquios::Renderer::CreateDefaultMats()
{
	if (!m_DefaultMats.Initialized)
	{
		std::ifstream basic_vifs("engine/assets/shaders/glsl/basic_vs.glsl");
		std::string basic_vsContent((std::istreambuf_iterator<char>(basic_vifs)),
			(std::istreambuf_iterator<char>()));
		std::ifstream basic_fifs("engine/assets/shaders/glsl/basic_fs.glsl");
		std::string basic_fsContent((std::istreambuf_iterator<char>(basic_fifs)),
			(std::istreambuf_iterator<char>()));

		if (!basic_vifs)
			AQ_CORE_ERROR("Couldn't read from basic_vs.glsl");
		if (!basic_fifs)
			AQ_CORE_ERROR("Couldn't read from basic_fs.glsl");

		auto* vsShader = this->CreateShader(Aquios::ShaderType::Vertex, basic_vsContent);
		auto* fsShader = this->CreateShader(Aquios::ShaderType::Fragment, basic_fsContent);

		auto* pipelineSpec = new Aquios::GraphicsPipelineSpec();
		pipelineSpec->VertexShader = vsShader;
		pipelineSpec->FragmentShader = fsShader;
		pipelineSpec->VertexLayout = this->GetDefaultVertexLayout();

		auto* pipeline = this->CreatePipeline(pipelineSpec);
		m_DefaultMats.Basic = new Aquios::Material(std::move(pipeline));
		auto* matUB = new Aquios::MaterialUB();
		matUB->m_BaseColor = glm::vec4(1, 1, 1, 1);
		matUB->m_Roughness = 0;

		m_DefaultMats.Basic->SetUBStruct(matUB, sizeof(Aquios::MaterialUB));

		m_DefaultMats.Initialized = true;
	}
}
