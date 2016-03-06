// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Resources/Prefab.hpp>

namespace Prefabs
{
class Light : public JuEngine::Prefab
{
	public:
		Light() { SetId("prefab_light"); }
		auto Create(JuEngine::Pool* pool) -> JuEngine::EntityPtr;
};
}
