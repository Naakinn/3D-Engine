app: main.o render.o input.o sdl.o 
	gcc bin/main.o bin/render.o bin/input.o bin/sdl.o -lm `sdl2-config --cflags --libs`

main.o : main.c
	gcc -c -o bin/main.o -I include main.c
render.o : render.c
	gcc -c -o bin/render.o -I include render.c
input.o : input.c
	gcc -c -o bin/input.o -I include input.c
sdl.o : sdl.c
	gcc -c -o bin/sdl.o -I include sdl.c
	
clean: 
	rm a.out bin/* 
