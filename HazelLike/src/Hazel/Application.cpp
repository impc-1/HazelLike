#include "hzpch.h"
#include "Application.h"
#include "Hazel/Log.h"
#include "glad/glad.h"
#include "Input.h"
namespace Hazel {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	void Application::PushLayer(Layer* layer) // Ӧ�ò������һ��Layer
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer* layer)
	{
		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e) { // ������¼���handled��Ȼ�� falseδ���������Ѿ���ע�ᵽ�����¼��У���Ϊ�ص�������ڡ�
		EventDispatcher dispatcher(e);  //����¼���glfw���ûص����� ��Ӧע��event
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));// ���ڽ������⴦��ر�ҳ��

		//HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) //�㼶�����¼� ÿ���㼶ȥѭ�����ܴ����¼��ġ�
		{
			(*--it)->OnEvent(e); // ��-- ��end()���ɽ�����
			if (e.Handled) //�¼���������
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
				layer->OnUpdate();//���ڻ��������ʲô�ã����ǲ㼶��Ⱦ����ѭ���б���Ϊһֱ������û���жϼ���
			
			m_Window->OnUpdate(); //m_window �Ǵ��壬�����������ģ��¼����
								  //glfwѭ�� ��ѯ�Ƿ񴥷��¼����������¼� -�����ûص� -��application::onEvent()
								  //���崦���¼� ÿ���㼶��ȥ����,ÿ���㼶��EVENT
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) // ����ر��¼�
	{
		m_Running = false;
		return true;
	}
}