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

		// �ﰢ�� �޽� ��ü
		std::unique_ptr<class TriangleMesh> tMesh;

		// �簢�� �޽� ��ü
		std::unique_ptr<class QuadMesh> qMesh;
	};
}
