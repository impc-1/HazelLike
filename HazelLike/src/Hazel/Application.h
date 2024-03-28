#pragma once
#include "Core.h"
#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"
namespace Hazel {
	class HAZEL_API Application //������û�з⹹�캯��
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);
		inline static Application& Get() { return *s_Instance; } // ��¶��ǰӦ�ö���application
		inline Window& GetWindow() { return *m_Window; } // ��¶�ڲ����Ĵ�����Ϣ������glfw�����ģ�
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance; // ���ò��ܸ�ֵnullptr
	};
	// ��ʹ�ö˶���
	Application* CreateApplication();
}

