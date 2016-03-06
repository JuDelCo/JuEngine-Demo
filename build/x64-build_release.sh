#!/bin/bash
# Copyright (c) 2016 Juan Delgado (JuDelCo)
# License: GPLv3 License
# GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $DIR

if [ ! -d "x64_Release" ]; then
	mkdir -p x64_Release
	cd x64_Release
	cmake ../..
	cd ..
fi

function build
{
	cd $DIR
	cd ..

	#clear
	cmake -D BUILD_CPU_ARCH:STRING=x64 -D CMAKE_BUILD_TYPE:STRING=Release -D CMAKE_INSTALL_PREFIX:PATH="" build/x64_Release/
	#clear
	cmake -L -N build/x64_Release/

	cd build/x64_Release
	make all
	make install

	read -p "Press any key to build again (or press CTRL+C to exit) ..." -n1 -s
	printf "\n"

	build
}

build
