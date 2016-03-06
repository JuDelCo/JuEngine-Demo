// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Hat.hpp"
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/MeshRenderer.hpp>

namespace Prefabs
{
auto Hat::Create(JuEngine::Pool* pool) -> JuEngine::EntityPtr
{
	auto entity = pool->CreateEntity();

	entity->Add<JuEngine::Transform>();
	// TODO: Fix orientation in Blender !
	entity->GetTransform()->Rotate(vec3(-JuEngine::Math::PI / 2.f, 0.f, 0.f));

	entity->Add<JuEngine::MeshRenderer>("obj_hat", "mat_vertexLit");

	return entity;
}
}
