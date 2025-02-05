#include "Window.h"

namespace Blue
{
	Window::Window(uint32 width, uint32 height, const std::wstring& title, HINSTANCE instance, WNDPROC messageProcedure)
		: width(width), height(height), title(title), instance(instance)
	{
		// â ������ �ʿ��� ���� ����ü
		WNDCLASS wc = { };

		// �޼��� ó���� ���� �ݹ� ����
		wc.lpfnWndProc = messageProcedure;

		// ���α׷� �ּ� ����
		wc.hInstance = instance;

		// â ������ ����� Ŭ���� �̸� ����
		wc.lpszClassName = className.c_str();

		// Ŭ���� ���
		if (!RegisterClass(&wc))
		{
			// �޼��� ��� #1: ���â �̿�
			OutputDebugStringA("Failed to register a window class\n");

			// �޼��� ��� #2: �޼��� �ڽ� �̿�
			MessageBoxA(nullptr, "Failed to register a window", "Error", MB_OK);

			__debugbreak();
		}

		// â�� ��ġ ����
		unsigned int positionX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		unsigned int positionY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

		// â ũ�� ����
		RECT rect = { 0, 0, (long)width, (long)height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		// â ũ�� �缳��
		unsigned int windowWidth = rect.right - rect.left;
		unsigned int windowHeight = rect.bottom - rect.top;

		// ����
		handle = CreateWindow(
			className.c_str(),			// Window class
			title.c_str(),				// Window text
			WS_OVERLAPPEDWINDOW,		// Window style
			// Size and position
			positionX, positionY,
			windowWidth, windowHeight,
			nullptr,					// Parent window
			nullptr,					// Menu
			instance,					// Instance handle
			nullptr						// Additional application data
		);

		// ���� �� ���� �޼��� ���
		if (handle == nullptr)
		{
			// �޼��� ��� #1: ���â �̿�
			OutputDebugStringA("Failed to create a window class\n");

			// �޼��� ��� #2: �޼��� �ڽ� �̿�
			MessageBoxA(nullptr, "Failed to create a window", "Error", MB_OK);

			__debugbreak();
		}

		// â ���̱�
		ShowWindow(handle, SW_SHOW);

		// â �޼��� ������Ʈ
		UpdateWindow(handle);
	}

	Window::~Window()
	{
		// Ŭ���� ��� ����
		UnregisterClass(className.c_str(), instance);
	}

	void Window::SetWidthHeight(uint32 width, uint32 height)
	{
		this->width = width;
		this->height = height;
	}
}
