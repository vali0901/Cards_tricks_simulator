build: main.o functions.o utils.o list_fct.o
	gcc -o tema1 main.o functions.o utils.o list_fct.o -Wall -Wextra -std=c99

main.o: main.c
	gcc -c main.c

functions.o: functions.c
	gcc -c functions.c

utils.o: utils.c
	gcc -c utils.c

list_fct.o: list_fct.c
	gcc -c list_fct.c

clean:
	rm tema1
	rm *.o
