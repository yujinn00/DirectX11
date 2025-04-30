#include "RenderTexture.h"
#include "Core/Engine.h"

Blue::RenderTexture::RenderTexture(uint32 width, uint32 height)
{
    // Render Target View / Shader Resource View / Depth Stencil View.
    static ID3D11Device& device = Engine::Get().Device();

    // 너비 및 높이 값 조정.
    width = width == 0 ? Engine::Get().Width() : width;
    height = height == 0 ? Engine::Get().Height() : height;

    // textureData 생성.
    textureData = std::make_unique<TextureData>();
    textureData->width = width;
    textureData->height = height;

    // Render Target View 생성.
    // 단계 1: RTV 생성에 사용할 텍스처 생성.
    // 단계 2: 생성된 텍스처와 옵션을 추가해 RTV 생성.

    // 단계 1.
}

Blue::RenderTexture::~RenderTexture()
{
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
}
