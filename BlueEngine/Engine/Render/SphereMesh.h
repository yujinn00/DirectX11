#pragma once

#include "Mesh.h"

namespace Blue
{
    // 구체 메쉬 클래스.
    class SphereMesh : public Mesh
    {
    public:
        SphereMesh();

        void Update(float deltaTime);

    private:
        void Rotate(float angle);
    };
}
