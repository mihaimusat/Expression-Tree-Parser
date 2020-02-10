all: build

build: structuri.h defines.h functii.h functii.c main.c
	gcc -Wall structuri.h defines.h functii.h functii.c main.c -o tema3 -lm

run: tema3
	./tema3

clean:
	rm -rf tema3
