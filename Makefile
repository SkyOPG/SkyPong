all:
	g++ src/packages/discordinit.cpp src/gameFiles/gameScreens/vsplayer.cpp src/gameFiles/gameScreens/common.cpp src/packages/tstk.cpp src/assets/icons.o src/gameFiles/pong.cpp -o Pong/pong.exe -L./libs -I./includes -lraylib -lopengl32 -ldiscord-rpc -lgdi32 -lwinmm
release:
	g++ src/packages/discordinit.cpp src/gameFiles/gameScreens/vsplayer.cpp src/gameFiles/gameScreens/common.cpp src/packages/tstk.cpp src/assets/icons.o src/gameFiles/pong.cpp -o out/pong.exe -L./libs -I./includes -lraylib -lopengl32 -ldiscord-rpc -lgdi32 -lwinmm -Wall -Wextra -mwindows