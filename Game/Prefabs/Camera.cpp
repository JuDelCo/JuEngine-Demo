// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Camera.hpp"
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/Camera.hpp>
#include "../Features/Camera/CameraComponent.hpp"

namespace Prefabs
{
auto Camera::Create(JuEngine::Pool* pool) -> JuEngine::EntityPtr
{
	auto entity = pool->CreateEntity();

	entity->Add<JuEngine::Transform>();
	entity->Add<JuEngine::Camera>(entity->GetTransform());
	entity->Add<Components::Camera>();

	return entity;
}
}
