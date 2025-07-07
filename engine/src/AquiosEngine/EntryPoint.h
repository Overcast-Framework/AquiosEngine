#pragma once
#ifdef AQ_PLATFORM_WINDOWS

extern Aquios::Application* Aquios::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Aquios::CreateApplication();
	app->Run();
	delete app;
}

#endif