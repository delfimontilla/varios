#ifndef RANKS__H
#define RANKS__H

#include "utilities.h"
#include "common.h"
#include "config.h"

#define AUX_FILE_NAME "aux_file.bin"

#define MAX_ARG_VALUE_OPERATIONS 8
#define ARG_POS_OPERATION 1
#define ARG_POS_DATA 3
#define ARG_POS_MODIFICATIONS 5
#define ARG_POS_ERRORS 7

#define CHAR_OPT_SUBSCRIBE 'a'
#define CHAR_OPT_UNSUBSCRIBE 'b'
#define CHAR_OPT_MODIFICATION 'm'

status_t validate_arguments_operations(int argc, char *argv[], FILE **db, FILE **data, FILE **log);
status_t process_arguments_operations(char *argv[], FILE *db, FILE *data, FILE *log,  FILE *aux_file);
status_t modificate_operation(FILE *db, FILE *data, FILE *log, FILE *aux_file);
status_t unsubscribe_operation(FILE *db, FILE *data, FILE *log,  FILE *aux_file);
status_t subscribe_operation(FILE *db, FILE *data, FILE *log,  FILE *aux_file);

#endif