#include "ranks.h"

/* Invocación: ./ranks operación -if basededatos -f modificación -log log */

int main(int argc, char * argv[]){
	status_t status;
	FILE *db, *data, *log, *aux_file;

	char * filename = AUX_FILE_NAME;

	if((status = validate_arguments_operations(argc, argv, &db, &data, &log)) != ST_OK){
		handle_error(status);
		return EXIT_FAILURE;
	}

 	if((aux_file = fopen(filename, "w+b")) == NULL){
		return ST_ERROR_OPEN_FILE;
	}

	if((status = process_arguments_operations(argv, db, data, log, aux_file)) != ST_OK){
		handle_error(status);
		return EXIT_FAILURE;
	}

	if(rename(filename, argv[ARG_POS_DATA]) == -1){
		return ST_ERROR_INVALID_DATA;
	}

	fclose(db);
	fclose(data);
	fclose(log);
	fclose(aux_file);

	return EXIT_SUCCESS;
}

status_t validate_arguments_operations(int argc, char *argv[], FILE **db, FILE **data, FILE **log){
	size_t n;

	if( !db || !data || !log || !argv ){
		return ST_ERROR_NULL_POINTER;
	}

	if(argc != MAX_ARG_VALUE_OPERATIONS){
		return ST_ERROR_INVALID_ARG;
	}

	for(n = 2; n < MAX_ARG_VALUE_OPERATIONS; n += 2){
		if(argv[n][0] != PREFIX_ARG_OPT_RANKS){
			return ST_ERROR_INVALID_ARG;
		}
	}

	if(( *db = fopen(argv[ARG_POS_DATA], "r+b")) == NULL){
	    return ST_ERROR_OPEN_FILE;
	}

	if((*data = fopen(argv[ARG_POS_MODIFICATIONS], "r+b")) == NULL){
		return ST_ERROR_OPEN_FILE;
	}

	if((*log = fopen(argv[ARG_POS_ERRORS], "a")) == NULL){
		return ST_ERROR_OPEN_FILE;
	}

	return ST_OK;
}

status_t process_arguments_operations(char *argv[], FILE *db, FILE *data, FILE *log, FILE *aux_file){
	status_t status;
	int operation;

	if( !db || !data || !log || !argv ){
		return ST_ERROR_NULL_POINTER;
	}

	operation = argv[ARG_POS_OPERATION][0];

	switch(operation){

		case CHAR_OPT_SUBSCRIBE:
			if((status = (subscribe_operation(db, data, log, aux_file))) != ST_OK){
                return status;
            }
			break;
		case CHAR_OPT_UNSUBSCRIBE:
			if((status = (unsubscribe_operation(db, data, log, aux_file))) != ST_OK){
                return status;
			}
			break;
		case CHAR_OPT_MODIFICATION:
			if((status = (modificate_operation(db, data, log, aux_file)))!= ST_OK){
                return status;
			}
			break;
		default:
			return ST_ERROR_INVALID_ARG;
    }

	return status;
}

status_t subscribe_operation(FILE *db, FILE *data, FILE *log, FILE *aux_file){
	movies_t aux1, aux2;
	size_t used;
	char aux_char;

	if( !db || !data || !log ){
		return ST_ERROR_NULL_POINTER;
	}

	if((read_movie(db, &aux1)) != ST_OK){
		return ST_ERROR_INVALID_DATA;
	}

	if((read_movie(data, &aux2)) != ST_OK){
		return ST_ERROR_INVALID_DATA;
	}

	used=0;

	while( !feof(data) && !feof(db) ){

		if(aux1.id < aux2.id){

			write_movie(aux_file, aux1);
			used++;
			read_movie(db, &aux1);
        }

		else if(aux1.id > aux2.id){

			write_movie(aux_file, aux2);
			used++;
			read_movie(data, &aux2);
        }

		else if(aux1.id == aux2.id){

			fprintf(log, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_INVALID_DATA_SUBS);
			print_movie(log, aux2);
			write_movie(aux_file, aux1);
			used++;
			read_movie(db, &aux1);
			read_movie(data, &aux2);
        }
	}

	while( !feof(db) ){
		write_movie(aux_file, aux1);
		used++;
		read_movie(db, &aux1);
	}

	while( !feof(data )){
		write_movie(aux_file, aux2);
		used++;
		read_movie(data, &aux2);
	}

	/* Reescribo la cantidad de peliculas del archivo para el decobase */
	aux_char = (char)used;
	if(fwrite(&aux_char, sizeof(char), 1, aux_file) != 1){
		return ST_ERROR_INVALID_DATA;
	}

	return ST_OK;
}

status_t unsubscribe_operation(FILE *db, FILE *data, FILE *log, FILE *aux_file){
	movies_t aux1, aux2;
	size_t used;
	char aux_char;

	if( !db || !data || !log ){
		return ST_ERROR_NULL_POINTER;
	}

	if((read_movie(db, &aux1)) != ST_OK){
		return ST_ERROR_INVALID_DATA;
	}

	if((read_movie(data, &aux2)) != ST_OK){
		return ST_ERROR_INVALID_DATA;
	}

	if(feof(data)){
		fprintf(log, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_INVALID_DATA_UNSUBS);
	}

	used = 0;

	while( !feof(data) && !feof(db) ){

		if( aux1.id < aux2.id ){
            write_movie(aux_file, aux1);
            used++;
			read_movie(db,&aux1);
        }
		else if( aux1.id == aux2.id ){
			read_movie(db, &aux1);
			read_movie(data, &aux2);
        }
        else if( aux1.id > aux2.id ){
        	fprintf(log, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_INVALID_DATA_UNSUBS);
			write_movie(log, aux2);
			read_movie(data, &aux2);
        }
	}

	while( !feof(db) ){
		write_movie(aux_file, aux1);
		used++;
		read_movie(db, &aux1);
	}

	while( !feof(data) ){
		fprintf(log, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_INVALID_DATA_UNSUBS);
		write_movie(log, aux2);
		read_movie(data, &aux2);
	}

	/* Reescribo la cantidad de peliculas del archivo para el decobase */
	aux_char = (char)used;
	if(fwrite( &aux_char, sizeof(char), 1, aux_file) != 1){
		return ST_ERROR_INVALID_DATA;
	}

	return ST_OK;
}

status_t modificate_operation(FILE *db, FILE *data, FILE *log, FILE *aux_file){
	size_t used;
	movies_t aux1, aux2;
	char aux_char;

	if(!db || !data || !log ){
		return ST_ERROR_NULL_POINTER;
	}

	if((read_movie(db, &aux1)) != ST_OK){
		return ST_ERROR_INVALID_DATA;
	}

	if((read_movie(data, &aux2)) != ST_OK){
		return ST_ERROR_INVALID_DATA;
	}

	used = 0;

	while( !feof(data) && !feof(db) ){

		if( aux1.id < aux2.id ){
        	write_movie(aux_file, aux1);
        	used++;
			read_movie(db, &aux1);
		}
		else if( aux1.id == aux2.id ){
			write_movie(aux_file, aux2);
			used++;
			read_movie(db, &aux1);
			read_movie(data, &aux2);
        }
        else if( aux1.id > aux2.id ){
			write_movie(log, aux2);
			fprintf(log, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_INVALID_DATA_UNSUBS);
			read_movie(data, &aux2);
        }
	}

	while( !feof(db) ){
		write_movie(aux_file, aux1);
		used++;
		read_movie(db, &aux1);
	}

	while( !feof(data) ){
		fprintf(log, "%s:%s \n", MSG_ERROR_PREFIX, MSG_ERROR_INVALID_DATA_UNSUBS);
		write_movie(log, aux2);
		read_movie(data, &aux2);
	}

	/* Reescribo la cantidad de peliculas del archivo para el decobase */
	aux_char = (char)used;
	if( fwrite(&aux_char, sizeof(char), 1, aux_file) !=1 ){
		return ST_ERROR_INVALID_DATA;
	}

	return ST_OK;
}
