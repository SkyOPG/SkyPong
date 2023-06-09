all:
	g++ src/packages/discordinit.cpp src/gameFiles/gameScreens/vsplayer.cpp src/gameFiles/gameScreens/common.cpp src/packages/tstk.cpp src/assets/icons.o src/gameFiles/pong.cpp -o Pong/pong.exe -L./lib -I./include -lraylib -lopengl32 -ldiscord-rpc -lgdi32 -lwinmm
release:
	g++ pong.cpp icons.o -o Pong/pong.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
test:
	g++ test.cpp icons.o -o Pong/data/test.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
logic:
	g++ logic.cpp icons.o -o Pong/data/logic.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
io:
	g++ io.cpp icons.o -o Pong/data/io.exe -L./lib -I./include -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra
installer:
	g++ -o pong.exe installer.cpp -lcurl -lz
net:
	g++ internet.cpp -I./include -L./lib -lwinmm -lws2_32 -o client.exe
	g++ server/internet.cpp -fpermissive -I./include -L./lib -lwinmm -lws2_32 -o host.exe