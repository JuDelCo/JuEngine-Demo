#!/bin/bash
# Copyright (c) 2016 Juan Delgado (JuDelCo)
# License: GPLv3 License
# GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

function run
{
	clear
	./Game_Debug_x64 --noconsole

	read -p "Press any key to run again (or press CTRL+C to exit) ..." -n1 -s
	printf "\n"

	run
}

run
