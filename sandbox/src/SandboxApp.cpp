#include <aqpch.h>
#include <AquiosEngine.h>
#include <imgui.h>

class ExampleLayer : public Aquios::Layer
{
public:
	ExampleLayer()
		: Aquios::Layer("Example")
	{
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Heyu");
		ImGui::Text("helo");
		ImGui::End();
	}

	virtual void OnAttach() override
	{
	}

	void OnUpdate() override
	{
		//AQ_INFO("Updated example layer");
	}

	void OnEvent(std::shared_ptr<Aquios::Event>& e) override
	{
		//AQ_TRACE(e->ToString());
	}
};

class Sandbox : public Aquios::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Aquios::Application* Aquios::CreateApplication()
{
	return new Sandbox();
}