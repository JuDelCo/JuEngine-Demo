// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Includes.hpp>

namespace Levels
{
class MainScreen : public Level
{
public:
	MainScreen();
	~MainScreen() = default;

	void LoadAdditive();
};
}
