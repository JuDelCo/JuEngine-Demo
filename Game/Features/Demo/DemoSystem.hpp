// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Entity/ISystem.hpp>

using namespace JuEngine;

namespace Systems
{
class Demo : public IInitializeSystem, public IExecuteSystem, public ISetPoolSystem
{
	public:
		Demo() = default;

		void SetPool(Pool* pool);
		void Initialize();
		void Execute();

	private:
		Pool* mPool;
};
}
