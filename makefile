path : main.o robot.o map.o gui.o
		gcc main.o robot.o map.o gui.o -o path -lSDL

main.o : main.c header.h
		gcc -c main.c

robot.o : robot.c header.h
		gcc -c robot.c

map.o : map.c header.h
		gcc -c map.c

gui.o : gui.c header.h
		gcc -c gui.c

clean :
		rm *.o path
