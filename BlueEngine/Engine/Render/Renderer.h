#pragma once

#include "../Core/Type.h"

// DirectX11 ���
#include <d3d11.h>
#include <dxgi.h>

namespace Blue
{
	// �׷��� ī�忡�� ó���ϴ� ��/���ҽ��� �����ϴ� Ŭ����
	// RHI - Render Hardware Interface
	class Renderer
	{
	public:
		Renderer(uint32 width, uint32 height, HWND window);
		~Renderer();

		// �׸��� �Լ�
		void Draw();

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

		// @Temp: �ӽ�
		// ���� ���� (���� ������ �����ϴ� �� ���)
		ID3D11Buffer* vertexBuffer = nullptr;

		// �ε��� ���� (������ ������ �� ������ ������ ����)
		ID3D11Buffer* indexBuffer = nullptr;

		// �Է� ���̾ƿ�
		ID3D11InputLayout* inputLayout = nullptr;

		// ���̴� ��ü
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;
	};
}
