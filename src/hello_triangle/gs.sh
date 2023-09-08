#!/bin/bash

g++ ${1} ../glad/glad.c -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
