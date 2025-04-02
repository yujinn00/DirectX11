#pragma once

#include "Core/Type.h"

// DirectX11 ���
#include <d3d11.h>
#include <dxgi.h>
#include <memory>

namespace Blue
{
	// �׷��� ī�忡�� ó���ϴ� ��/���ҽ��� �����ϴ� Ŭ����
	// RHI - Render Hardware Interface
	class Renderer
	{
		// ���� Ŭ���� friend ����
		// �� �翬������ friend ���� ���� �� ���Ͱ� �����
		friend class Engine;

	public:
		Renderer(uint32 width, uint32 height, HWND window);
		~Renderer();

		// �׸��� �Լ�
		void Draw(std::shared_ptr<class Level> level);

	private:
		// ���ҽ�
		// ��ġ��
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* context = nullptr;
		IDXGISwapChain* swapChain = nullptr; // ����� �� ���۸� �����ϴ� ü��

		// ����
		ID3D11RenderTargetView* renderTargetView = nullptr;
		
		// ����Ʈ
		D3D11_VIEWPORT viewport;
	};
}
