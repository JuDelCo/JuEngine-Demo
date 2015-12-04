#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $DIR

if [ ! -d "x64_Debug" ]; then
	mkdir -p x64_Debug
	cd x64_Debug
	cmake ../..
	cd ..
fi

function build
{
	cd $DIR
	cd ..

	#clear
	cmake -D BUILD_CPU_ARCH:STRING=x64 -D CMAKE_BUILD_TYPE:STRING=Debug -D CMAKE_INSTALL_PREFIX:PATH="" build/x64_Debug/
	#clear
	cmake -L -N build/x64_Debug/

	cd build/x64_Debug
	make all
	#make install > /dev/null

	read -p "Press any key to build again (or press CTRL+C to exit) ..." -n1 -s
	printf "\n"

	build
}

build
