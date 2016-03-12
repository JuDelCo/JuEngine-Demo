// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Game/GameController.hpp"
//#include "Tests/Bandit/bandit.h"

int main(const int argc, const char* argv[])
{
	/*if(true) // RunTests (WIP)
	{
		char const* arguments[] = {"JuEngine_Game", "--reporter=spec"};
		return bandit::run(2, (char**)arguments);
	}*/

	GameController* app = new GameController();

	char const* arguments[] = {"JuEngine_Game", "--noconsole"};
	app->Init(2, arguments);
	app->Run();

	delete app;

	return 0;
}
