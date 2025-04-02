#include "Actor.h"
#include "Component/Component.h"

namespace Blue
{
    Actor::Actor()
    {
    }

    Actor::~Actor()
    {
    }

    void Actor::BeginPlay()
    {
        // ���� ó��.
        if (hasInitialized)
        {
            return;
        }

        // �ʱ�ȭ ����.
        hasInitialized = true;

        // ������Ʈ �Լ� ȣ��.
        for (const auto& component : components)
        {
            component->BeginPlay();
        }
    }

    void Actor::Tick(float deltaTime)
    {
        // ���� ó��.
        if (!IsActive())
        {
            return;
        }

        // Ʈ������ ������Ʈ.
        transform.Tick();

        // ������Ʈ �Լ� ȣ��.
        for (const auto& component : components)
        {
            component->Tick(deltaTime);
        }
    }

    void Actor::Draw()
    {
        // ���� ó��.
        if (!IsActive())
        {
            return;
        }

        // Ʈ������ ���ε� (���̴��� ������ ����).
        transform.Bind();

        // ������Ʈ �Լ� ȣ��.
        for (const auto& component : components)
        {
            component->Draw();
        }
    }

    void Actor::Destroy()
    {
        hasDestroyed = true;
    }

    void Actor::AddComponent(std::shared_ptr<Component> newComponent)
    {
        // ������Ʈ �迭�� ���ο� ������Ʈ �߰�.
        components.emplace_back(newComponent);

        // ������Ʈ�� ���� ����.
        newComponent->SetOwner(this);
    }

    const bool Actor::IsActive() const
    {
        return isActive && !hasDestroyed;
    }

    const bool Actor::HasInitialized() const
    {
        return hasInitialized;
    }
}
