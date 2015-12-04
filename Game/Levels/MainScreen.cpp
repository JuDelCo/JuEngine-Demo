// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "MainScreen.hpp"

namespace Levels
{
MainScreen::MainScreen()
{
	SetName("lvl_mainScreen");
}

void MainScreen::LoadAdditive()
{
	PrefabManager::Instantiate("prefab_grid");

	/*auto worldPlane = EntityManager::Create("worldPlane");
	worldPlane->CreateComponent<MeshRenderer>("obj_cube", "mat_plane");
	worldPlane->GetComponent<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));
	worldPlane->GetComponent<Transform>()->Scale(vec3(100000.0f, 0.1f, 100000.0f));
	worldPlane->GetComponent<Transform>()->Translate(vec3(0.f, -0.1f, 0.f));*/

	/*auto plane = EntityManager::Create("plane");
	plane->CreateComponent<MeshRenderer>("obj_cube", "mat_plane");
	plane->GetComponent<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));
	plane->GetComponent<Transform>()->Scale(vec3(100.0f, 0.1f, 100.0f));
	plane->GetComponent<Transform>()->Translate(vec3(0.f, -0.05f, 0.f));*/

	auto duck_0 = PrefabManager::Instantiate("prefab_duck");
	auto duck_r = PrefabManager::Instantiate("prefab_duck");
	auto duck_g = PrefabManager::Instantiate("prefab_duck");
	auto duck_b = PrefabManager::Instantiate("prefab_duck");

	duck_0->GetComponent<MeshRenderer>()->SetMaterial("mat_white");
	duck_r->GetComponent<Transform>()->Translate(vec3(2.0f, 0.0f, 0.0f));
	duck_r->GetComponent<MeshRenderer>()->SetMaterial("mat_red");
	duck_g->GetComponent<Transform>()->Translate(vec3(0.0f, 2.0f, 0.0f));
	duck_g->GetComponent<MeshRenderer>()->SetMaterial("mat_green");
	duck_b->GetComponent<Transform>()->Translate(vec3(0.0f, 0.0f, 2.0f));
	duck_b->GetComponent<MeshRenderer>()->SetMaterial("mat_blue");

	auto hat0 = PrefabManager::Instantiate("prefab_hat");
	auto hat1 = PrefabManager::Instantiate("prefab_hat");
	auto hat2 = PrefabManager::Instantiate("prefab_hat");
	auto hat3 = PrefabManager::Instantiate("prefab_hat");

	hat0->GetComponent<Transform>()->SetParent(duck_0);
	hat1->GetComponent<MeshRenderer>()->SetMaterial("mat_green");
	hat1->GetComponent<Transform>()->SetParent(duck_r);
	hat2->GetComponent<MeshRenderer>()->SetMaterial("mat_blue");
	hat2->GetComponent<Transform>()->SetParent(duck_g);
	hat3->GetComponent<MeshRenderer>()->SetMaterial("mat_red");
	hat3->GetComponent<Transform>()->SetParent(duck_b);

	auto camera = PrefabManager::Instantiate("prefab_camera");
	camera->GetComponent<Transform>()->SetLocalPosition(vec3(8.61f, 2.91f, -4.02f));
	camera->GetComponent<Transform>()->SetLocalEulerAngles(vec3(0.16f, -1.19f, 0.f));

	auto sun = EntityManager::Create("sun");
	sun->CreateComponent<Light>(vec3(1.0f, 0.956f, 0.839f), 1.0f, LightType::LIGHT_DIRECTIONAL);
	sun->CreateComponent<MeshRenderer>("obj_sphere", "mat_light");
	sun->GetComponent<Transform>()->Scale(vec3(85.0f, 85.0f, 85.1f));

	auto light1 = EntityManager::Create("light1");
	light1->CreateComponent<Light>(vec3(1.0f, 1.0f, 1.0f), 0.2f);
	light1->CreateComponent<MeshRenderer>("obj_cube", "mat_light");
	light1->GetComponent<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));

	auto light2 = EntityManager::Create("light2");
	light2->CreateComponent<Light>(vec3(1.0f, 0.f, 0.f), 0.2f);
	light2->CreateComponent<MeshRenderer>("obj_cube", "mat_light");
	light2->GetComponent<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));

	auto light3 = EntityManager::Create("light3");
	light3->CreateComponent<Light>(vec3(0.f, 1.0f, 0.f), 0.2f);
	light3->CreateComponent<MeshRenderer>("obj_cube", "mat_light");
	light3->GetComponent<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));

	auto light4 = EntityManager::Create("light4");
	light4->CreateComponent<Light>(vec3(0.f, 0.f, 1.0f), 0.2f);
	light4->CreateComponent<MeshRenderer>("obj_cube", "mat_light");
	light4->GetComponent<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));

	//auto testObj = EntityManager::Create("testObj");
	//testObj->CreateComponent<MeshRenderer>("obj_test", "mat_white"); /* mat_plane mat_white */
	//testObj->GetComponent<Transform>()->Scale(vec3(10.01f, 10.01f, 10.01f));
	//testObj->GetComponent<Transform>()->Translate(vec3(0.f, 125.0f, 0.f));

	DebugLog::Write("Mainscreen level loaded");
}
}
