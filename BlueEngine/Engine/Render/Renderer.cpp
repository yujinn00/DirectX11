#include "Renderer.h"
#include "Math/Vector3.h"
#include "TriangleMesh.h"
#include "QuadMesh.h"
#include "Core/Common.h"
#include "Level/Level.h"

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

		// 장치 생성.
		ThrowIfFailed(D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			&device,
			nullptr,
			&context
		), TEXT("Failed to create devices."));

		// IDXGIFactory 리소스 생성.
		IDXGIFactory* factory = nullptr;
		//CreateDXGIFactory(__uuidof(factory), reinterpret_cast<void**>(&factory));
		ThrowIfFailed(CreateDXGIFactory(
			IID_PPV_ARGS(&factory)
		), TEXT("Failed to create dxgifactory."));

		// 스왑 체인 정보 구조체
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { };
		swapChainDesc.Windowed = true; // 창 모드
		swapChainDesc.OutputWindow = window;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2; // 백 버퍼 개수
		swapChainDesc.SampleDesc.Count = 1; // 멀티 샘플링 개수
		swapChainDesc.SampleDesc.Quality = 0; // 멀티 샘플링 수준 (Quality = Count - 1)
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		//// 장치 생성
		//ThrowIfFailed(D3D11CreateDeviceAndSwapChain(
		//	nullptr,
		//	D3D_DRIVER_TYPE_HARDWARE,
		//	nullptr,
		//	flag,
		//	featureLevels,
		//	_countof(featureLevels),
		//	D3D11_SDK_VERSION,
		//	&swapChainDesc,
		//	&swapChain,
		//	&device,
		//	nullptr,
		//	&context
		//), TEXT("Failed to create devices"));

		// SwapChain 생성.
		ThrowIfFailed(factory->CreateSwapChain(
			device,
			&swapChainDesc,
			&swapChain
		), TEXT("Failed to create a swap chain."));

		// 렌더 타겟 뷰 생성
		ID3D11Texture2D* backbuffer = nullptr;
		//swapChain->GetBuffer(0, __uuidof(backbuffer), reinterpret_cast<void**>(&backbuffer));

		ThrowIfFailed(swapChain->GetBuffer(
			0, IID_PPV_ARGS(&backbuffer)
		), TEXT("Failed to get back buffer"));

		ThrowIfFailed(device->CreateRenderTargetView(
			backbuffer, nullptr, &renderTargetView
		), TEXT("Failed to create render target view."));

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

	void Renderer::Draw(std::shared_ptr<Level> level)
	{
		// 삼사각형 쉐이더 객체 생성
		if (mesh1 == nullptr)
		{
			mesh1 = std::make_unique<QuadMesh>();
			mesh1->transform.scale = Vector3::One * 0.5f;
			mesh1->transform.position.x = 0.5f;
		}
		if (mesh2 == nullptr)
		{
			mesh2 = std::make_unique<QuadMesh>();
			mesh2->transform.scale = Vector3::One * 0.5f;
			mesh2->transform.position.x = -0.5f;
		}
		//if (mesh3 == nullptr)
		//{
		//	mesh3 = std::make_unique<TriangleMesh>();
		//	mesh3->transform.scale = Vector3::One * 0.5f;
		//	mesh3->transform.position.y = 0.5f;
		//}

		// 0. 그리기 전 작업 (BeginScene).
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);

		// 1. 지우기 (Clear) => BeginScene
		float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		context->ClearRenderTargetView(renderTargetView, color);

		// @Test.
		mesh1->Update(1.0f / 60.0f);
		mesh2->Update(1.0f / 60.0f);

		//// 2. 삼사각형 드로우 (Draw)
		mesh1->Draw();
		mesh2->Draw();
		//mesh3->Draw();

		// 3. 버퍼 교환 (Swap) => EndScene/Present
		swapChain->Present(1u, 0u);
	}
}
