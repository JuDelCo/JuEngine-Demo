// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "LightSystem.hpp"
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>
#include <JuEngine/Components/Camera.hpp>
#include <JuEngine/Components/World.hpp>
#include <JuEngine/Managers/InputManager.hpp>
#include <JuEngine/Managers/WindowManager.hpp>
#include <JuEngine/Resources/DebugLog.hpp>
#include "LightComponent.hpp"

namespace Systems
{
void Light::SetPool(JuEngine::Pool* pool)
{
	mPool = pool;
}

void Light::Execute()
{
	float offset = 0.f;
	auto lights = mPool->GetGroup(Matcher_AllOf(Components::Light))->GetEntities();

	for(auto &light : lights)
	{
		light->UseTransform()->SetLocalPosition(vec3(sin(lightCounter + JuEngine::Math::PI * offset) * 5.f, 1.f, cos(lightCounter + JuEngine::Math::PI * offset) * 5.f));
		offset += 0.5f;
	}

	lightCounter += 0.01;
}
}
