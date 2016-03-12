// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Resources/Prefab.hpp>

using namespace JuEngine;

namespace Prefabs
{
class Grid : public Prefab
{
	public:
		Grid() { SetId("prefab_grid"); }
		auto Create(Pool* pool) -> EntityPtr;
};
}
