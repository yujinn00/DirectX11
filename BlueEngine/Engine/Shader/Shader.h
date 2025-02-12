#pragma once

#include <string>
#include <d3d11.h>

namespace Blue
{
	class Shader
	{
	public:
		Shader(const std::wstring& name = L"Default");
		virtual ~Shader();

		// GPU�� ���̴� ��ü�� ����(���ε�)�ϴ� �Լ�
		virtual void Bind();

	protected:
		// ���̴� �̸�
		std::wstring name;

		// DX ���ҽ�
		ID3D11InputLayout* inputLayout = nullptr;

		ID3D11VertexShader* vertexShader = nullptr;
		ID3DBlob* vertexShaderBuffer = nullptr;

		ID3D11PixelShader* pixelShader = nullptr;
		ID3DBlob* pixelShaderBuffer = nullptr;
	};
}
