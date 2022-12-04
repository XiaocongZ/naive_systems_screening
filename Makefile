all: main.o parse.o cJSON.o
	cc -fsanitize=address -o screen main.o parse.o cJSON.o


main.o: main.c
	cc -c -ggdb -fsanitize=address main.c -o main.o
parse.o: parse.c
	cc -c -ggdb -fsanitize=address parse.c -o parse.o # Runs second
cJSON.o: third_party/cJSON/cJSON.c
	cc -c -ggdb -fsanitize=address third_party/cJSON/cJSON.c -o cJSON.o
clean:
	rm *.o screen
