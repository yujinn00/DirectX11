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
		// 장치 생성에 사용하는 옵션
		uint32 flag = 0u;

#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// 생성할 라이브러리 버전
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		// 스왑 체인 정보 구조체
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { };
		swapChainDesc.Windowed = true; // 창 모드
		swapChainDesc.OutputWindow = window;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1; // 백 버퍼 개수
		swapChainDesc.SampleDesc.Count = 1; // 멀티 샘플링 개수
		swapChainDesc.SampleDesc.Quality = 0; // 멀티 샘플링 수준 (Quality = Count - 1)
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// 장치 생성
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

		// 결과 확인
		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create devices", "Error", MB_OK);
		}

		// 렌더 타겟 뷰 생성
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

		// 렌더 타겟 뷰 바인딩 (연결)
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);

		// 뷰포트 (화면)
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;

		// 뷰포트 설정
		context->RSSetViewports(1, &viewport);
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Draw()
	{
		// 삼각형 쉐이더 객체 생성
		if (tMesh == nullptr)
		{
			tMesh = std::make_unique<TriangleMesh>();
		}

		//// 사각형 쉐이더 객체 생성
		//if (qMesh == nullptr)
		//{
		//	qMesh = std::make_unique<QuadMesh>();
		//}

		// 1. 지우기 (Clear) => BeginScene
		float color[] = { 0.92f, 0.77f, 0.84f, 1.0f };
		context->ClearRenderTargetView(renderTargetView, color);

		// 2. 삼각형 드로우 (Draw)
		tMesh->Draw();

		//// 2. 사각형 드로우 (Draw)
		//qMesh->Draw();

		// 3. 버퍼 교환 (Swap) => EndScene/Present
		swapChain->Present(1u, 0u);
	}
}
