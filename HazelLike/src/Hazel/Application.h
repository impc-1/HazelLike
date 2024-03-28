#pragma once
#include "Core.h"
#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"
namespace Hazel {
	class HAZEL_API Application //单例但没有封构造函数
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);
		inline static Application& Get() { return *s_Instance; } // 暴露当前应用对象application
		inline Window& GetWindow() { return *m_Window; } // 暴露内部核心窗口信息（包含glfw上下文）
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance; // 引用不能赋值nullptr
	};
	// 在使用端定义
	Application* CreateApplication();
}

