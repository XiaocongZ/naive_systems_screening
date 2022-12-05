#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parse.h"

int check_url(char *url){
	char *p;
	if(strchr(url, ' ') != NULL){
		//url contains space, error
		return -1;
	}

	p = strchr(url, '?');
	if(p == NULL){
		//valid url with no query string
		return 0;
	}else if(strchr(p+1, '?') != NULL){
		//more than one '?', error
		return -1;
	}


}



/*
only allocate mem for params
key value are in place(in truncated part of url)
Currently, anchors, i.e. things after "#", that are after query string are discarded. urls with no query string are unaffected.
*/
int
parse_query_string(char* url, struct query_parameter** out)
{
	// TODO free strdup
	char *urldup = strdup(url);

	*out = NULL; //so that realloc works
	int parameter_count = 0;
	char *query_string, *question_mark;

	int res = check_url(url);
	if (res == -1){
		free(urldup);
		return parameter_count;
	}else if (res == 0){
		free(urldup);
		return parameter_count;
	}

	//if res == 1, has one '?'
	question_mark = strchr(url, '?');
	query_string = question_mark + 1;
	*question_mark = '\0';
	char *anchor = strchr(query_string, '#');
	if (anchor != NULL){
		*anchor = '\0';
	}


	//while query_string is not empty
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
			parameter_count++;
			//if query_v contains '=', error
			if(strchr(query_v, '&') == NULL){
				if(strchr(query_v, '=') != NULL){
					goto error;
				}
			}else if (strchr(query_v, '=') != NULL && strchr(query_v, '=') < strchr(query_v, '&')){
				goto error;
			}
		}
		if(*ep == '&'){
			query_string = ep + 1;
			*ep = '\0';
		}else{
			query_string = ep;
		}
	}
	free(urldup);
	return parameter_count;

error:
	//restore url, clean query parameters, free urldup
	strcpy(url, urldup);
	free(urldup);
	free(*out);
	*out = NULL;
	parameter_count = 0;
	return parameter_count;
}
