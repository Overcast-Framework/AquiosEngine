#include <AquiosEngine.h>

class Sandbox : public Aquios::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Aquios::Application* Aquios::CreateApplication()
{
	return new Sandbox();
}