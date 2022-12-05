all: main.o parse.o cJSON.o main_asan.o parse_asan.o cJSON_asan.o
	cc -o screen main.o parse.o cJSON.o
	cc -fsanitize=address -o screen_asan main_asan.o parse_asan.o cJSON_asan.o


main.o: main.c
	cc -g -c  main.c -o main.o
	cc -g -fsanitize=address -c  main.c -o main_asan.o
parse.o: parse.c
	cc -g -c parse.c -o parse.o
	cc -g -fsanitize=address -c parse.c -o parse_asan.o
cJSON.o: third_party/cJSON/cJSON.c
	cc -g -c third_party/cJSON/cJSON.c -o cJSON.o
	cc -g -fsanitize=address -c third_party/cJSON/cJSON.c -o cJSON_asan.o
clean:
	rm *.o screen screen_asan
