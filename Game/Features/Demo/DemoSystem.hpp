// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Entity/ISystem.hpp>

namespace Systems
{
class Demo : public JuEngine::IInitializeSystem, public JuEngine::IExecuteSystem, public JuEngine::ISetPoolSystem
{
	public:
		Demo() = default;

		void SetPool(JuEngine::Pool* pool);
		void Initialize();
		void Execute();

	private:
		JuEngine::Pool* mPool;
};
}
