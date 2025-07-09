#include <AquiosEngine.h>

class ExampleLayer : public Aquios::Layer
{
public:
	ExampleLayer()
		: Aquios::Layer("Example")
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
		PushOverlay(new Aquios::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Aquios::Application* Aquios::CreateApplication()
{
	return new Sandbox();
}