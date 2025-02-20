#include "Engine.h"
#include "Window.h"
#include "Render/Renderer.h"

namespace Blue
{
	// �̱��� ��ü ����
	Engine* Engine::instance = nullptr;

	Engine::Engine(uint32 width, uint32 height, const std::wstring& title, HINSTANCE hInstance)
	{
		// �̱��� ��ü �� ����
		instance = this;

		// â ��ü ����
		window = std::make_shared<Window>(
			width, height, title, hInstance, WindowProc
		);

		// ������ ����
		renderer = std::make_shared<Renderer>(
			width, height, window->Handle()
		);
	}

	Engine::~Engine()
	{
	}

	void Engine::Run()
	{
		// �޼��� ó�� ����
		MSG msg = { };
		//while (msg.message != WM_DESTROY)
		while (msg.message != WM_QUIT)
		{
			// â�� �޼����� ���� �� ����
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				// �޼��� ����
				TranslateMessage(&msg);

				// �޼��� ����
				DispatchMessage(&msg);
			}
			// â�� �޼����� ���� �� �ٸ� �۾� ó��
			else
			{
				// ���� ����
				renderer->Draw();
			}
		}
	}

	LRESULT Engine::WindowProc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		// �޼��� ó��
		switch (message)
		{
			// â�� �����Ǹ� �����
		case WM_DESTROY:
			// ���α׷� ���� �޼��� ����
			PostQuitMessage(0);
			return 0;
		}

		// �⺻ �޼��� ó��
		return DefWindowProc(handle, message, wparam, lparam);
	}

	Engine& Engine::Get()
	{
		return *instance;
	}

	ID3D11Device& Engine::Device() const
	{
		return *renderer->device;
	}

	ID3D11DeviceContext& Engine::Context() const
	{
		return *renderer->context;
	}
}
