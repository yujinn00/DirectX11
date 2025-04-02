#include "QuadActor.h"

#include "Component/StaticMeshComponent.h"
#include "Render/QuadMesh.h"
#include "Shader/TextureMappingShader.h"
#include "Resource/ShaderLoader.h"

namespace Blue
{
    QuadActor::QuadActor()
    {
        // ����ƽ �޽� ������Ʈ ����.
        std::shared_ptr<StaticMeshComponent> meshComponent
            = std::make_shared<StaticMeshComponent>();

        // ���Ϳ� ������Ʈ �߰�.
        AddComponent(meshComponent);

        // ���ҽ� �ε� �� ������Ʈ ����.
        meshComponent->SetMesh(std::make_shared<QuadMesh>());
        std::weak_ptr<TextureMappingShader> shader;
        if (ShaderLoader::Get().Load<TextureMappingShader>(shader, "T_coord.png"))
        {
            meshComponent->AddShader(shader);
        }
    }
}
