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
#include "Component/CameraComponent.h"

namespace Blue
{
    DemoLevel::DemoLevel()
    {
        // ���� ��(����) ����.

        // ���� ����.
        std::shared_ptr<QuadActor> actor = std::make_shared<QuadActor>();
        actor->transform.scale = Vector3::One * 0.5f;
        //actor->transform.position.x = 0.5f;

        std::shared_ptr<QuadActor> actor2 = std::make_shared<QuadActor>();
        actor2->transform.scale = Vector3::One * 0.5f;
        actor2->transform.position.x = 0.6f;

        // ī�޶� ���� ����.
        std::shared_ptr<Actor> cameraActor = std::make_shared<Actor>();
        cameraActor->transform.position.y = -0.5f;
        cameraActor->AddComponent(std::make_shared<CameraComponent>());

        //this->cameraActor = cameraActor;

        // ���͸� ������ �߰�.
        AddActor(actor);
        AddActor(actor2);
        AddActor(cameraActor);
    }

    DemoLevel::~DemoLevel()
    {
    }
}
