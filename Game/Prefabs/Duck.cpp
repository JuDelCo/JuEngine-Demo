// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Duck.hpp"
#include "../Scripts/TestMultiple.hpp"

namespace Prefabs
{
Duck::Duck()
{
	SetName("prefab_duck");
}

auto Duck::Create() -> Entity*
{
	auto entity = EntityManager::Create("duck");

	entity->CreateComponent<MeshRenderer>("obj_duck", "mat_vertexLit");
	entity->CreateComponent<Scripts::TestMultipleScript>();

	return entity;
}
}
