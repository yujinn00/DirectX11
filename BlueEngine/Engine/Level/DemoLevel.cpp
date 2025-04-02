#include "DemoLevel.h"

#include "Actor/Actor.h"
#include "Actor/QuadActor.h"

#include "Math/Transform.h"
#include "Math/Vector3.h"

#include "Render/QuadMesh.h"

#include "Resource/ShaderLoader.h"
#include "Resource/ModelLoader.h"
#include "Resource/TextureLoader.h"

#include "Shader/TextureMappingShader.h"

#include "Component/StaticMeshComponent.h"

namespace Blue
{
    DemoLevel::DemoLevel()
    {
        // ���� ��(����) ����.

        // ���� ����.
        std::shared_ptr<QuadActor> actor = std::make_shared<QuadActor>();
        actor->transform.scale = Vector3::One * 0.5f;
        actor->transform.position.x = 0.5f;

        // ���͸� ������ �߰�.
        AddActor(actor);
    }

    DemoLevel::~DemoLevel()
    {
    }
}
