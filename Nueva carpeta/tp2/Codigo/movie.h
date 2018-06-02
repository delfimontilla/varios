#ifndef MOVIE__H
#define MOVIE__H

#include <time.h>

typedef struct movies{
	short id;
	char * title;
	char * script;
	char * director;
	time_t date;
	double score;
	size_t reviews;
} movies_t;


#endif
