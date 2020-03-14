path : main.o robot.o map.o gui.o
		gcc main.o robot.o map.o gui.o -o path -lSDL

main.o : main.c include/header.h
		gcc -c main.c

robot.o : src/robot.c include/header.h
		gcc -c src/robot.c

map.o : src/map.c include/header.h
		gcc -c src/map.c

gui.o : src/gui.c include/header.h
		gcc -c src/gui.c

clean :
		rm *.o path
