#pragma once

#include "../Core/Type.h"

#include <string>

namespace Blue
{
	// 2���� ���� Ŭ����
	class Vector2
	{
	public:
		// X ��ǥ �� Y ��ǥ
		float x;
		float y;

		Vector2()
			: x(0.0f), y(0.0f)
		{
		}

		Vector2(float value)
			: x(value), y(value)
		{
		}

		Vector2(float x, float y)
			: x(x), y(y)
		{
		}

		// �޸� ũ��
		static uint32 Stride() { return sizeof(Vector2); }

		// ������ �����ε�
		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);
		Vector2& operator*=(float scale);
		Vector2& operator/=(float scale);

		bool operator==(const Vector2& other);
		bool operator!=(const Vector2& other);

		Vector2 operator-() const;

		friend Vector2 operator+(const Vector2& left, const Vector2& right);
		friend Vector2 operator-(const Vector2& left, const Vector2& right);

		friend Vector2 operator*(const Vector2& vector, float scale);
		friend Vector2 operator*(float scale, const Vector2& vector);

		friend Vector2 operator/(const Vector2& vector, float scale);

		// (x, y) ���ڿ� ���� �Լ�
		std::wstring ToString();

		// ���� ���ϱ�
		float Length();
		friend float Dot(const Vector2& left, const Vector2& right);
		Vector2 Normalized();
		bool Equals(const Vector2& other);

		// ���� ���� (���� �ϱ� ��õ)
		// ����: ((1 - t) * from) + (t * to)
		friend Vector2 Lerp(const Vector2& from, const Vector2& to, float t);

		// �⺻ ��
		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 Right;
		static const Vector2 Up;
	};
};
