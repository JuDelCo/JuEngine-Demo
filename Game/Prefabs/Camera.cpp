// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Camera.hpp"
#include "../Scripts/Camera.hpp"
#include "../Scripts/TestUnique.hpp" // TEST

namespace Prefabs
{
CameraEditor::CameraEditor()
{
	SetName("prefab_camera");
}

auto CameraEditor::Create() -> Entity*
{
	auto entity = EntityManager::Create("camera");

	entity->CreateComponent<Camera>(); //->SetCurrent();
	entity->CreateComponent<Scripts::CameraController>();
	entity->CreateComponent<Scripts::TestUniqueScript>(); // TEST

	return entity;
}
}
