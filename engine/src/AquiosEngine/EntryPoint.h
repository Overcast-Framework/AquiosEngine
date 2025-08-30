#pragma once
#ifdef AQ_PLATFORM_WINDOWS

extern Aquios::Application* Aquios::CreateApplication();

int main(int argc, char** argv)
{
	Aquios::Log::Init();
	AQ_CORE_WARN("Initialized log");
	auto app = Aquios::CreateApplication();
	app->Run();
	delete app;
}

#endif