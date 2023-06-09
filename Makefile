all:
	g++ pong.cpp icons.o -o Pong/pong.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
	g++ io.cpp icons.o -o Pong/data/io.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
	g++ test.cpp icons.o -o Pong/data/test.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
	g++ logic.cpp icons.o -o Pong/data/logic.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
release:
	g++ pong.cpp icons.o -o Pong/pong.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
test:
	g++ test.cpp icons.o -o Pong/data/test.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
logic:
	g++ logic.cpp icons.o -o Pong/data/logic.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
io:
	g++ io.cpp icons.o -o Pong/data/io.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra