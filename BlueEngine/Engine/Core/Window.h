#pragma once

#include "Type.h"

#include <Windows.h>
#include <string>

namespace Blue
{
	// 윈도우 클래스
	class Window
	{
	public:
		Window(uint32 width, uint32 height, const std::wstring& title, HINSTANCE instance, WNDPROC messageProcedure);
		~Window();

		// Getter
		inline const uint32 Width() const { return width; }
		inline const uint32 Height() const { return height; }
		inline HWND Handle() const { return handle; }

		// Setter
		void SetWidthHeight(uint32 width, uint32 height);

	private:
		uint32 width = 0;
		uint32 height = 0;
		std::wstring title = nullptr;
		std::wstring className = TEXT("Engine Class");
		HWND handle = nullptr;
		HINSTANCE instance = nullptr;
	};
}
