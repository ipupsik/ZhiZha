#include "ComponentDrop.h"
#include "Components/MeshComponent.h"
#include "Components/RenderedComponent.h"
#include "ZhizhaVolumeComponent.h"
#include "DrawableZhizha.h"
#include "utils.h"

#include "FormZhizhaVolume_System.h"

using namespace sf::Extensions::Vector2;

void FormZhizhaVolume_System::OnFixedUpdate()
{
	const auto& drops = _entities->GetEntitiesBy<ComponentDrop>();

	const auto& _ZhizhaVolume = _entities->GetEntitiesBy<RenderedComponent, ZhizhaVolumeComponent>();
	if (_ZhizhaVolume.size() > 0)
	{
		const auto& [_RenderedComponent, _ZhizhaVolumeComponent] = _ZhizhaVolume[0].Components;

		DrawableZhizha* _DrawableZhizha = dynamic_cast<DrawableZhizha*>(_RenderedComponent->DrawableObj);

		std::vector<sf::Vector2f>tmp(0);
		for (auto& [components, cur_entity] : drops)
		{
			auto& [drop_comp] = components;
			sf::Vector2f center = _entities->GetComponent<TransformComponent>(*cur_entity)->Location;
			float radius = _entities->GetComponent<TransformComponent>(*cur_entity)->Scale.x;
			int length = drop_comp->neighbours.size();

			/*for (int i = 0; i < length - 1; i++)
			{
				sf::Vector2f center_i = _entities->GetComponent<TransformComponent>(*(drop_comp->neighbours[i]))->Location;
				for (int j = i + 1; j < length; j++)
				{
					sf::Vector2f center_j = _entities->GetComponent<TransformComponent>(*(drop_comp->neighbours[i]))->Location;
					tmp.emplace_back(center_i);
					tmp.emplace_back(center);
					tmp.emplace_back(center_j);
				}
			}*/

			for (int i = 0; i < length; i++)
			{
				sf::Vector2f center_i = _entities->GetComponent<TransformComponent>(*(drop_comp->neighbours[i]))->Location;

				sf::Vector2f CenterVector = center_i - center;

				sf::Vector2f OthoCenterVector;
				OthoCenterVector.x = CenterVector.y;
				OthoCenterVector.y = -CenterVector.x;
				OthoCenterVector->*Normalize();
				OthoCenterVector *= radius;

				tmp.emplace_back(center + OthoCenterVector);
				tmp.emplace_back(center_i - OthoCenterVector);
				tmp.emplace_back(center - OthoCenterVector);
			}
			_DrawableZhizha->vertices[_DrawableZhizha->side] = tmp;
		}
	}
}