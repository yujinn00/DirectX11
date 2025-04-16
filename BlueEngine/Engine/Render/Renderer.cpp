#include "Renderer.h"
#include "Math/Vector3.h"
#include "TriangleMesh.h"
#include "QuadMesh.h"
#include "Core/Common.h"

#include "Level/Level.h"
#include "Actor/Actor.h"

#include <vector>
#include <d3dcompiler.h>

namespace Blue
{
	Renderer::Renderer(uint32 width, uint32 height, HWND window)
	{
		// 장치 생성에 사용하는 옵션.
		uint32 flag = 0u;

#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// 생성할 라이브러리 버전.
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

		// 스왑 체인 정보 구조체.
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { };
		swapChainDesc.Windowed = true; // 창 모드.
		swapChainDesc.OutputWindow = window;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2; // 백 버퍼 개수.
		swapChainDesc.SampleDesc.Count = 1; // 멀티 샘플링 개수.
		swapChainDesc.SampleDesc.Quality = 0; // 멀티 샘플링 수준 (Quality = Count - 1).
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

		// 렌더 타겟 뷰 생성.
		ID3D11Texture2D* backbuffer = nullptr;
		//swapChain->GetBuffer(0, __uuidof(backbuffer), reinterpret_cast<void**>(&backbuffer));

		ThrowIfFailed(swapChain->GetBuffer(
			0, IID_PPV_ARGS(&backbuffer)
		), TEXT("Failed to get back buffer"));

		ThrowIfFailed(device->CreateRenderTargetView(
			backbuffer, nullptr, &renderTargetView
		), TEXT("Failed to create render target view."));

		// 사용한 리소스 해제.
		backbuffer->Release();
		backbuffer = nullptr;

		// 뎁스 스텐실 뷰 생성.
		ID3D11Texture2D* depthStencilBuffer = nullptr;
		D3D11_TEXTURE2D_DESC depthStencilDesc = { };
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		// 2차원 리소스 생성.
		ThrowIfFailed(
			device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer),
			TEXT("Failed to create depth stencil buffer,"))

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = { };
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		// 뷰 생성.
		ThrowIfFailed(device->CreateDepthStencilView(
			depthStencilBuffer,
			&depthStencilViewDesc,
			&depthStencilView),
			TEXT("Failed to create depth stencil view."))

		// 사용한 리소스 해제.
		depthStencilBuffer->Release();
		depthStencilBuffer = nullptr;

		// 렌더 타겟 뷰 바인딩 (연결).
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);

		// 뷰포트 (화면).
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;

		// 뷰포트 설정.
		context->RSSetViewports(1, &viewport);
	}

	Renderer::~Renderer()
	{
		// DX 리소스 해제.
		if (context)
		{
			context->Release();
			context = nullptr;
		}
		if (swapChain)
		{
			swapChain->Release();
			swapChain = nullptr;
		}
 
		if (renderTargetView)
		{
			renderTargetView->Release();
			renderTargetView = nullptr;
		}

		if (depthStencilView)
		{
			depthStencilView->Release();
			depthStencilView = nullptr;
		}
 
		if (device)
		{
			device->Release();
			device = nullptr;
		}
	}

	void Renderer::Draw(std::shared_ptr<Level> level)
	{
		// 화면 크기 변경 중일 때는 종료.
		if (isResizing)
		{
			return;
		}

		// 0. 그리기 전 작업 (BeginScene).
		context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

		// 1. 지우기 (Clear).
		float color[] = { 0.6f, 0.7f, 0.8f, 1.0f };
		context->ClearRenderTargetView(renderTargetView, color);
		context->ClearDepthStencilView(
			depthStencilView,
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f,
			0
		);

		// 2. 그리기 (Draw).
		// 카메라 바인딩.
		if (level->GetCamera())
		{
			level->GetCamera()->Draw();
		}

		for (uint32 ix = 0; ix < level->ActorCount(); ++ix)
		{
			// 액터 가져오기.
			auto actor = level->GetActor(ix);

			// Draw.
			if (actor->IsActive())
			{
				//for (const auto& component : actor->components)
				//{
				//	// Check if component is drawable.
				//}

				actor->Draw();
			}
		}

		// 3. 버퍼 교환 (Swap) => EndScene/Present.
		swapChain->Present(1u, 0u);
	}

	void Renderer::OnResize(uint32 width, uint32 height)
	{
		// 창 변경으로 인한 리소스 크기 조정.
		if (!device || !context || !swapChain)
		{
			return;
		}

		isResizing = true;

		// 컨텍스트 비우기.
		context->ClearState();
		context->Flush();

		// 렌더타겟 해제.
		if (renderTargetView)
		{
			renderTargetView->Release();
			renderTargetView = nullptr;
		}

		// 뎁스 스텐실 뷰 해제.
		if (depthStencilView)
		{
			depthStencilView->Release();
			depthStencilView = nullptr;
		}

		// 스왑체인 백버퍼 크기 변경.
		ThrowIfFailed(
			swapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0),
			TEXT("Failed to resize swapchain buffer.")
		)

		// 렌더타겟 재생성.
		ID3D11Texture2D* backbuffer = nullptr;
		ThrowIfFailed(
			swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer)),
			TEXT("Failed to get buffer from swapchain.")
		)

		ThrowIfFailed(
			device->CreateRenderTargetView(backbuffer, nullptr, &renderTargetView),
			TEXT("Failed to create render target view.")
		)

		backbuffer->Release();
		backbuffer = nullptr;

		// 뎁스 스텐실 뷰 생성.
		ID3D11Texture2D* depthStencilBuffer = nullptr;
		D3D11_TEXTURE2D_DESC depthStencilDesc = { };
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		// 2차원 리소스 생성.
		ThrowIfFailed(
			device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer),
			TEXT("Failed to create depth stencil buffer,"))

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = { };
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		// 뷰 생성.
		ThrowIfFailed(device->CreateDepthStencilView(
			depthStencilBuffer,
			&depthStencilViewDesc,
			&depthStencilView),
			TEXT("Failed to create depth stencil view."))

		// 사용한 리소스 해제.
		depthStencilBuffer->Release();
		depthStencilBuffer = nullptr;

		// 뷰포트 업데이트.
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;

		// 뷰포트 재설정.
		context->RSSetViewports(1, &viewport);

		isResizing = false;
	}
}
