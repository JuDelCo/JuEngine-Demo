// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Demo.hpp"
#include "../Features/Demo/DemoSystem.hpp"
#include "../Features/Camera/CameraSystem.hpp"
#include "../Features/Light/LightSystem.hpp"
#include "../Features/Sun/SunSystem.hpp"
#include "../Features/Duck/DuckSystem.hpp"
#include <JuEngine/Managers/PoolManager.hpp>
#include <JuEngine/Managers/PrefabManager.hpp>
#include <JuEngine/Managers/SystemManager.hpp>
#include <JuEngine/Managers/WindowManager.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/MeshRenderer.hpp>
#include <JuEngine/Components/Light.hpp>
#include <JuEngine/Components/World.hpp>
#include <JuEngine/Resources/Renderer.hpp>
#include <JuEngine/Resources/DebugLog.hpp>

	// DEBUG
	//#include <JuEngine/Components/Camera.hpp>
	//#include "../Features/Camera/CameraComponent.hpp"
	//#include "../Features/Light/LightComponent.hpp"
	//#include "../Features/Sun/SunComponent.hpp"

namespace Levels
{
void Demo::LoadAdditive()
{
	JuEngine::PoolManager::Create("pool");
	JuEngine::WindowManager::GetRenderer().get()->Register(JuEngine::PoolManager::Get("pool"));

	// ===================================
	//JuEngine::DebugLog::Write("Component ID: %u -> %s", JuEngine::ComponentTypeId::Get<JuEngine::Transform>(), "JuEngine Transform");
	//JuEngine::DebugLog::Write("Component ID: %u -> %s", JuEngine::ComponentTypeId::Get<JuEngine::MeshRenderer>(), "JuEngine MeshRenderer");
	//JuEngine::DebugLog::Write("Component ID: %u -> %s", JuEngine::ComponentTypeId::Get<JuEngine::Camera>(), "JuEngine Camera");
	//JuEngine::DebugLog::Write("Component ID: %u -> %s", JuEngine::ComponentTypeId::Get<JuEngine::Light>(), "JuEngine Light");
	//JuEngine::DebugLog::Write("Component ID: %u -> %s", JuEngine::ComponentTypeId::Get<JuEngine::World>(), "JuEngine World");
	//JuEngine::DebugLog::Write("Component ID: %u -> %s", JuEngine::ComponentTypeId::Get<Components::Camera>(), "Demo Camera");
	//JuEngine::DebugLog::Write("Component ID: %u -> %s", JuEngine::ComponentTypeId::Get<Components::Light>(), "Demo Light");
	//JuEngine::DebugLog::Write("Component ID: %u -> %s", JuEngine::ComponentTypeId::Get<Components::Sun>(), "Demo Sun");
	// ===================================

	LoadEntities();
	LoadSystems();

	JuEngine::DebugLog::Write("Demo level loaded");
}

void Demo::LoadEntities()
{
	auto pool = JuEngine::PoolManager::Get("pool");

	pool->CreateEntity()->Add<JuEngine::World>(vec3(0.211f, 0.227f, 0.258f), vec3(0.529f, 0.807f, 1.0f));

	auto camera = JuEngine::PrefabManager::Instantiate(pool, "prefab_camera");
	camera->GetTransform()->SetLocalPosition(vec3(8.61f, 2.91f, -4.02f));
	camera->GetTransform()->SetLocalEulerAngles(vec3(0.16f, -1.19f, 0.f));

	JuEngine::PrefabManager::Instantiate(pool, "prefab_grid");

	//auto worldPlane = pool->CreateEntity();
	//worldPlane->Add<JuEngine::MeshRenderer>("obj_cube", "mat_plane");
	//worldPlane->GetTransform()->Scale(vec3(0.1f, 0.1f, 0.1f));
	//worldPlane->GetTransform()->Scale(vec3(100000.f, 0.1f, 100000.f));
	//worldPlane->GetTransform()->Translate(vec3(0.f, -0.1f, 0.f));

	//auto plane = pool->CreateEntity();
	//plane->Add<JuEngine::MeshRenderer>("obj_cube", "mat_plane");
	//plane->GetTransform()->Scale(vec3(0.1f, 0.1f, 0.1f));
	//plane->GetTransform()->Scale(vec3(100.f, 0.1f, 100.f));
	//plane->GetTransform()->Translate(vec3(0.f, -0.05f, 0.f));

	auto duck_0 = JuEngine::PrefabManager::Instantiate(pool, "prefab_duck");
	auto duck_r = JuEngine::PrefabManager::Instantiate(pool, "prefab_duck");
	auto duck_g = JuEngine::PrefabManager::Instantiate(pool, "prefab_duck");
	auto duck_b = JuEngine::PrefabManager::Instantiate(pool, "prefab_duck");

	duck_0->Replace<JuEngine::MeshRenderer>("obj_duck","mat_white");
	duck_r->GetTransform()->Translate(vec3(2.f, 0.f, 0.f));
	duck_r->Replace<JuEngine::MeshRenderer>("obj_duck","mat_red");
	duck_g->GetTransform()->Translate(vec3(0.f, 2.f, 0.f));
	duck_g->Replace<JuEngine::MeshRenderer>("obj_duck","mat_green");
	duck_b->GetTransform()->Translate(vec3(0.f, 0.f, 2.f));
	duck_b->Replace<JuEngine::MeshRenderer>("obj_duck","mat_blue");

	auto hat0 = JuEngine::PrefabManager::Instantiate(pool, "prefab_hat");
	auto hat1 = JuEngine::PrefabManager::Instantiate(pool, "prefab_hat");
	auto hat2 = JuEngine::PrefabManager::Instantiate(pool, "prefab_hat");
	auto hat3 = JuEngine::PrefabManager::Instantiate(pool, "prefab_hat");

	hat0->GetTransform()->SetParent(duck_0);
	hat1->Replace<JuEngine::MeshRenderer>("obj_hat","mat_green");
	hat1->GetTransform()->SetParent(duck_r);
	hat2->Replace<JuEngine::MeshRenderer>("obj_hat","mat_blue");
	hat2->GetTransform()->SetParent(duck_g);
	hat3->Replace<JuEngine::MeshRenderer>("obj_hat","mat_red");
	hat3->GetTransform()->SetParent(duck_b);

	JuEngine::PrefabManager::Instantiate(pool, "prefab_sun");

	auto light1 = JuEngine::PrefabManager::Instantiate(pool, "prefab_light");
	auto light2 = JuEngine::PrefabManager::Instantiate(pool, "prefab_light");
	auto light3 = JuEngine::PrefabManager::Instantiate(pool, "prefab_light");
	auto light4 = JuEngine::PrefabManager::Instantiate(pool, "prefab_light");

	light1->Replace<JuEngine::Light>(vec3(1.f, 1.f, 1.f), 0.2f);
	light1->GetTransform()->Scale(vec3(0.1f, 0.1f, 0.1f));
	light2->Replace<JuEngine::Light>(vec3(1.f, 0.f, 0.f), 0.2f);
	light2->GetTransform()->Scale(vec3(0.1f, 0.1f, 0.1f));
	light3->Replace<JuEngine::Light>(vec3(0.f, 1.f, 0.f), 0.2f);
	light3->GetTransform()->Scale(vec3(0.1f, 0.1f, 0.1f));
	light4->Replace<JuEngine::Light>(vec3(0.f, 0.f, 1.f), 0.2f);
	light4->GetTransform()->Scale(vec3(0.1f, 0.1f, 0.1f));

	//auto testObj = pool->CreateEntity();
	//testObj->Add<JuEngine::MeshRenderer>("obj_test", "mat_white"); // mat_plane mat_white
	//testObj->GetTransform()->Scale(vec3(10.01f, 10.01f, 10.01f));
	//testObj->GetTransform()->Translate(vec3(0.f, 125.f, 0.f));
}

void Demo::LoadSystems()
{
	auto pool = JuEngine::PoolManager::Get("pool");

	JuEngine::SystemManager::Add(pool->CreateSystem<Systems::Demo>());
	JuEngine::SystemManager::Add(pool->CreateSystem<Systems::Camera>());
	JuEngine::SystemManager::Add(pool->CreateSystem<Systems::Light>());
	JuEngine::SystemManager::Add(pool->CreateSystem<Systems::Sun>());
	JuEngine::SystemManager::Add(pool->CreateSystem<Systems::Duck>());
}
}
