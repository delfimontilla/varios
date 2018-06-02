#ifndef DATABASE__H
#define DATABASE__H

#include "utilities.h"
#include "common.h"
#include "config.h"

#define MAX_ARG_VALUE_DATABASE 3
#define ARG_POS_INPUT 1
#define ARG_POS_OUTPUT 2

#define ID_FIELD_POS 0
#define TITLE_FIELD_POS 1
#define SCRIPT_FIELD_POS 2
#define DIRECTOR_FIELD_POS 3
#define DATE_FIELD_POS 4
#define SCORE_FIELD_POS 5
#define REVIEWS_FIELD_POS 6

status_t validate_arguments_database(int argc, char *argv[], FILE **fin, FILE **fout);
status_t create_database(FILE *fin,FILE *fout);


#endif