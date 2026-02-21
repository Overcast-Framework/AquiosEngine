#include <aqpch.h>
#include <AquiosEngine.h>
#include <fstream>
#include <filesystem>
#include <imgui.h>

class ExampleLayer : public Aquios::Layer
{
public:
	ExampleLayer()
		: Aquios::Layer("Example")
	{
	}

	virtual void OnRender(Aquios::Renderer& renderer) override
	{
		Aquios::Application& app = Aquios::Application::Get();
		auto& window = app.GetActiveWindow();

		auto renderer2D = renderer.GetRenderer2D();

		renderer2D->DrawQuad({ 1,0,0,1 }, { 0,0,0 }, { 100,100,0 }, rotation);
		renderer2D->SubmitBatch();
	}

	virtual void OnImGuiRender() override
	{
		Aquios::Application& app = Aquios::Application::Get();
		auto renderer = app.GetActiveWindow().GetRenderer();

		ImGui::Begin("Stats");

		ImGui::Text("Quad Count: %d", renderer->Stats.QuadCount);
		ImGui::Text("Mesh Count: %d", renderer->Stats.MeshCount);
		ImGui::Text("Draw Calls: %d", renderer->Stats.DrawCalls);
		ImGui::Text("Frame Time: %0.3fms", renderer->GetDeltaTime());
		ImGui::Text("FPS: %d", renderer->GetFPS());

		ImGui::SliderInt("Grid Size", &gridSize, 1, 100);
		ImGui::SliderFloat("Rotation Speed", &rotationSpeed, 0, 360);
		ImGui::End();
	}

	virtual void OnAttach() override
	{
		Aquios::Application& app = Aquios::Application::Get();
		auto& window = app.GetActiveWindow();
		auto renderer = app.GetActiveWindow().GetRenderer();
		renderer->CreateDefaultMats();

		renderer->SetCamera(new Aquios::OrthographicCamera({ 0,0,1 }, { 0,1,0 }, { window.GetWidth(), window.GetHeight() }));
	}

	virtual void OnDetach() override 
	{
	}

	void OnUpdate() override
	{
		Aquios::Application& app = Aquios::Application::Get();
		auto renderer = app.GetActiveWindow().GetRenderer();
		rotation += rotationSpeed * renderer->GetDeltaTime();
	}

	void OnEvent(std::shared_ptr<Aquios::Event>& e) override
	{
		if (e->GetName() == "KeyPressedEvent")
		{
			Aquios::Application& app = Aquios::Application::Get();
			auto renderer = app.GetActiveWindow().GetRenderer();
			auto camera = renderer->GetCamera();

			auto* keyEvent = dynamic_cast<Aquios::KeyPressedEvent*>(e.get());
			auto key = keyEvent->GetKeycode();
			if (key == AQ_KEY_W)
			{
				camera->Position += glm::vec3{0, 1, 0} * 600.0f * renderer->GetDeltaTime();
			}
			else if (key == AQ_KEY_S)
			{
				camera->Position += glm::vec3{ 0, -1, 0 } * 600.0f * renderer->GetDeltaTime();
			}
			else if (key == AQ_KEY_A)
			{
				camera->Position += glm::vec3{ -1, 0, 0 } * 600.0f * renderer->GetDeltaTime();
			}
			else if (key == AQ_KEY_D)
			{
				camera->Position += glm::vec3{ 1, 0, 0 } * 600.0f * renderer->GetDeltaTime();
			}
		}
	}

private:
	float baseColor[4] = { 1,1,1,1 };
	int gridSize = 2;
	float rotation = 0;
	float rotationSpeed = 0;
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