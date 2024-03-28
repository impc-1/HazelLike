#pragma once

#include "Hazel/Input.h"

namespace Hazel { //��ֱ�ӻ�ȡ������Ϣ �����Ϣ�����������¼���ʽ
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