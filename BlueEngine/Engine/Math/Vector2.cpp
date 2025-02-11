#include "Vector2.h"

#include <Windows.h>
#include <cmath>

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
*/

/*
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
	float Vector2::Dot(const Vector2& other)
	{
		return (x * other.x) + (y * other.y);
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
}
