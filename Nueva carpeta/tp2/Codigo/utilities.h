#ifndef UTILITIES__H
#define UTILITIES__H

#include <time.h>

#include "types.h"
#include "movie.h"

char * strdup(const char * s);
status_t split(const char * s, char delim, char *** str_array, size_t * l);
status_t del_array(char *** s_array, size_t *l);

#endif