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

		float quadSize = 25.0f;
		float spacing = 2.0f;
		float windowCenterX = window.GetWidth() / 2.0f;
		float windowCenterY = window.GetHeight() / 2.0f;
		float totalWidth = gridSize * quadSize + (gridSize - 1) * spacing;
		float totalHeight = gridSize * quadSize + (gridSize - 1) * spacing;
		float halfWidth = totalWidth / 2.0f;
		float halfHeight = totalHeight / 2.0f;

		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				float x = i * (quadSize + spacing) - totalWidth / 2.0f + quadSize / 2.0f + windowCenterX;
				float y = j * (quadSize + spacing) - totalHeight / 2.0f + quadSize / 2.0f + windowCenterY;
				renderer.DrawQuad({ 1,0,0,1 }, { x, y+(200*sin((renderer.GetFrameCount()/10)+ 0.5 * x - 1.2 * y)*renderer.GetDeltaTime()), 0}, {quadSize, quadSize, 1}, rotation);
			}
		}
		renderer.FlushQuadBatch();
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
		auto renderer = app.GetActiveWindow().GetRenderer();
		renderer->CreateDefaultMats();
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
		//AQ_TRACE(e->ToString());
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