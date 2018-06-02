#include "functions.h"

status_t del_array(char ***s_array, size_t *l){
	size_t i;

	if( !s_array || !l ){
		return ST_ERROR_NULL_POINTER;
	}

	for( i = 0; i < *l; i++){
		free((*s_array)[i]);
		(*s_array)[i] = NULL;
	}

	free(*s_array);
	*s_array = NULL;
	*l = 0;

	return ST_OK;
}

char* strdup(const char *s){
	char *s2;

	s2 = malloc((strlen(s) +1));
	strcpy(s2, s);

	return s2;
}

status_t del_movies_array(movies_t **movies, size_t *n){

	if(!movies || !n){
		return ST_ERROR_NULL_POINTER;
	}

	free(*movies);
	*movies = NULL;
	*n = 0;

	return ST_OK;
}

status_t handle_error(status_t status){

	switch(status){
		case ST_ERROR_NO_MEMORY:
			fprintf(stdout, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_NO_MEMORY);
			break;

		case ST_ERROR_NULL_POINTER:
			fprintf(stdout, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_NULL_POINTER);
			break;

		case ST_ERROR_OPEN_FILE:
			fprintf(stdout, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_OPEN_FILE);
			break;

		case ST_ERROR_INVALID_ARG:
			fprintf(stdout, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_INVALID_ARG);
			break;

		case ST_ERROR_INVALID_DATA:
			fprintf(stdout, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_INVALID_DATA);
			break;

		case ST_ERROR_INVALID_READ:
			fprintf(stdout, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_INVALID_READ);
			break;

		case ST_ERROR_INVALID_WRITE:
			fprintf(stdout, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_INVALID_WRITE);
			break;

		case ST_ERROR_INVALID_PRINT:
			fprintf(stdout, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_INVALID_PRINT);
			break;

		default:
			break;
	}
	return ST_OK;
}

status_t split(const char *s, char delim, char ***str_array, size_t *l){
	char **string;
	size_t n, i;
	char *field, *line;
	char *aux;
	char sdelim[2];

	if(!s || !str_array || !l){
		 return ST_ERROR_NULL_POINTER;
	}

	for( n = 1, i = 0; s[i]; i++){
		if(s[i] == delim){
			 n++;
		}
	}

	if((string = (char **)malloc(n * sizeof(char *))) == NULL){
		 return ST_ERROR_NO_MEMORY;
	}

	if((line = strdup(s)) == NULL){
		free(string);
		return ST_ERROR_NO_MEMORY;
	}

	sdelim[0] = delim;
	sdelim[1] = '\0';

	aux = line;
	field = strtok(aux, sdelim);
	for(i = 0; field != NULL; i++){
		if((string[i] = strdup(field)) == NULL){
			free(line);
			del_array(&string, &i);
			*str_array = NULL;
			*l = 0;
			return ST_ERROR_NO_MEMORY;
		}
		field = strtok(NULL, sdelim);
	}

	free(line);
	*l = n;
	*str_array = string;

	return ST_OK;
}

struct tm* transform_date (struct tm * fecha, char * csv_fields, char ** endptr){

	char day[LONG_DAY+1], month[LONG_MONTH+1], year[LONG_YEAR+1];

	if( !fecha || !csv_fields || !endptr)
		return NULL;

	strncpy(day, csv_fields + POS_DAY, LONG_DAY);
	day[LONG_DAY] = '\0';
	fecha->tm_mday = strtol(day, endptr, 10);
	strncpy(month, csv_fields + POS_MONTH, LONG_MONTH);
	month[LONG_MONTH] = '\0';
	fecha->tm_mon = strtol(month, endptr, 10) -1;
	strncpy(year, csv_fields + POS_YEAR, LONG_YEAR);
	year[LONG_YEAR] = '\0';
	fecha->tm_year = strtol(year, endptr, 10) - 1900;
	fecha->tm_sec = 0;
	fecha->tm_min = 0;
	fecha->tm_hour = 0;
	fecha->tm_wday = 0;
	fecha->tm_yday = 0;
	fecha->tm_isdst = 0;

	return fecha;
}

status_t read_movie(FILE *stream, movies_t *movie){
	char aux_char, aux_impresion;
	size_t n;

	/* id*/
    if((fread(&(movie->id), sizeof(int), 1, stream)) != 1){
        return ST_ERROR_INVALID_READ;
    }

    /* largo*/
    if((fread(&aux_char, sizeof(size_t), 1, stream)) != 1){
        return ST_ERROR_INVALID_READ;
    }
    aux_impresion = (size_t)aux_char;

    /* titulo*/
    if((movie->title = (char*)malloc(sizeof(char)*aux_impresion)) == NULL){
        return ST_ERROR_NO_MEMORY;
    }

    for(n = 0; n < aux_impresion; n++){
        if((fread(&aux_char, sizeof(char), 1, stream)) != 1){
        	free(movie->title);
            return ST_ERROR_INVALID_READ;
        }

    (movie->title)[n] = aux_char;
    }

    /*largo*/
    if((fread(&aux_char, sizeof(size_t), 1, stream)) != 1){
    	free(movie->title);
        return ST_ERROR_INVALID_READ;
    }
    aux_impresion = (size_t)aux_char;

    /*script*/
    if((movie->script = (char*)malloc(sizeof(char)*aux_impresion)) == NULL){
    	free(movie->title);
        return ST_ERROR_NO_MEMORY;
    }

    for(n = 0; n < aux_impresion; n++){
        if((fread(&aux_char, sizeof(char), 1, stream)) !=1 ){
        	free(movie->title);
        	free(movie->script);
            return ST_ERROR_INVALID_READ;
        }

        (movie->script)[n] = aux_char;
    }

    /*largo*/
    if((fread(&aux_char, sizeof(size_t), 1, stream)) != 1){
    	free(movie->title);
        free(movie->script);
        return ST_ERROR_INVALID_READ;
    }
    aux_impresion = (size_t)aux_char;

    /*director*/
    if((movie->director = (char*)malloc(sizeof(char)*aux_impresion)) == NULL){
    	free(movie->title);
        free(movie->script);
        return ST_ERROR_NO_MEMORY;
    }

    for(n = 0; n < aux_impresion; n++){
        if((fread(&aux_char, sizeof(char), 1, stream)) != 1){
        	free(movie->title);
        	free(movie->script);
        	free(movie->director);
            return ST_ERROR_INVALID_READ;
        }
        (movie->director)[n] = aux_char;
    }

    /*Fecha*/
    if((fread(&(movie->date), sizeof(time_t), 1, stream)) != 1){
    	free(movie->title);
        free(movie->script);
        free(movie->director);
        return ST_ERROR_INVALID_READ;
    }

    /* Score */
    if((fread(&(movie->score), sizeof(double), 1, stream)) != 1){
    	free(movie->title);
        free(movie->script);
        free(movie->director);
        return ST_ERROR_INVALID_READ;
    }

    /* Reviews */
    if((fread(&(movie->reviews), sizeof(size_t), 1, stream)) != 1){
    	free(movie->title);
        free(movie->script);
        free(movie->director);
        return ST_ERROR_INVALID_READ;
    }

	return ST_OK;
}

status_t print_movie(FILE *stream, const movies_t movie ){
	struct tm *timeptr;
	char aux_impresion, date_aux[MAX_DATE];

	/* ID */
	aux_impresion = (size_t)movie.id;
	if((fprintf(stream, "%u, " , aux_impresion)) == -1){
		return ST_ERROR_INVALID_PRINT;
	}

	/* Title */
	if((fprintf(stream, "%s, " , movie.title)) == -1){
		return ST_ERROR_INVALID_PRINT;
	}

	/* Script */
	if((fprintf(stream, "%s, " , movie.script)) == -1){
		return ST_ERROR_INVALID_PRINT;
	}

	/* Director */
	if((fprintf(stream, "%s, " , movie.director)) == -1){
		return ST_ERROR_INVALID_PRINT;
	}

	/* Fecha */
	 if( !(timeptr = localtime(&movie.date)) ){
		return ST_ERROR_INVALID_DATA;
	}

	if(!(strftime(date_aux, MAX_DATE, "%x", timeptr))){
		return ST_ERROR_INVALID_DATA;
	}
	if((fprintf(stream, "%s, " , date_aux)) == -1){
		return ST_ERROR_INVALID_PRINT;
	}

	/* Score */
	if((fprintf(stream, "%f, " , movie.score)) == -1){
		return ST_ERROR_INVALID_PRINT;
	}

	/* Reviews */
	if((fprintf(stream, "%lu", movie.reviews)) == -1){
		return ST_ERROR_INVALID_PRINT;
	}

	if((fprintf(stream, "\n")) == -1){
		return ST_ERROR_INVALID_PRINT;
	}

	return ST_OK;
}

status_t write_movie(FILE* stream, movies_t movie){
	size_t aux;

	if(fwrite(&movie.id, sizeof(int), 1, stream) != 1){
		return ST_ERROR_INVALID_WRITE;
	}

	aux = (size_t)strlen(movie.title);

	if(fwrite(&aux, sizeof(size_t), 1, stream) != 1){
		return ST_ERROR_INVALID_WRITE;
	}

	if(fwrite(movie.title, sizeof(char), aux, stream) != aux){
		return ST_ERROR_INVALID_WRITE;
	}

	aux = (size_t)strlen(movie.script);

	if(fwrite(&aux, sizeof(size_t), 1, stream) != 1){
		return ST_ERROR_INVALID_WRITE;
	}

	if(fwrite(movie.script, sizeof(char), aux, stream) != aux){
		return ST_ERROR_INVALID_WRITE;
	}

	aux = (size_t)strlen(movie.director);

	if(fwrite(&aux, sizeof(size_t), 1, stream) != 1){
		return ST_ERROR_INVALID_WRITE;
	}

	if(fwrite(movie.director, sizeof(char), aux,stream) != aux){
		return ST_ERROR_INVALID_WRITE;
	}

	if(fwrite(&movie.date, sizeof(time_t), 1, stream) != 1){
		return ST_ERROR_INVALID_WRITE;
	}

	if(fwrite(&movie.score, sizeof(double), 1, stream) != 1){
		return ST_ERROR_INVALID_WRITE;
	}

	if(fwrite(&movie.reviews, sizeof(size_t), 1, stream) != 1){
		return ST_ERROR_INVALID_WRITE;
	}

	return ST_OK;
}
