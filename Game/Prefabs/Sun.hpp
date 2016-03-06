// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Resources/Prefab.hpp>

namespace Prefabs
{
class Sun : public JuEngine::Prefab
{
	public:
		Sun() { SetId("prefab_sun"); }
		auto Create(JuEngine::Pool* pool) -> JuEngine::EntityPtr;
};
}
