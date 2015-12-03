// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Grid.hpp"
#include "../Scripts/TestMultiple.hpp"

namespace Prefabs
{
Grid::Grid()
{
	SetName("prefab_grid");
}

auto Grid::Create() -> Entity*
{
	auto entity = EntityManager::Create("grid");

	entity->CreateComponent<MeshRenderer>("obj_grid", "mat_vertexColor");

	return entity;
}
}
