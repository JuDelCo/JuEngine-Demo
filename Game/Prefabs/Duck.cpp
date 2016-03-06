// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Duck.hpp"
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/MeshRenderer.hpp>
#include "../Features/Duck/DuckComponent.hpp"

namespace Prefabs
{
auto Duck::Create(JuEngine::Pool* pool) -> JuEngine::EntityPtr
{
	auto entity = pool->CreateEntity();

	entity->Add<JuEngine::Transform>();
	entity->Add<JuEngine::MeshRenderer>("obj_duck", "mat_vertexLit");
	entity->Add<Components::Duck>();

	return entity;
}
}
