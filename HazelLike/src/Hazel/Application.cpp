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
	void Application::PushLayer(Layer* layer) // 应用层面加入一个Layer
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer* layer)
	{
		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e) { // 传入的事件的handled必然是 false未处理，函数已经被注册到窗体事件中，作为回调函数入口。
		EventDispatcher dispatcher(e);  //这个事件由glfw调用回调传入 对应注册event
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));// 现在仅仅特殊处理关闭页面

		//HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) //层级处理事件 每个层级去循环找能处理事件的。
		{
			(*--it)->OnEvent(e); // 先-- ，end()不可解引用
			if (e.Handled) //事件被处理了
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
				layer->OnUpdate();//现在还不清楚有什么用，像是层级渲染，在循环中表现为一直在运行没有中断迹象
			
			m_Window->OnUpdate(); //m_window 是窗体，有整个上下文，事件起点
								  //glfw循环 查询是否触发事件并触发绑定事件 -》内置回调 -》application::onEvent()
								  //集体处理事件 每个层级都去处理,每个层级的EVENT
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) // 处理关闭事件
	{
		m_Running = false;
		return true;
	}
}