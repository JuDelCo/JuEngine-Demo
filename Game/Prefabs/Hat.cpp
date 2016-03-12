// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Hat.hpp"
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/MeshRenderer.hpp>

namespace Prefabs
{
auto Hat::Create(Pool* pool) -> EntityPtr
{
	auto entity = pool->CreateEntity();

	entity->Add<Transform>();
	// TODO: Fix orientation in Blender !
	entity->Get<Transform>()->Rotate(vec3(-Math::PI / 2.f, 0.f, 0.f));

	entity->Add<MeshRenderer>("obj_hat", "mat_vertexLit");

	return entity;
}
}
