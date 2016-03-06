// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Resources/Prefab.hpp>

namespace Prefabs
{
class Hat : public JuEngine::Prefab
{
	public:
		Hat() { SetId("prefab_hat"); }
		auto Create(JuEngine::Pool* pool) -> JuEngine::EntityPtr;
};
}
