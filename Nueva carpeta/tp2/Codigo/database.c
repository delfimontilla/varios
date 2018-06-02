#include "database.h"
#include "functions.h"
#include "utilities.h"
#include "common.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	FILE *fin, *fout;
	status_t status;

	if((status = validate_arguments_database(argc, argv, &fin, &fout)) != ST_OK){
		handle_error(status);
		return EXIT_FAILURE;
	}
	if((status = create_database(fin,fout)) != ST_OK){
		handle_error(status);
		return EXIT_FAILURE;
	}

	fclose(fin);
	fclose(fout);

	return EXIT_SUCCESS;
}

status_t validate_arguments_database(int argc, char *argv[], FILE **fin, FILE **fout){

	if( !fin || !fout || !argv ){
		return ST_ERROR_NULL_POINTER;
	}

	if(argc != MAX_ARG_VALUE_DATABASE){
		return ST_ERROR_INVALID_ARG;
	}

	if((*fin = fopen(argv[ARG_POS_INPUT], "r+" )) == NULL){
		return ST_ERROR_OPEN_FILE;
	}

	if((*fout = fopen(argv[ARG_POS_OUTPUT], "wb" )) == NULL){
		fclose(*fin);
		return ST_ERROR_OPEN_FILE;
	}

	return ST_OK;
}

status_t create_database(FILE *fin, FILE *fout){
	movies_t *movies, *aux;
	struct tm date;
	char **csv_fields, *endptr, line[MAX_STR], aux_char;
	size_t n, used_size, alloc_size, aux_lenght;
	status_t status;

	/*Pido memoria para la estructura*/
	if((movies = (movies_t *)calloc(INITIAL_MOVIES, sizeof(movies_t))) == NULL){
		fclose(fin);
		fclose(fout);
		return ST_ERROR_NO_MEMORY;
	}

	used_size = 0;
	alloc_size = INITIAL_MOVIES;

	/*Comienzo la asignacion*/
    while(fgets(line, MAX_STR, fin) != NULL){

		/*Busco el fin de linea*/
		if((endptr = strrchr(line, '\n')) != NULL){
			*endptr = '\0';
		}
		/*Separo los campos*/
		if((status = split(line, CHAR_CSV_FIELD_SEPARATOR, &csv_fields, &n)) != ST_OK){
			del_movies_array(&movies, &used_size);
			return ST_ERROR_INVALID_DATA;
		}
		/*Si me quedo sin espacios*/
		if(used_size == alloc_size){

			if((aux = (movies_t *)realloc(movies, (alloc_size + INITIAL_MOVIES) * sizeof(movies_t))) == NULL){
				del_movies_array(&movies, &used_size);
				del_array(&csv_fields, &n);
				return ST_ERROR_NO_MEMORY;
			}

			alloc_size += INITIAL_MOVIES;
			movies = aux;
		}
		/* Comienzo la asignacion de datos*/

		/*Asigno el id*/
		movies[used_size].id = strtoul(csv_fields[ID_FIELD_POS], &endptr, 10);
		if( *endptr != '\0' ){
			del_movies_array(&movies, &used_size);
			del_array(&csv_fields,&n);
			return ST_ERROR_NULL_POINTER;
		}

		if(fwrite(&movies[used_size].id, sizeof(int), 1, fout) != 1){
			return ST_ERROR_INVALID_DATA;
		}

		/*Asigno titulo*/
		if((movies[used_size].title = (char *)malloc(sizeof(csv_fields[TITLE_FIELD_POS]))) == NULL){
			del_movies_array(&movies, &used_size);
			del_array(&csv_fields, &n);
			return ST_ERROR_NO_MEMORY;
		}
		strcpy(movies[used_size].title, csv_fields[TITLE_FIELD_POS]);

		aux_lenght = (size_t)strlen(movies[used_size].title);
		if(fwrite(&aux_lenght, sizeof(size_t), 1, fout) != 1){
			return ST_ERROR_INVALID_DATA;
		}

		if(fwrite(movies[used_size].title, sizeof(char), aux_lenght, fout) != aux_lenght){
			return ST_ERROR_INVALID_DATA;
		}

		/*Asigno script*/
		if((movies[used_size].script = (char *)malloc(sizeof(csv_fields[SCRIPT_FIELD_POS]))) == NULL){
			del_movies_array(&movies, &used_size);
			del_array(&csv_fields, &n);
			return ST_ERROR_NO_MEMORY;
		}
		strcpy(movies[used_size].script, csv_fields[SCRIPT_FIELD_POS]);

		aux_lenght = (size_t)strlen(movies[used_size].script);
		if(fwrite(&aux_lenght, sizeof(size_t), 1, fout) != 1){
			return ST_ERROR_INVALID_DATA;
		}

		if(fwrite(movies[used_size].script, sizeof(char),aux_lenght, fout) != aux_lenght){
			return ST_ERROR_INVALID_DATA;
		}

		/*Asigno director*/
		if((movies[used_size].director = (char *)malloc(sizeof(csv_fields[DIRECTOR_FIELD_POS]))) == NULL){
			del_movies_array(&movies, &used_size);
			del_array(&csv_fields, &n);
			return ST_ERROR_NO_MEMORY;
		}
		strcpy(movies[used_size].director,csv_fields[DIRECTOR_FIELD_POS]);

		aux_lenght = (size_t)strlen(movies[used_size].director);
		if(fwrite(&aux_lenght, sizeof(size_t), 1, fout) != 1){
			return ST_ERROR_INVALID_DATA;
		}

		if(fwrite(movies[used_size].director, sizeof(char), aux_lenght, fout) != aux_lenght){
			return ST_ERROR_INVALID_DATA;
		}

		/* Asigno fecha*/
		(movies[used_size]).date = mktime(transform_date(&date, csv_fields[DATE_FIELD_POS], &endptr));
		/*char_to_structtm(csv_fields[DATE_FIELD_POS], &date); */
		if((movies[used_size].date = mktime(&date)) == -1){
			return ST_ERROR_INVALID_DATA;
		}
		if(fwrite(&movies[used_size].date, sizeof(time_t), 1, fout) != 1){
			return ST_ERROR_INVALID_DATA;
		}

		/*Asigno Score*/
		movies[used_size].score = strtod(csv_fields[SCORE_FIELD_POS], &endptr);
		if( *endptr != '\0' ){
			del_movies_array(&movies, &used_size);
			del_array(&csv_fields, &n);
			return ST_ERROR_NULL_POINTER;
		}
		if(fwrite(&movies[used_size].score, sizeof(double), 1, fout) != 1){
			return ST_ERROR_INVALID_DATA;
		}

		/*Asigno Reviews*/
		movies[used_size].reviews = strtoul(csv_fields[REVIEWS_FIELD_POS], &endptr, 10);
		/*if(*endptr!='\0'||*endptr==' '){
			printf("Entro el el strtol if reviews\n");
			printf("endptr:%s\n",endptr);
			del_movies_array(&movies,&used_size);
			del_array(&csv_fields,&n);
			return ST_ERROR_NULL_POINTER;
		}*/
		if(fwrite(&movies[used_size].reviews, sizeof(size_t), 1, fout) != 1){
			return ST_ERROR_INVALID_DATA;
		}
		del_array(&csv_fields, &n);
		used_size++;
	}

	aux_char = (char)used_size;
	if(fwrite(&aux_char, sizeof(char), 1, fout) != 1){
		return ST_ERROR_INVALID_DATA;
	}

	return ST_OK;
}
