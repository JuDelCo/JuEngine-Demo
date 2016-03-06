// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Sun.hpp"
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/MeshRenderer.hpp>
#include <JuEngine/Components/Light.hpp>
#include "../Features/Sun/SunComponent.hpp"

namespace Prefabs
{
auto Sun::Create(JuEngine::Pool* pool) -> JuEngine::EntityPtr
{
	auto entity = pool->CreateEntity();

	entity->Add<JuEngine::Transform>();
	entity->GetTransform()->Scale(vec3(85.f, 85.f, 85.1f));

	entity->Add<JuEngine::MeshRenderer>("obj_sphere", "mat_light");
	entity->Add<JuEngine::Light>(vec3(1.f, 0.956f, 0.839f), 1.f, JuEngine::LightType::LIGHT_DIRECTIONAL);
	entity->Add<Components::Sun>();

	return entity;
}
}
