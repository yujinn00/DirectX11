#include "TextureMappingShader.h"
#include "Render/Texture.h"

namespace Blue
{
	TextureMappingShader::TextureMappingShader()
		:Shader(L"Default")
	{
	}

	TextureMappingShader::TextureMappingShader(const std::string& textureName)
		: Shader(L"Default")
	{
		// �ؽ�ó ����
		texture = std::make_unique<Texture>(textureName);
	}

	void TextureMappingShader::Bind()
	{
		Shader::Bind();

		if (texture)
		{
			texture->Bind();
		}
	}
}
