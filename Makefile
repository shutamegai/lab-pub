# Makefile

file = test

.PHONY: check-syntax
check-syntax:
	gcc -Wall -fsyntax-only $(CHK_SOURCES)

main_gcc: $(file)/main.c $(file)/fractal.c $(file)/init.c $(file)/iteration.c $(file)/return.c
		gcc -O3 -fopenmp -Wall -o bin/main.out \
	$(file)/main.c $(file)/fractal.c $(file)/init.c $(file)/iteration.c $(file)/return.c -lm

main_icc: $(file)/main.c $(file)/fractal.c $(file)/init.c $(file)/iteration.c $(file)/return.c
		icc -qopenmp -Wall -fast -o bin/main.out \
	$(file)/main.c $(file)/fractal.c $(file)/init.c $(file)/iteration.c $(file)/return.c
