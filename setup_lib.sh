#!/bin/bash

OS_MAC="$(uname)"
OS_ARCH="$(uname -r)"

if [[ -d ./lib/MLX42 ]]; then
	echo "\033[1;33m./lib/MLX42/ Exists\033[0m";
else
{
	git clone https://github.com/codam-coding-college/MLX42.git 
	mv MLX42 ./lib
	if [[ $OS_MAC == 'Darwin' ]]; then
		echo "Installing GLFW"
		curl -LO https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.bin.MACOS.zip
		unzip glfw-3.3.8.bin.MACOS.zip
		rm glfw-3.3.8.bin.MACOS.zip
		mv glfw-3.3.8.bin.MACOS/lib-universal glfw-3.3.8.bin.MACOS/glfw_lib
		mv glfw-3.3.8.bin.MACOS/glfw_lib ./lib/MLX42/
		rm -rf glfw-3.3.8.bin.MACOS
	fi
	if [[ $OS_ARCH == *'arch'* ]]; then
		echo "Installing glfw-x11"
		if pacman -Qs glfw-x11 >/dev/null; then
			echo "glfw-x11 is already installed"
		else
			sudo pacman -S glfw-x11
		fi
	fi
	cd lib/MLX42
	cmake -B build
	cmake --build build -j4;
}
fi