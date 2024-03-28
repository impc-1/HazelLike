#pragma once

#include "Hazel/Window.h"

struct GLFWwindow; //extern reference
namespace Hazel {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }


		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; } 
		// ����ͳ�ʼ���� m_Data�е��¼��ص��ĺ����塣
		// ��������ΪOnEvent�� ִ�в���Ϊ��һ����

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window; //window ����ʹ�õ� glfw�����Ķ���

		struct WindowData //window �������ݼ�
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};
}