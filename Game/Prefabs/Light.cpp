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
auto Light::Create(Pool* pool) -> EntityPtr
{
	auto entity = pool->CreateEntity();

	entity->Add<Transform>();
	entity->Get<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));
	entity->Add<MeshRenderer>("obj_cube", "shader_vertexColor");
	entity->Add<JuEngine::Light>(vec3(1.f, 1.f, 1.f), 1.0f, LightType::LIGHT_POINT);
	entity->Add<Components::Light>();

	return entity;
}
}
