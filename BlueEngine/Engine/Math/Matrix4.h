#pragma once

#include "Vector3.h"

namespace Blue
{
	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(const Matrix4& other);
		~Matrix4() = default;

		// 메모리 너비 (단위: 바이트).
		static uint32 Stride() { return sizeof(Matrix4); }

		// 이동 변환 행렬 (T).
		static Matrix4 Translation(const Vector3& position);	// 메인 X => 간접 호출.
		static Matrix4 Translation(float x, float y, float z);	// 메인 O.

		// 회전 변환 행렬 (R).
		static Matrix4 Rotation(const Vector3& rotation);		// 메인 X => 간접 호출.
		static Matrix4 Rotation(float x, float y, float z);		// 메인 X => 간접 호출.
		static Matrix4 RotationX(float angle);					// 메인 O.
		static Matrix4 RotationY(float angle);					// 메인 O.
		static Matrix4 RotationZ(float angle);					// 메인 O.

		// 크기 변환 행렬 (S).
		static Matrix4 Scale(const Vector3& scale);				// 메인 X => 간접 호출.
		static Matrix4 Scale(float x, float y, float z);		// 메인 O.
		static Matrix4 Scale(float scale);						// 메인 X => 간접 호출.

		// 전치 행렬.
		static Matrix4 Transpose(const Matrix4& target);

		// 원근 투영 (perspective).
		static Matrix4 Perspective(
			float fieldOfView,		// 시야각.
			float width,			// 종횡비를 구하기 위한 화면의 너비.
			float height,			// 종횡비를 구하기 위한 화면의 높이.
			float nearDistance,		// 화면에 그려질 수 있는 가장 가까운 거리.
			float farDistance		// 화면에 그려질 수 있는 가장 먼 거리.
		);

		// operator overloading.
		Matrix4& operator=(const Matrix4& other);
		Matrix4 operator*(const Matrix4& other);
		Matrix4 operator*=(const Matrix4& other);

		friend Vector3 operator*(const Matrix4& matrix, const Vector3& vector); // 이건 메인이 아니므로 간접 호출.
		friend Vector3 operator*(const Vector3& vector, const Matrix4& matrix); // DX에서는 이게 메인.

		// Degree <-> Radian.
		static Matrix4 Identity;
		static constexpr float degreeToRadian = 3.141592f / 180.0f;
		static constexpr float radianToDegree = 180.0f / 3.141592f;

	private:
		// 공용체.
		union
		{
			struct
			{
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};

			float elements[4 * 4];
		};
	};
}
