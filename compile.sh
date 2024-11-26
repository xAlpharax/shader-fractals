#!/bin/bash

gcc mandelbrot.c -o mandelbrot -lGL -lGLEW -lglfw -O3 -march=native -ffast-math

gcc julia.c -o julia -lGL -lGLEW -lglfw -O3 -march=native -ffast-math
