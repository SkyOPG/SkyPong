all:
	g++ pong.cpp icons.o -o pong.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra