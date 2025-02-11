#include "Renderer.h"

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
		//DXGI_MODE_DESC BufferDesc;
		//DXGI_SAMPLE_DESC SampleDesc;
		//DXGI_USAGE BufferUsage;
		//UINT BufferCount;
		//HWND OutputWindow;
		//BOOL Windowed;
		//DXGI_SWAP_EFFECT SwapEffect;
		//UINT Flags;

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

		// ���� ������ ����
		float vertices[] =
		{
			0.0f, 0.5f, 0.5f,		// 0��
			0.5f, -0.5f, 0.5f,		// 1��
			-0.5f, -0.5f, 0.5f,		// 2��
		};

		// @Temp: �ӽ� ���ҽ� ����
		// ����(Buffer) - �޸� ���
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth = sizeof(float) * 3 * 3;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// ���� ������
		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = vertices;

		// (����)���� ����
		result = device->CreateBuffer(
			&vertexBufferDesc, &vertexData, &vertexBuffer
		);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create vertex buffer", "Error", MB_OK);
			__debugbreak();
		}

		// �ε���(����) ���� ���� => ������ �����ϴ� ����
		int indices[] = { 0, 1, 2 };

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(float) * 3 * 3;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = {};
		indexData.pSysMem = indices;

		result = device->CreateBuffer(
			&indexBufferDesc, &indexData, &indexBuffer
		);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create index buffer", "Error", MB_OK);
			__debugbreak();
		}

		// ���̴� ������
		ID3DBlob* vertexShaderBuffer = nullptr;
		D3DCompileFromFile(
			TEXT("VertexShader.hlsl"),
			nullptr,
			nullptr,
			"main",
			"vs_5_0",
			0, 0,
			&vertexShaderBuffer, nullptr
		);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to compile vertex shader", "Error", MB_OK);
			__debugbreak();
		}

		// ���̴� ����
		result = device->CreateVertexShader(
			vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			nullptr,
			&vertexShader
		);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create vertex shader", "Error", MB_OK);
			__debugbreak();
		}

		// �Է� ���̾ƿ�
		// ���� ���̴��� ������ ���� �����Ͱ� ��� ������� �˷���
		//LPCSTR SemanticName;
		//UINT SemanticIndex;
		//DXGI_FORMAT Format;
		//UINT InputSlot;
		//UINT AlignedByteOffset;
		//D3D11_INPUT_CLASSIFICATION InputSlotClass;
		//UINT InstanceDataStepRate;
		D3D11_INPUT_ELEMENT_DESC inputDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		
		result = device->CreateInputLayout(
			inputDesc,
			1,
			vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			&inputLayout
		);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create input layout", "Error", MB_OK);
			__debugbreak();
		}

		// �ȼ� ���̴� ������ �� ���� (���� �� ��)
		// �� ���ҽ� ���ε� (���� �� ��)
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Draw()
	{
		// 1. �׸��� �� �۾� => BeginScene
		// �����(Clear)
		float color[] = { 0.6f, 0.7f, 0.8f, 1.0f };
		context->ClearRenderTargetView(renderTargetView, color);

		// 2. ��ο�(Draw) => Draw

		// 3. ���� ��ȯ => EndScene/Present
		swapChain->Present(1u, 0u);
	}
}
