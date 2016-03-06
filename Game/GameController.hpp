// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#pragma once

#include <JuEngine/Application.hpp>

class GameController : public JuEngine::Application
{
	public:
		GameController() = default;

		void Init(const int argc, const char* argv[]);

	protected:
		void LoadAssets();
		void ConfigureInput();
};
