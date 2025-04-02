#include "StaticMeshComponent.h"
#include "Render/Mesh.h"
#include "Shader/Shader.h"
#include "Core/Engine.h"

namespace Blue
{
    StaticMeshComponent::StaticMeshComponent()
    {
    }

    StaticMeshComponent::~StaticMeshComponent()
    {
    }

    void StaticMeshComponent::Draw()
    {
        // ���� �޽ø� ��ȸ�ϸ鼭 DrawCall.
        uint32 meshCount = mesh->SubMeshCount();

        // ����ó��.
        if (meshCount != (uint32)shaders.size())
        {
            return;
        }

        for (int ix = 0; ix < meshCount; ++ix)
        {
            // ���� �޽� ��������.
            auto subMesh = mesh->GetSubMesh(ix);

            // �޽ð� ��ȿ�ϸ� Draw.
            if (subMesh.lock())
            {
                // ���� �޽� ���ε�.
                subMesh.lock()->Bind();

                // ���̴� ���ε�.
                shaders[ix]->Bind();

                // DrawCall.
                static ID3D11DeviceContext& context = Engine::Get().Context();
                context.DrawIndexed(subMesh.lock()->IndexCount(), 0u, 0u);
            }
        }
    }

    void StaticMeshComponent::SetMesh(std::shared_ptr<Mesh> newMesh)
    {
        mesh = newMesh;
    }

    void StaticMeshComponent::AddShader(std::shared_ptr<Shader> newShader)
    {
        shaders.emplace_back(newShader);
    }
}
