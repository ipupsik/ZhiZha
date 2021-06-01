#include "ComponentDrop.h"
#include "ComponentVolume.h"
#include "utils.h"
#include "DefinesPhysics.h"

#include <iostream>


#include "Systems/ComplexCollisionSystem.h"

#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"
#include "Components/MeshCollider.h"
#include "Components/ComplexCollisionComponent.h"
#include "Components/SpeedComponent.h"

using namespace sf::Extensions::Vector2;

void ComplexCollisionSystem::OnFixedUpdate()
{
	/*
	//получаем все треугольники, принадлежащие карте (интерактивной) -- start
	const auto& mesh_componetns = _entities->GetEntitiesBy<MeshComponent, MeshCollider>();

	struct face {
		sf::Vector2f v1, v2, v3;
	};
	std::vector<face> triangles_map;

	for (auto& [components, cur_map] : mesh_componetns)
	{
		auto& [mesh_comp, mesh_collider] = components;

		face cur_face;

		for (int i = 0; i < mesh_comp->Mesh->_faces.size(); i += 3)
		{
			cur_face.v1.x = mesh_comp->Mesh->_faces[i].x;
			cur_face.v1.y = mesh_comp->Mesh->_faces[i].y;

			cur_face.v2.x = mesh_comp->Mesh->_faces[i + 1].x;
			cur_face.v2.y = mesh_comp->Mesh->_faces[i + 1].y;

			cur_face.v3.x = mesh_comp->Mesh->_faces[i + 2].x;
			cur_face.v3.y = mesh_comp->Mesh->_faces[i + 2].y;

			triangles_map.push_back(cur_face);
		}		
	}
	//получаем все треугольники, принадлежащие карте (интерактивной) -- end
	*/

	//сталкиваем все камли с треугольниками карты
	const auto& drops = _entities->GetEntitiesBy<ComponentDrop, SpeedComponent, TransformComponent>(); //наши капли
	const auto& maps_items = _entities->GetEntitiesBy<ComplexCollisionComponent>(); //наши объекты, с которыми мы можем столкнуться

	for (auto& [components, cur_entity] : drops)
	{
		auto& [drop_comp, speed_comp, transform] = components;

		for (auto& [components_map, cur_map_item] : maps_items)
		{
			auto& [ccc] = components_map;

			std::cout << ccc->ComplexCollision.size() << std::endl;

			for (int i = 0; i < ccc->ComplexCollision.size(); ++i)
			{
				// составление векторов-сторон треугольника
				sf::Vector2f vec12 = ccc->ComplexCollision[i].v2 - ccc->ComplexCollision[i].v1;
				sf::Vector2f vec13 = ccc->ComplexCollision[i].v3 - ccc->ComplexCollision[i].v1;
				sf::Vector2f vec23 = ccc->ComplexCollision[i].v3 - ccc->ComplexCollision[i].v2;

				// составление вектора от каждой точки до центра окружности
				sf::Vector2f vec10 = transform->Location - ccc->ComplexCollision[i].v1;
				sf::Vector2f vec20 = transform->Location - ccc->ComplexCollision[i].v2;
				sf::Vector2f vec30 = transform->Location - ccc->ComplexCollision[i].v3;

				

				float cos_012 = vec12->*Dot(vec10) / vec12->*Length() / vec10->*Length();
				
				float cos_021 = (-vec12)->*Dot(vec20) / vec12->*Length() / vec20->*Length();

				float cos_013 = vec13->*Dot(vec10) / vec13->*Length() / vec10->*Length();
				float cos_031 = (-vec13)->*Dot(vec30) / vec13->*Length() / vec30->*Length();

				
				float cos_023 = vec23->*Dot(vec20) / vec23->*Length() / vec20->*Length();
				float cos_032 = (-vec23)->*Dot(vec30) / vec23->*Length() / vec30->*Length();

				float h_12 = fabs(sqrt(pow(vec10->*Length(), 2) - pow(cos_012 * vec10->*Length(), 2)));
				float h_13 = fabs(sqrt(pow(vec10->*Length(), 2) - pow(cos_013 * vec10->*Length(), 2)));
				float h_23 = fabs(sqrt(pow(vec20->*Length(), 2) - pow(cos_023 * vec20->*Length(), 2)));

				float min_h; //минимальное расстояние до стороны
				sf::Vector2f min_line; //минимальная сторона
				sf::Vector2f min_dist_to_center; //минимальное расстояние до центра окружности
				bool does_hit = false;

				if (cos_012 >= 0 && cos_021 >= 0)
				{
					min_h = h_12;
					min_line = vec12;
					min_dist_to_center = vec10;

					does_hit = true;
				}
				else if (cos_012 < 0 && cos_021 >= 0)
				{
					min_h = vec10->*Length();
					min_line = vec12;
					min_dist_to_center = vec10;

					does_hit = true;
				}

				if (cos_013 >= 0 && cos_031 >= 0)
				{
					if (!does_hit || h_13 < min_h)
					{
						min_h = h_13;
						min_line = vec13;
						min_dist_to_center = vec10;

						does_hit = true;
					}
				}
				else if (cos_013 < 0 && cos_031 >= 0)
				{
					if (!does_hit || vec10->*Length() < min_h)
					{
						min_h = vec10->*Length();
						min_line = vec13;
						min_dist_to_center = vec10;

						does_hit = true;
					}
				}

				if (cos_023 >= 0 && cos_032 >= 0)
				{
					if (!does_hit || h_23 < min_h)
					{
						min_h = h_23;
						min_line = vec23;
						min_dist_to_center = vec20;

						does_hit = true;
					}
				}
				else if (cos_023 < 0 && cos_032 >= 0)
				{
					if (!does_hit || vec20->*Length() < min_h)
					{
						min_h = vec20->*Length();
						min_line = vec23;
						min_dist_to_center = vec20;

						does_hit = true;
					}
				}
				
				// int res = min_h < RADIUS;
				std::cout << "hello" << std::endl;

				if (does_hit && min_h < RADIUS)
				{
					std::cout << "collided wall" << std::endl;

					float z_coord = -min_line.x * min_dist_to_center.y + min_line.y * min_dist_to_center.x;
					sf::Vector2f n = {
						min_line.y * z_coord,
						-min_line.x * z_coord
					};

					n->*Normalize();

					

					sf::Vector2f new_velocity = speed_comp->Speed - n * 2.f * n->*Dot(speed_comp->Speed);

					speed_comp->Speed = new_velocity * 1.f;

					transform->Location = transform->Location + n * (RADIUS - min_h);
				}
			}
		}
	}
}