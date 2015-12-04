// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Includes.hpp>

class GamePong : public Application
{
public:
	GamePong() = default;
	~GamePong() = default;

	void Init(const int argc, const char* argv[]);
};
