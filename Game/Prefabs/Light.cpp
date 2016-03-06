// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Light.hpp"
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/MeshRenderer.hpp>
#include <JuEngine/Components/Light.hpp>
#include "../Features/Light/LightComponent.hpp"

namespace Prefabs
{
auto Light::Create(JuEngine::Pool* pool) -> JuEngine::EntityPtr
{
	auto entity = pool->CreateEntity();

	entity->Add<JuEngine::Transform>();
	entity->Add<JuEngine::MeshRenderer>("obj_cube", "mat_light");
	entity->Add<JuEngine::Light>(vec3(1.f, 1.f, 1.f), 0.2f);
	entity->Add<Components::Light>();

	return entity;
}
}
