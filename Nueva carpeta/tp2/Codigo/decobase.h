#ifndef DECOBASE__H
#define DECOBASE__H

#include "utilities.h"
#include "common.h"
#include "config.h"

#define MAX_DATE 9

#define MAX_ARG_VALUE_DECOBASE 2
#define ARG_POS_DECOBASE 1

#define MAX_ARG_VALUE_DECOBASE 2
#define ARG_POS_DECOBASE 1

status_t validate_arguments_decobase(int argc, char *argv[], FILE **decobase);
status_t print_database(FILE *decobase);

#endif