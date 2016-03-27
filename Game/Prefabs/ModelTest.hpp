// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Resources/Prefab.hpp>

using namespace JuEngine;

namespace Prefabs
{
class ModelTest : public Prefab
{
	public:
		ModelTest() { SetId("prefab_modelTest"); }
		auto Create(Pool* pool) -> EntityPtr;
};
}
