#pragma once

#include "Core/Type.h"

#include <string>

namespace Blue
{
	class Vector3
	{
	public:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		Vector3(float value)
			: x(value), y(value), z(value)
		{
		}

		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
			: x(x), y(y), z(z)
		{
		}

		// �޸� ũ��
		static uint32 Stride() { return sizeof(Vector3); }

		// ������ �����ε�
		Vector3& operator+=(const Vector3& other);
		Vector3& operator-=(const Vector3& other);
		Vector3& operator*=(float scale);
		Vector3& operator/=(float scale);

		bool operator==(const Vector3& other);
		bool operator!=(const Vector3& other);

		Vector3 operator-() const;

		friend Vector3 operator+(const Vector3& left, const Vector3& right);
		friend Vector3 operator-(const Vector3& left, const Vector3& right);

		friend Vector3 operator*(const Vector3& vector, float scale);
		friend Vector3 operator*(float scale, const Vector3& vector);

		friend Vector3 operator/(const Vector3& vector, float scale);

		// (x, y) ���ڿ� ���� �Լ�
		std::wstring ToString();

		// ���� ���ϱ�
		float Length();
		friend float Dot(const Vector3& left, const Vector3& right); // ����: Dot
		friend Vector3 Cross(const Vector3& left, const Vector3& right); // ����: Cross
		Vector3 Normalized();
		bool Equals(const Vector3& other);

		// ���� ���� (���� �ϱ� ��õ)
		// ����: ((1 - t) * from) + (t * to)
		friend Vector3 Lerp(const Vector3& from, const Vector3& to, float t);

		// �⺻ ��
		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 Right;
		static const Vector3 Up;
		static const Vector3 Forward;
	};
}
