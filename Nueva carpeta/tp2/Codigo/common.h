#ifndef COMMON__H
#define COMMON__H

#include "types.h"
#include "movie.h"
#include <time.h>
#include <stdio.h> 

#define MAX_STR 110
#define MAX_DATE 9

status_t print_lines(char * argv[], FILE * fi);
status_t handle_error(status_t status);
/*status_t char_to_structtm(char * csv_date_field, struct tm * date);*/
struct tm* transform_date (struct tm * fecha, char * csv_fields, char ** endptr);
status_t tm_asign(long auxint, struct tm * aux_field, size_t field_counter);
status_t del_movies_array(movies_t ** movies, size_t * n);
status_t read_movie(FILE *stream, movies_t *movie);
status_t print_movie(FILE* stream, const movies_t movie);
status_t write_movie(FILE* stream, movies_t movie);

#endif