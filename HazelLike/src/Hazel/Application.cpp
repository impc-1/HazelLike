#include "hzpch.h"
#include "Application.h"
#include "Hazel/Log.h"
#include "glad/glad.h"
namespace Hazel {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	void Application::PushLayer(Layer* layer) // Ӧ�ò������һ��Layer
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverLay(Layer* layer)
	{
		m_LayerStack.PushOverLayer(layer);
	}

	void Application::OnEvent(Event& e) { // ����Ӧ�ô������¼��ȵ��߼���������Ϊ�ص�������ڡ�
		EventDispatcher dispatcher(e);  //����¼���glfw���ûص����� ��Ӧע��event
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));// ���ڽ������⴦��ر�ҳ��

		//HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e); // ��-- ��end()���ɽ�����
			if (e.Handled)
				break;
		}
	}

	Application::~Application()
	{
	}
	
	void Application::Run()
	{

		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate(); // glfwѭ�� ��ѯ�Ƿ񴥷��¼����������¼�
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}