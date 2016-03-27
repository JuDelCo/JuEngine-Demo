// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Demo.hpp"
#include "../Features/Demo/DemoSystem.hpp"
#include "../Features/Camera/CameraSystem.hpp"
#include "../Features/Light/LightSystem.hpp"
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

using namespace JuEngine;

namespace Levels
{
void Demo::LoadAdditive()
{
	App::Data()->Add<Pool>("pool");
	App::Window()->GetRenderer().get()->Register(App::Data()->Get<Pool>("pool"));

	LoadEntities();
	LoadSystems();

	App::Log()->Info("Demo level loaded");
}

void Demo::LoadEntities()
{
	auto pool = App::Data()->Get<Pool>("pool");

	auto world = pool->CreateEntity()->Add<World>(vec3(0.211f, 0.227f, 0.258f), vec3(0.529f, 0.807f, 1.0f));
	world->Get<World>()->SetSkyColor(vec3(0.001f, 0.001f, 0.001f));
	world->Get<World>()->SetAmbientColor(vec3(0.211f, 0.227f, 0.258f));
	world->Get<World>()->SetAmbientIntensity(0.3f);

	auto camera = App::Data()->Get<Prefab>("p_camera")->Create(pool);
	camera->Get<Transform>()->SetLocalPosition(vec3(8.61f, 2.91f, -4.02f));
	camera->Get<Transform>()->SetLocalEulerAngles(vec3(0.16f, -1.19f, 0.f));

	App::Data()->Get<Prefab>("p_grid")->Create(pool);

	auto modelTest = App::Data()->Get<Prefab>("p_modelTest")->Create(pool);
	modelTest->Get<Transform>()->SetLocalPosition(vec3(0.0f, 0.0f, 0.0f));
	modelTest->Get<Transform>()->Rotate(vec3(0.f, Math::DegToRad(90.f), 0.f));

	auto lightSun = pool->CreateEntity();
	lightSun->Add<Light>(vec3(1.f, 1.f, 1.f), 0.1f, JuEngine::LightType::LIGHT_DIRECTIONAL);
	lightSun->Add<Transform>();
	lightSun->Get<Transform>()->Rotate(vec3(Math::DegToRad(75.f), Math::DegToRad(-25.f), 0.f), true);

	auto lightPoint1 = App::Data()->Get<Prefab>("p_light")->Create(pool);
	auto lightPoint2 = App::Data()->Get<Prefab>("p_light")->Create(pool);
	auto lightPoint3 = App::Data()->Get<Prefab>("p_light")->Create(pool);
	auto lightPoint4 = App::Data()->Get<Prefab>("p_light")->Create(pool);
	lightPoint1->Replace<Light>(vec3(1.f, 1.f, 1.f), 2.0f, JuEngine::LightType::LIGHT_POINT);
	lightPoint2->Replace<Light>(vec3(1.f, 0.f, 0.f), 2.0f, JuEngine::LightType::LIGHT_POINT);
	lightPoint3->Replace<Light>(vec3(0.f, 1.f, 0.f), 2.0f, JuEngine::LightType::LIGHT_POINT);
	lightPoint4->Replace<Light>(vec3(0.f, 0.f, 1.f), 2.0f, JuEngine::LightType::LIGHT_POINT);

	auto lightSpot = pool->CreateEntity();
	lightSpot->Add<Transform>();
	lightSpot->Get<Transform>()->SetParent(camera);
	lightSpot->Add<Light>(vec3(1.f, 1.f, 1.f), 5.0f, JuEngine::LightType::LIGHT_SPOT);
	//lightSpot->Get<Light>()->SetLinearAttenuation(0.22f);
	//lightSpot->Get<Light>()->SetQuadraticAttenuation(0.20f);
	//lightSpot->Get<Light>()->SetSpotCutOff();
	//lightSpot->Get<Light>()->SetSpotOuterCutOff();
}

void Demo::LoadSystems()
{
	auto pool = App::Data()->Get<Pool>("pool");

	App::System()->Add(pool->CreateSystem<Systems::Demo>());
	App::System()->Add(pool->CreateSystem<Systems::Camera>());
	App::System()->Add(pool->CreateSystem<Systems::Light>());
}
}
