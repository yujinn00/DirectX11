#include "Renderer.h"
#include "../Math/Vector3.h"
#include "TriangleMesh.h"
#include "QuadMesh.h"

#include <vector>
#include <d3dcompiler.h>

namespace Blue
{
	Renderer::Renderer(uint32 width, uint32 height, HWND window)
	{
		// ��ġ ������ ����ϴ� �ɼ�
		uint32 flag = 0u;

#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// ������ ���̺귯�� ����
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		// ���� ü�� ���� ����ü
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { };
		swapChainDesc.Windowed = true; // â ���
		swapChainDesc.OutputWindow = window;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1; // �� ���� ����
		swapChainDesc.SampleDesc.Count = 1; // ��Ƽ ���ø� ����
		swapChainDesc.SampleDesc.Quality = 0; // ��Ƽ ���ø� ���� (Quality = Count - 1)
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// ��ġ ����
		HRESULT result = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&swapChain,
			&device,
			nullptr,
			&context
		);

		// ��� Ȯ��
		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create devices", "Error", MB_OK);
		}

		// ���� Ÿ�� �� ����
		ID3D11Texture2D* backbuffer = nullptr;
		//swapChain->GetBuffer(0, __uuidof(backbuffer), reinterpret_cast<void**>(&backbuffer));
		result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));
		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to get back buffer", "Error", MB_OK);
			__debugbreak();
		}

		result = device->CreateRenderTargetView(backbuffer, nullptr, &renderTargetView);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create render target view", "Error", MB_OK);
			__debugbreak();
		}

		// ���� Ÿ�� �� ���ε� (����)
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);

		// ����Ʈ (ȭ��)
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;

		// ����Ʈ ����
		context->RSSetViewports(1, &viewport);
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Draw()
	{
		// �ﰢ�� ���̴� ��ü ����
		if (tMesh == nullptr)
		{
			tMesh = std::make_unique<TriangleMesh>();
		}

		//// �簢�� ���̴� ��ü ����
		//if (qMesh == nullptr)
		//{
		//	qMesh = std::make_unique<QuadMesh>();
		//}

		// 1. ����� (Clear) => BeginScene
		float color[] = { 0.92f, 0.77f, 0.84f, 1.0f };
		context->ClearRenderTargetView(renderTargetView, color);

		// 2. �ﰢ�� ��ο� (Draw)
		tMesh->Draw();

		//// 2. �簢�� ��ο� (Draw)
		//qMesh->Draw();

		// 3. ���� ��ȯ (Swap) => EndScene/Present
		swapChain->Present(1u, 0u);
	}
}
