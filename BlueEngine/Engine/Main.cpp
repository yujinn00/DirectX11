#include "Core/Engine.h"
#include "Core/Common.h"
#include "Math/Vector2.h"
#include "Render/Texture.h"
#include "Core/Common.h"
#include "Shader/Shader.h"
#include "Shader/TextureMappingShader.h"

#include <iostream>
#include <typeinfo>

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

template<typename T, typename std::enable_if<std::is_base_of<Shader, T>::value>::type* = nullptr>
void TestClass()
{
	std::boolalpha(std::cout);
	std::cout << typeid(T).name() << "\n";
	std::cout << std::is_base_of<Shader, T>::value << "\n";
}

int main()
{
	//TestClass<TextureMappingShader>();
	//TestClass<Engine>();

	//ThrowIfFailed(E_FAIL, TEXT("Test"));

	Engine engine(1280, 800, TEXT("Engine Demo"), GetModuleHandle(nullptr));
	engine.Run();
}
