#include "Core/Engine.h"
#include "Math/Vector2.h"

#include <iostream>

using namespace Blue;

// 창 모드로 할 때 메인 함수 (Entry Point)
//int WINAPI WinMain(
//	_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPSTR lpCmdLine,
//	_In_ int nShowCmd
//)
//{
//	// 엔진 생성 및 실행
//	Engine engine(1280, 800, TEXT("Engine Demo"), hInstance);
//	engine.Run();
//
//	return 0;
//}

#include "Render/Texture.h"

int main()
{
	// @Test: 텍스처 파일 로드 테스트
	//Texture texture("T_coord.png");

	Engine engine(1280, 800, TEXT("Engine Demo"), GetModuleHandle(nullptr));
	engine.Run();
}
