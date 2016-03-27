// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Grid.hpp"
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/MeshRenderer.hpp>

namespace Prefabs
{
auto Grid::Create(Pool* pool) -> EntityPtr
{
	auto entity = pool->CreateEntity();

	entity->Add<Transform>();
	entity->Add<MeshRenderer>("obj_grid", "shader_vertexColor");

	return entity;
}
}
