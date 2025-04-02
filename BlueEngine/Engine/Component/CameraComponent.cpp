#include "CameraComponent.h"
#include "Core/Engine.h"
#include "Math/Transform.h"
#include "Actor/Actor.h"

namespace Blue
{
    CameraComponent::CameraComponent()
    {
        // ����� ������Ʈ �� ���ε�.
        data.viewMatrix
            = Matrix4::Translation(owner->transform.position * -1.0f)
            * Matrix4::Transpose(Matrix4::Rotation(owner->transform.rotation));

        // ������ ��Ƽ� ���� ����.
    }

    void CameraComponent::Draw()
    {
        Component::Draw();

        // ����� ������Ʈ �� ���ε�.
        data.viewMatrix
            = Matrix4::Translation(owner->transform.position * -1.0f)
            * Matrix4::Transpose(Matrix4::Rotation(owner->transform.rotation));
    }
}
