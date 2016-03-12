// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Demo.hpp"
#include "../Features/Demo/DemoSystem.hpp"
#include "../Features/Camera/CameraSystem.hpp"
#include "../Features/Light/LightSystem.hpp"
#include "../Features/Sun/SunSystem.hpp"
#include "../Features/Duck/DuckSystem.hpp"
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/MeshRenderer.hpp>
#include <JuEngine/Components/Light.hpp>
#include <JuEngine/Components/World.hpp>
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Resources/Prefab.hpp>
#include <JuEngine/Resources/Renderer.hpp>
#include <JuEngine/App.hpp>
#include <JuEngine/Services/IDataService.hpp>
#include <JuEngine/Services/ISystemService.hpp>
#include <JuEngine/Services/IWindowService.hpp>

// DEBUG
//#include <JuEngine/Components/Camera.hpp>
//#include "../Features/Camera/CameraComponent.hpp"
//#include "../Features/Light/LightComponent.hpp"
//#include "../Features/Sun/SunComponent.hpp"

using namespace JuEngine;

namespace Levels
{
void Demo::LoadAdditive()
{
	App::Data()->Add<Pool>("pool");
	App::Window()->GetRenderer().get()->Register(App::Data()->Get<Pool>("pool"));

	// ===================================
	//App::Log()->Debug("Component ID: %u -> %s", ComponentTypeId::Get<Transform>(), "JuEngine Transform");
	//App::Log()->Debug("Component ID: %u -> %s", ComponentTypeId::Get<MeshRenderer>(), "JuEngine MeshRenderer");
	//App::Log()->Debug("Component ID: %u -> %s", ComponentTypeId::Get<Camera>(), "JuEngine Camera");
	//App::Log()->Debug("Component ID: %u -> %s", ComponentTypeId::Get<Light>(), "JuEngine Light");
	//App::Log()->Debug("Component ID: %u -> %s", ComponentTypeId::Get<World>(), "JuEngine World");
	//App::Log()->Debug("Component ID: %u -> %s", ComponentTypeId::Get<Components::Camera>(), "Demo Camera");
	//App::Log()->Debug("Component ID: %u -> %s", ComponentTypeId::Get<Components::Light>(), "Demo Light");
	//App::Log()->Debug("Component ID: %u -> %s", ComponentTypeId::Get<Components::Sun>(), "Demo Sun");
	// ===================================

	LoadEntities();
	LoadSystems();

	App::Log()->Info("Demo level loaded");
}

void Demo::LoadEntities()
{
	auto pool = App::Data()->Get<Pool>("pool");

	pool->CreateEntity()->Add<World>(vec3(0.211f, 0.227f, 0.258f), vec3(0.529f, 0.807f, 1.0f));

	auto camera = App::Data()->Get<Prefab>("camera")->Create(pool);
	camera->Get<Transform>()->SetLocalPosition(vec3(8.61f, 2.91f, -4.02f));
	camera->Get<Transform>()->SetLocalEulerAngles(vec3(0.16f, -1.19f, 0.f));

	App::Data()->Get<Prefab>("grid")->Create(pool);

	//auto worldPlane = pool->CreateEntity();
	//worldPlane->Add<MeshRenderer>("obj_cube", "mat_plane");
	//worldPlane->Get<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));
	//worldPlane->Get<Transform>()->Scale(vec3(100000.f, 0.1f, 100000.f));
	//worldPlane->Get<Transform>()->Translate(vec3(0.f, -0.1f, 0.f));

	//auto plane = pool->CreateEntity();
	//plane->Add<MeshRenderer>("obj_cube", "mat_plane");
	//plane->Get<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));
	//plane->Get<Transform>()->Scale(vec3(100.f, 0.1f, 100.f));
	//plane->Get<Transform>()->Translate(vec3(0.f, -0.05f, 0.f));

	auto duck_0 = App::Data()->Get<Prefab>("duck")->Create(pool);
	auto duck_r = App::Data()->Get<Prefab>("duck")->Create(pool);
	auto duck_g = App::Data()->Get<Prefab>("duck")->Create(pool);
	auto duck_b = App::Data()->Get<Prefab>("duck")->Create(pool);

	duck_0->Replace<MeshRenderer>("obj_duck","mat_white");
	duck_r->Get<Transform>()->Translate(vec3(2.f, 0.f, 0.f));
	duck_r->Replace<MeshRenderer>("obj_duck","mat_red");
	duck_g->Get<Transform>()->Translate(vec3(0.f, 2.f, 0.f));
	duck_g->Replace<MeshRenderer>("obj_duck","mat_green");
	duck_b->Get<Transform>()->Translate(vec3(0.f, 0.f, 2.f));
	duck_b->Replace<MeshRenderer>("obj_duck","mat_blue");

	auto hat0 = App::Data()->Get<Prefab>("hat")->Create(pool);
	auto hat1 = App::Data()->Get<Prefab>("hat")->Create(pool);
	auto hat2 = App::Data()->Get<Prefab>("hat")->Create(pool);
	auto hat3 = App::Data()->Get<Prefab>("hat")->Create(pool);

	hat0->Get<Transform>()->SetParent(duck_0);
	hat1->Replace<MeshRenderer>("obj_hat","mat_green");
	hat1->Get<Transform>()->SetParent(duck_r);
	hat2->Replace<MeshRenderer>("obj_hat","mat_blue");
	hat2->Get<Transform>()->SetParent(duck_g);
	hat3->Replace<MeshRenderer>("obj_hat","mat_red");
	hat3->Get<Transform>()->SetParent(duck_b);

	App::Data()->Get<Prefab>("sun")->Create(pool);

	auto light1 = App::Data()->Get<Prefab>("light")->Create(pool);
	auto light2 = App::Data()->Get<Prefab>("light")->Create(pool);
	auto light3 = App::Data()->Get<Prefab>("light")->Create(pool);
	auto light4 = App::Data()->Get<Prefab>("light")->Create(pool);

	light1->Replace<Light>(vec3(1.f, 1.f, 1.f), 0.2f);
	light1->Get<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));
	light2->Replace<Light>(vec3(1.f, 0.f, 0.f), 0.2f);
	light2->Get<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));
	light3->Replace<Light>(vec3(0.f, 1.f, 0.f), 0.2f);
	light3->Get<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));
	light4->Replace<Light>(vec3(0.f, 0.f, 1.f), 0.2f);
	light4->Get<Transform>()->Scale(vec3(0.1f, 0.1f, 0.1f));

	//auto testObj = pool->CreateEntity();
	//testObj->Add<MeshRenderer>("obj_test", "mat_white"); // mat_plane mat_white
	//testObj->Get<Transform>()->Scale(vec3(10.01f, 10.01f, 10.01f));
	//testObj->Get<Transform>()->Translate(vec3(0.f, 125.f, 0.f));
}

void Demo::LoadSystems()
{
	auto pool = App::Data()->Get<Pool>("pool");

	App::System()->Add(pool->CreateSystem<Systems::Demo>());
	App::System()->Add(pool->CreateSystem<Systems::Camera>());
	App::System()->Add(pool->CreateSystem<Systems::Light>());
	App::System()->Add(pool->CreateSystem<Systems::Sun>());
	App::System()->Add(pool->CreateSystem<Systems::Duck>());
}
}
