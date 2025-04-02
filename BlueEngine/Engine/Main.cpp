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

/*
* Todo List.
* - Input Controller (Window Message Process).
* - Actor(Entity/GameObject) / Component / Scene(Level).
* - FBX Loader (Assimp/FBX SDK -> Submesh).
* - Camera ( View / Projection(Perspective/Othographic) ).
*   - Screen Coordinate System (NDC - Normalized Device Coordinates).
* - Shade (Shader) (Light / Brightness / Darkness ).
*   - Ambient(Static/GI) / Diffuse (Lambert .../Roughness) / Specular (Highlight, Phong/Blinn-Phong / Metalic).
* - Normal Mapping.
* - Render Target (Draw to texture).
* - Shadow Mapping (Shadow Map).
* - Environment Mapping (Sky Sphere(Box)).
* - Study (Tone Mapping).
*
* - Skeletal Mesh (Skinned Mesh) - Skeleton.
*   - Skeletal Mesh Animation.
* - Toy Project...
*
* - Study (Physics).
*/

/*
* IA(�Է� ����) -> VS ...(Option) -> RS/������ -> PS -> OM(��� ����).
* - VS (���� ��ȯ Object->World->View->Projection).
* - PS (���� ó��) - PBR / ��ǻ�� / ����ŧ��.
* - ���� ������ (������(Renderer) - ������).
*/

int main()
{
	Engine engine(1280, 800, TEXT("Engine Demo"), GetModuleHandle(nullptr));
	engine.Run();
}
