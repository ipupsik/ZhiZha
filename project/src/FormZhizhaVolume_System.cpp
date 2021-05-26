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
	const auto& [_RenderedComponent, _ZhizhaVolumeComponent] = _ZhizhaVolume[0].Components;

	DrawableZhizha*_DrawableZhizha = dynamic_cast<DrawableZhizha*>(_RenderedComponent->DrawableObj);
	_DrawableZhizha->vertices.clear();
	for (auto& [components, cur_entity] : drops)
	{
		auto&[drop_comp] = components;
		sf::Vector2f center = _entities->GetComponent<TransformComponent>(*cur_entity)->Location;
		float radius = _entities->GetComponent<TransformComponent>(*cur_entity)->Scale.x;

		for (int i = 0; i < drop_comp->neighbours.size() - 1; i++)
		{
			sf::Vector2f center_i = _entities->GetComponent<TransformComponent>(*drop_comp->neighbours[i])->Location;
			for (int j = i + 1; j < drop_comp->neighbours.size(); j++)
			{
				sf::Vector2f center_j = _entities->GetComponent<TransformComponent>(*drop_comp->neighbours[i])->Location;
				_DrawableZhizha->vertices.emplace_back(center_i.x);
				_DrawableZhizha->vertices.emplace_back(center_i.x);

				_DrawableZhizha->vertices.emplace_back(center.x);
				_DrawableZhizha->vertices.emplace_back(center.y);

				_DrawableZhizha->vertices.emplace_back(center_j.x);
				_DrawableZhizha->vertices.emplace_back(center_j.y);
			}
		}

		for (int i = 0; i < drop_comp->neighbours.size(); i++)
		{
			sf::Vector2f center_i = _entities->GetComponent<TransformComponent>(*drop_comp->neighbours[i])->Location;

			sf::Vector2f CenterVector = center_i - center;

			sf::Vector2f OthoCenterVector;
			OthoCenterVector.x = CenterVector.y;
			OthoCenterVector.y = -CenterVector.x;
			OthoCenterVector->*Normalize();
			OthoCenterVector *= radius;

			_DrawableZhizha->vertices.emplace_back((center + OthoCenterVector).x);
			_DrawableZhizha->vertices.emplace_back((center + OthoCenterVector).y);

			_DrawableZhizha->vertices.emplace_back((center_i - OthoCenterVector).x);
			_DrawableZhizha->vertices.emplace_back((center_i - OthoCenterVector).y);

			_DrawableZhizha->vertices.emplace_back((center - OthoCenterVector).x);
			_DrawableZhizha->vertices.emplace_back((center - OthoCenterVector).y);
		}
	}
}