// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Includes.hpp>

namespace Prefabs
{
class Grid : public Prefab
{
public:
	Grid();
	~Grid() = default;

	auto Create() -> Entity*;
};
}
