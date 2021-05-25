#include "Systems/MaterialAttachSystem.h"
#include "Components/MaterialComponent.h"
#include "Components/RenderedComponent.h"
#include "ObjectDrawable.h"

void MaterialAttachSystem::OnInit()
{
    auto Entities = _entities->GetEntitiesBy<MaterialComponent>();

    for (const auto& it : Entities)
    {
        auto [material] = it.Components;

        GLint ok;
        GLchar log[2000];
        material->_materialId = glCreateProgram();
        glAttachShader(material->_materialId, material->FragmentShader->_shaderId);
        glAttachShader(material->_materialId, material->VertexShader->_shaderId);
        glLinkProgram(material->_materialId);
        glGetProgramiv(material->_materialId, GL_LINK_STATUS, &ok);
        if (!ok)
        {
            glGetProgramInfoLog(material->_materialId, 2000, NULL, log);
            printf("\n");
        }
    }
}
