// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "LightSystem.hpp"
#include "LightComponent.hpp"
#include <JuEngine/Entity/Group.hpp>
#include <JuEngine/Entity/Pool.hpp>
#include <JuEngine/Components/Transform.hpp>

namespace Systems
{
void Light::SetPool(Pool* pool)
{
	mPool = pool;
}

void Light::Execute()
{
	float offset = 0.f;
	auto lights = mPool->GetGroup(Matcher_AllOf(Components::Light))->GetEntities();

	for(auto &light : lights)
	{
		light->Use<Transform>()->SetLocalPosition(vec3(sin(lightCounter + Math::PI * offset) * 5.f, 1.f, cos(lightCounter + Math::PI * offset) * 5.f));
		offset += 0.5f;
	}

	lightCounter += 0.01;
}
}
