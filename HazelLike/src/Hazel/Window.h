#pragma once
#include "hzpch.h"
#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

	struct WindowProps //窗体数据集 --长宽标题
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hazel Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};
	
	class HAZEL_API Window  //窗体 事件
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>; // 包装一个 参数为自定义事件对象引用 返回值为void 的函数包装器

		virtual ~Window() {}

		virtual void OnUpdate() = 0;                          //窗体更新
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// window attributes

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;         //设置事件回调

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());        //创建窗体函数，
	};
}