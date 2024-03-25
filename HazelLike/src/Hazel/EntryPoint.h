#pragma once

#ifdef HZ_PLATFORM_WINDOWS

//extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Error!");
	int a = 111;
	HZ_ERROR("Hello!,{0}",a);
	HZ_CORE_ERROR("ERROR!,{0}", "1111111");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif