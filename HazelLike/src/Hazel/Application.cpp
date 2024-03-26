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
	void Application::PushLayer(Layer* layer) // 应用层面加入一个Layer
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverLay(Layer* layer)
	{
		m_LayerStack.PushOverLayer(layer);
	}

	void Application::OnEvent(Event& e) { // 这是应用处理点击事件等的逻辑函数，作为回调函数入口。
		EventDispatcher dispatcher(e);  //这个事件由glfw调用回调传入 对应注册event
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));// 现在仅仅特殊处理关闭页面

		//HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e); // 先-- ，end()不可解引用
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

			m_Window->OnUpdate(); // glfw循环 查询是否触发事件并触发绑定事件
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}