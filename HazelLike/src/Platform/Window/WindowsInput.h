#pragma once

#include "Hazel/Input.h"

namespace Hazel { //想直接获取键盘信息 鼠标信息，而不是以事件形式
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int keycode) override;
		virtual std::pair<float,float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	
	};
}