// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Entity/ISystem.hpp>
#include <JuEngine/Resources/Math.hpp>

using namespace JuEngine;

namespace Systems
{
class Duck : public IInitializeSystem, public IExecuteSystem, public ISetPoolSystem
{
	public:
		Duck() = default;

		void SetPool(Pool* pool);
		void Initialize();
		void Execute();

	private:
		Pool* mPool;

		vec2 lastMousePoint{0.f,0.f};
		vec2 mouseDiff{0.f,0.f};
		float lightCounter{0.f};
		bool interpolating{false};
		quat startOrientation;
		quat desiredOrientation;
		float startInterpolating;
};
}
