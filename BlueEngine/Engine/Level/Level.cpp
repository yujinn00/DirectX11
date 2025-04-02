#include "Level.h"
#include "Actor/Actor.h"
#include "Component/CameraComponent.h"

namespace Blue
{
    Level::Level()
    {
    }

    Level::~Level()
    {
    }

    void Level::BeginPlay()
    {
        for (const auto& actor : actors)
        {
            actor->BeginPlay();
        }
    }

    void Level::Tick(float deltaTime)
    {
        if (cameraActor)
        {
            cameraActor->Tick(deltaTime);
        }

        for (const auto& actor : actors)
        {
            actor->Tick(deltaTime);
        }
    }

    void Level::AddActor(std::shared_ptr<Actor> newActor)
    {
        // ���� �߰��ϴ� ���Ͱ� ī�޶� ������Ʈ�� �����µ� Ȯ��.
        // �����ٸ�, ���� ī�޶�� ����.
        for (auto component : newActor->components)
        {
            std::shared_ptr<CameraComponent> cameraComp
                = std::dynamic_pointer_cast<CameraComponent>(component);

            if (cameraComp)
            {
                cameraActor = newActor;
                return;
            }
        }

        actors.emplace_back(newActor);
    }

    std::shared_ptr<Actor> Level::GetActor(int index) const
    {
        if (index < 0 || index >= (int)actors.size())
        {
            return nullptr;
        }

        return actors[index];
    }

    const uint32 Level::ActorCount() const
    {
        return (uint32)actors.size();
    }

    std::shared_ptr<Actor> Level::GetCamera() const
    {
        return cameraActor;
    }
}
