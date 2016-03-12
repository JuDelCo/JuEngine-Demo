// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/AppController.hpp>

using namespace JuEngine;

class GameController : public AppController
{
	public:
		GameController() = default;

		void Init(const int argc, const char* argv[]);

	protected:
		void LoadAssets();
		void ConfigureInput();
};
