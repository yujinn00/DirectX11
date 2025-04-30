#pragma once

#include "Core/Type.h"
#include <string>
#include <d3d11.h>
#include <memory>

namespace Blue
{
	// 텍스처 파일을 읽어서 저정할 구조체.
	struct TextureData
	{
		TextureData() = default;
		~TextureData()
		{
			// 원시 리소스 해제.
			if (data)
			{
				free(data);
				data = nullptr;
			}

			// DX 리소스 해제.
			if (shaderResourceView)
			{
				shaderResourceView->Release();
				shaderResourceView = nullptr;
			}

			if (samplerState)
			{
				samplerState->Release();
				samplerState = nullptr;
			}
		}

		// 텍스처 원시 데이터.
		int32 width = 0;
		int32 height = 0;
		int32 channelCount = 0;
		void* data = nullptr;

		// DX 리소스.
		ID3D11ShaderResourceView* shaderResourceView = nullptr;
		ID3D11SamplerState* samplerState = nullptr;
	};

	// 텍스처 클래스.
	class Texture
	{
		// 바인딩할 셰이더 열거형.
		enum class BindType
		{
			VertexShader,
			PixelShader
		};

	public:
		Texture();
		Texture(
			const std::string& name,
			BindType bindType = BindType::PixelShader,
			uint32 index = 0u);
		~Texture();

		void Bind(uint32 index = 0);

	protected:
		// 내부에서 이미지 부르는 함수.
		void LoadTexture(const std::string& name);

	protected:
		// 이미지 이름.
		std::string name;

		// 텍스처 순번.
		// uint32 index = 0u;

		// 바인딩 셰이더 타입.
		BindType bindType = BindType::PixelShader;

		// 텍스처 데이터.
		std::unique_ptr<TextureData> textureData;
	};
}
