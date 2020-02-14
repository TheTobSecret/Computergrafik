#!/bin/bash

echo "Compiling"

g++ -o build/main src/main.cpp /usr/src/glad.c -lGL -lGLU -lGLEW -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -I/usr/include/GL/

echo "Starting Compiled Programm"

build/main