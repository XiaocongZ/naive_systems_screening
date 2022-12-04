all: main.o parse.o cJSON.o
	cc -o screen main.o parse.o cJSON.o


main.o: main.c
	cc -c -ggdb main.c -o main.o
parse.o: parse.c
	cc -c -ggdb parse.c -o parse.o # Runs second
cJSON.o: third_party/cJSON/cJSON.c
	cc -c -ggdb third_party/cJSON/cJSON.c -o cJSON.o
clean:
	rm *.o screen
