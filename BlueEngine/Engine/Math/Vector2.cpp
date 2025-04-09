#include "Vector2.h"

#include <Windows.h>
#include <cmath>
#include <cassert>

/*
레전드 상황 발생 => 아래 필기를 했는데,
이게 왜 갑자기 나왔는지 전혀 모름 ㅋㅎ
Q) tan 왜 쓰냐 ?
A) sin cos도 되긴 되는데
tan이 더 효율적임
이유는 잘 모름 ㅋㅎ
tan 치명적인 단점: 특정 부분에 무한대로 뻗음
그래서 그 부분에 값이 들어가면 해를 못 구함
이걸 해결하는 방법: 아크탄젠트2
무한대로 뻗는 탄젠트를 평행 이동시켜서
각도만 구하는 방법임
Q) 부동 소수가 어떻게 저장되는가 ?
A) 모름 ㅋㅎ
*/

namespace Blue
{
	const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
	const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
	const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
	const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);

	std::wstring Vector2::ToString()
	{
		wchar_t buffer[256];
		swprintf_s(buffer, 256, TEXT("(%f, %f)"), x, y);

		return buffer;
	}

	float Vector2::Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2 operator+(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x + right.x, left.y + right.y);
	}

	Vector2 operator-(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x - right.x, left.y - right.y);
	}

	Vector2 operator*(const Vector2& vector, float scale)
	{
		return Vector2(vector.x * scale, vector.y * scale);
	}

	Vector2 operator*(float scale, const Vector2& vector)
	{
		//return Vector2(vector.x * scale, vector.y * scale);
		return vector * scale;
	}

	Vector2 operator/(const Vector2& vector, float scale)
	{
		assert(scale != 0.0f);
		return Vector2(vector.x / scale, vector.y / scale);
	}

	float Dot(const Vector2& left, const Vector2& right)
	{
		return (left.x * right.x) + (left.y * right.y);
	}

	Vector2 Lerp(const Vector2& from, const Vector2& to, float t)
	{
		// t 가두기.
		if (t < 0.0f)
		{
			t = 0.0f;
		}
		if (t > 1.0f)
		{
			t = 1.0f;
		}

		return (1.0f - t) * from + t * to;
	}

	Vector2 Vector2::Normalized()
	{
		float length = Length();
		return Vector2(x / length, y / length);
	}

	bool Vector2::Equals(const Vector2& other)
	{
		return x == other.x && y == other.y;
	}

	Vector2& Vector2::operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2& Vector2::operator*=(float scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}

	Vector2& Vector2::operator/=(float scale)
	{
		// 나눌 값이 0이 아닌지 확인하는 것이 좋음.
		assert(scale != 0.0f);

		x /= scale;
		y /= scale;
		return *this;
	}

	bool Vector2::operator==(const Vector2& other)
	{
		return x == other.x && y == other.y;
	}

	bool Vector2::operator!=(const Vector2& other)
	{
		return x != other.x || y != other.y;
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2(-x, -y);
	}
}
