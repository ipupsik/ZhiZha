#include "Systems/MaterialAttachSystem.h"
#include "Components/MaterialComponent.h"

void MaterialAttachSystem::OnInit()
{
    auto Entities = _entities->GetEntitiesBy<MaterialComponent>();

    for (const auto& it : Entities)
    {
        auto [Material] = it.Components;

        GLint ok;
        GLchar log[2000];
        Material->_materialId = glCreateProgram();
        glAttachShader(Material->_materialId, Material->FragmentShader->_shaderId);
        glAttachShader(Material->_materialId, Material->VertexShader->_shaderId);
        glLinkProgram(Material->_materialId);
        glGetProgramiv(Material->_materialId, GL_LINK_STATUS, &ok);
        if (!ok)
        {
            glGetProgramInfoLog(Material->_materialId, 2000, NULL, log);
            printf("\n");
        }
    }
}
