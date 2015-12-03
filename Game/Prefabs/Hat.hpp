// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Includes.hpp>

namespace Prefabs
{
class Hat : public Prefab
{
public:
	Hat();
	~Hat() = default;

	auto Create() -> Entity*;
};
}
