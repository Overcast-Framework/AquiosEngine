#pragma once
#ifdef AQ_PLATFORM_WINDOWS

extern Aquios::Application* Aquios::CreateApplication();

int main(int argc, char** argv)
{
	Aquios::Log::Init();
	AQ_CORE_WARN("Initialized log");
	int a = 5;
	AQ_INFO("Hellooo Var={0}", a);
	auto app = Aquios::CreateApplication();
	app->Run();
	delete app;
}

#endif