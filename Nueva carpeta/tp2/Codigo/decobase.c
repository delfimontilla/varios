#include "decobase.h"

int main(int argc, char* argv[]){
	status_t status;
	FILE *decobase;

	if((status = (validate_arguments_decobase(argc, argv, &decobase))) != ST_OK){
		handle_error(status);
		return EXIT_FAILURE;
	}

	if((status = (print_database(decobase))) != ST_OK){
		handle_error(status);
		return EXIT_FAILURE;
	}

	fclose(decobase);
	return EXIT_SUCCESS;
}

status_t validate_arguments_decobase(int argc, char *argv[], FILE **decobase){
	
	if( !decobase || !argv || !argc){
		return ST_ERROR_NULL_POINTER;
	}

	if(argc != MAX_ARG_VALUE_DECOBASE){
		return ST_ERROR_INVALID_ARG;
	}

	if((*decobase = fopen(argv[ARG_POS_DECOBASE], "r+")) == NULL){
		return ST_ERROR_OPEN_FILE;
	}
	return ST_OK;
}

status_t print_database(FILE *decobase){
	movies_t movie;
	size_t amount, n;
	char aux_char;

	/* Valido punteros*/
	if( !decobase ){
		return ST_ERROR_NULL_POINTER;
	}

	/* Verifica la cantidad de peliculas */
	if(fseek(decobase, -1L, SEEK_END) == -1){
		return ST_ERROR_INVALID_DATA;
	}

	if((fread(&aux_char, sizeof(char), 1, decobase)) != 1){
	    return ST_ERROR_INVALID_DATA;
	}

	amount = (size_t)aux_char;
	fprintf(stdout, "%s %lu\n", MSG_AMOUNT_MOVIES, amount);

	/*Impresión de peliculas*/
	fseek(decobase, 0L, SEEK_SET);

	for(n = 0; n != amount; n++){
		
		if(read_movie(decobase, &movie) != ST_OK){
			return ST_ERROR_INVALID_DATA;
		}

		if(print_movie(stdout, movie) != ST_OK){
			return ST_ERROR_INVALID_DATA;
		}
	}

	return ST_OK;
}