#pragma once

#include <d3d11.h>

#include "Vector3.h"
#include "Matrix4.h"

namespace Blue
{
	// Ʈ������(��ȯ) ������ �����ϴ� Ŭ����.
	class Transform
	{
	public:
		Transform();
		~Transform();

		void Bind();

	public:
		// Ʈ������(��ȯ) ��� (TRS).
		Vector3 position = Vector3::Zero;
		Vector3 rotation = Vector3::Zero; // ���� ������� �ٲ� �� ����.
		Vector3 scale = Vector3::One;

	private:
		// Ʈ������ ���.
		Matrix4 transformMatrix;

		// ��� ����.
		ID3D11Buffer* constantBuffer = nullptr;
	};
}
