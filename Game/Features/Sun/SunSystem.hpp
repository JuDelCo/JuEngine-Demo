// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Entity/ISystem.hpp>

using namespace JuEngine;

namespace Systems
{
class Sun : public IExecuteSystem, public ISetPoolSystem
{
	public:
		Sun() = default;

		void SetPool(Pool* pool);
		void Execute();

	private:
		Pool* mPool;

		float sunCounter{0.f};
		float sunVel{0.1f};
};
}
