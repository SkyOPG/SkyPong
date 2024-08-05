#! /bin/bash

g++ src/**/*.cpp -o out/pong.exe -L./libs -I./includes -lraylib -ldiscord-rpc -Wall -Wextra