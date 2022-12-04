all: main.o parse.o cJSON.o
	cc -fsanitize=address -o screen main.o parse.o cJSON.o


main.o: main.c
	cc -g -fsanitize=address -c  main.c -o main.o
parse.o: parse.c
	cc -g -fsanitize=address -c parse.c -o parse.o # Runs second
cJSON.o: third_party/cJSON/cJSON.c
	cc -g -fsanitize=address -c third_party/cJSON/cJSON.c -o cJSON.o
clean:
	rm *.o screen
