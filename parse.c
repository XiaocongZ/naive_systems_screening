#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parse.h"
/*
only allocate mem for params
key value are in place(in truncated part of url)
TODO free mem
*/
int
parse_query_string(char* url, struct query_parameter** out)
{
	/* TODO */
	*out = NULL; //so that realloc works
	int parameter_count = 0;
	char *query_string, *question_mark;

	question_mark = strchr(url, '?');


	//No query_string, no '?'
	if(question_mark == NULL){
		printf("Has no '?'; No parameters\n");
		return parameter_count;
	}
	else{
		//modify url here
		query_string = question_mark + 1;
		*question_mark = '\0';
	}
	//query_string is not empty
	while(query_string[0] != '\0'){
		char *query_k, *query_v, *equal_sign;
		char *ep;
		ep = strchr(query_string, '&');
		if(ep == NULL){
			ep = strchr(query_string, '\0');
		}

		equal_sign = strchr(query_string, '=');
		if(equal_sign == NULL){
			goto error;
		}
		else{
			query_k = query_string;
			query_v = equal_sign + 1;
			*equal_sign = '\0';
			//realloc query_parameter and store query key value
			*out = realloc(*out, (parameter_count + 1)* sizeof(struct query_parameter));
			struct query_parameter *query = *out + parameter_count;
			query->name = query_k;
			query->value = query_v;
			printf("name %s value %s\n", query_k, query_v);
			parameter_count++;
		}
		if(*ep == '&'){
			query_string = ep + 1;
			*ep = '\0';
		}else{
			query_string = ep;
		}
	}

	return parameter_count;

error:
	printf("ERROR: \n");
	return parameter_count;
}
