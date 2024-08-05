all:
	g++ src/**/*.cpp src/**/**/**/*.cpp src/**/**/*.cpp -o out/pong -L./libs -I./includes -lraylib -ldiscord-rpc -Wall -Wextra