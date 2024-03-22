#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Error!");
	int a = 111;
	HZ_ERROR("Hello!,{0}",a);

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif