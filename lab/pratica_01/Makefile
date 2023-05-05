all: app

CC= arm-none-eabi-gcc

app: main.o
	$(CC) obj/main.o -lc -lrdimon -o bin/app

main.o: src/main.c
	$(CC) -c src/main.c -Iinc -o obj/main.o

clean:
	rm obj/*.o bin/app
