// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Game/GameController.hpp"

int main(const int argc, const char* argv[])
{
	GameController app{};

	app.Init(argc, argv);
	app.Run();

	return 0;
}
