all:
	g++ pong.cpp icons.o -o virus.exe -LC:/mingw_dev_lib/raylib/lib -IC:/mingw_dev_lib/raylib/include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
