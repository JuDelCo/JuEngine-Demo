// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Entity/ISystem.hpp>

namespace Systems
{
class Camera : public JuEngine::IExecuteSystem, public JuEngine::ISetPoolSystem
{
	public:
		Camera() = default;

		void SetPool(JuEngine::Pool* pool);
		void Execute();

	private:
		JuEngine::Pool* mPool;
};
}
