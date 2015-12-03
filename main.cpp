// Copyright (c) 2015 Juan Delgado (JuDelCo)
// License: GPLv3 License
// GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

#include "Game/GamePong.hpp"

int main(const int argc, const char* args[])
{
	GamePong app{};

	app.Init();
	app.Run();

	return 0;
}
