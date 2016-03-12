// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Entity/IComponent.hpp>
#include <JuEngine/Resources/Math.hpp>

using namespace JuEngine;

namespace Components
{
struct Camera : public IComponent
{
	vec2 lastMousePoint;
	vec2 mouseDiff;

	void Reset(vec2 lastMousePoint = vec2(0.f,0.f), vec2 mouseDiff = vec2(0.f,0.f))
	{
		this->lastMousePoint = lastMousePoint;
		this->lastMousePoint = mouseDiff;
	}
};
}
