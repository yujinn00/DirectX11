#include "Core/Engine.h"
#include "Math/Vector2.h"

#include <iostream>

using namespace Blue;

// â ���� �� �� ���� �Լ� (Entry Point)
//int WINAPI WinMain(
//	_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPSTR lpCmdLine,
//	_In_ int nShowCmd
//)
//{
//	// ���� ���� �� ����
//	Engine engine(1280, 800, TEXT("Engine Demo"), hInstance);
//	engine.Run();
//
//	return 0;
//}

#include "Render/Texture.h"

int main()
{
	// @Test: �ؽ�ó ���� �ε� �׽�Ʈ
	//Texture texture("T_coord.png");

	Engine engine(1280, 800, TEXT("Engine Demo"), GetModuleHandle(nullptr));
	engine.Run();
}
