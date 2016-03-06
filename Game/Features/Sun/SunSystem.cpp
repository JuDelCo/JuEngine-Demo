// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "SunSystem.hpp"
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/Camera.hpp>
#include <JuEngine/Components/Light.hpp>
#include <JuEngine/Components/World.hpp>
#include <JuEngine/Managers/InputManager.hpp>
#include <JuEngine/Managers/WindowManager.hpp>
#include <JuEngine/Resources/DebugLog.hpp>
#include "SunComponent.hpp"

namespace Systems
{
void Sun::SetPool(JuEngine::Pool* pool)
{
	mPool = pool;
}

void Sun::Execute()
{
	auto sun = mPool->GetGroup(Matcher_AllOf(Components::Sun))->GetSingleEntity();
	auto world = mPool->GetGroup(Matcher_AllOf(JuEngine::World))->GetSingleEntity()->Get<JuEngine::World>();

	float sunForce = JuEngine::Math::Clamp(JuEngine::Math::Clamp((float)cos(sunCounter * sunVel)) * 3.f, 0.f, 1.f);
	sun->GetTransform()->SetLocalPosition(vec3(-sin(sunCounter * sunVel) * 4500.f, cos(sunCounter * sunVel) * 4500.f, 0.f));
	sun->Get<JuEngine::Light>()->SetIntensity(sunForce * 1.f);
	world->SetAmbientIntensity(sunForce * 0.1f);
	world->SetSkyColor(vec3(0.529f, 0.807f, 1.f) * sunForce);
	world->SetLightAttenuation(0.1f + 0.9f * sunForce);

	sunCounter += 0.01;
}
}
