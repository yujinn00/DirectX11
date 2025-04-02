#pragma once

#include <vector>
#include <memory>

#include "Core/Type.h"

namespace Blue
{
    // ���忡 ��ġ�� ���͸� ����.
    class Actor;
    class Level
    {
    public:
        Level();
        virtual ~Level();

        virtual void BeginPlay();
        virtual void Tick(float deltaTime);

        void AddActor(std::shared_ptr<Actor> newActor);

        // Getter.
        std::shared_ptr<Actor> GetActor(int index) const;
        const uint32 ActorCount() const;

        std::shared_ptr<Actor> GetCamera() const;

    protected:
        std::vector<std::shared_ptr<Actor>> actors;

        // ���� ī�޶� ����.
        std::shared_ptr<Actor> cameraActor;
    };
}
