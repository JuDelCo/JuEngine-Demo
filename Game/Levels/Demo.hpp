// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Resources/Level.hpp>

namespace Levels
{
class Demo : public JuEngine::Level
{
	public:
		Demo() { SetId("lvl_demo"); }
		void LoadAdditive();

		void LoadEntities();
		void LoadSystems();
};
}
