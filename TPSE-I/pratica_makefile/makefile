all: velha

velha: main.o velha.o
	gcc -o jogo_da_velha main.o velha.o

#main.o: main.c
#	gcc main.c -I. -c -o main.o

#velha.o: velha.c
#	gcc velha.c -I. -c -o velha.o

run:
	./jogo_da_velha

clean:
	rm -rf *.o
