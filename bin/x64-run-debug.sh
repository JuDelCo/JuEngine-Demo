#!/bin/bash

function run
{
	clear
	./Game_Debug_x64 --noconsole

	read -p "Press any key to run again (or press CTRL+C to exit) ..." -n1 -s
	printf "\n"

	run
}

run
