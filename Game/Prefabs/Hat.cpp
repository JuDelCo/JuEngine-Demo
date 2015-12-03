// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Hat.hpp"

namespace Prefabs
{
Hat::Hat()
{
	SetName("prefab_hat");
}

auto Hat::Create() -> Entity*
{
	auto entity = EntityManager::Create("hat");

	// TODO: Arreglar desviación (de orientación) en Blender !
	entity->GetComponent<Transform>()->Rotate(vec3(-Math::PI / 2.0f, 0.f, 0.f));
	entity->GetComponent<Transform>()->Translate(vec3(0.f, 0.02f, 0.01f));
	entity->CreateComponent<MeshRenderer>("obj_hat", "mat_vertexLit");

	return entity;
}
}
