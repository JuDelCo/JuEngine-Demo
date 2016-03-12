// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Resources/Prefab.hpp>

using namespace JuEngine;

namespace Prefabs
{
class Duck : public Prefab
{
	public:
		Duck() { SetId("prefab_duck"); }
		auto Create(Pool* pool) -> EntityPtr;
};
}
