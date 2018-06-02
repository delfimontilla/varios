#ifndef TYPES__H
#define TYPES__H

typedef enum{

	ST_OK,
	ST_ERROR_NULL_POINTER,
	ST_ERROR_OPEN_FILE,
	ST_ERROR_INVALID_ARG,
	ST_ERROR_NO_MEMORY,
	ST_ERROR_INVALID_DATA,
	ST_ERROR_INVALID_READ,
	ST_ERROR_INVALID_WRITE,
	ST_ERROR_INVALID_PRINT,
	ST_ERROR_INVALID_DATA_SUBSCRIBE,
	ST_ERROR_INVALID_DATA_UNSUBSCRIBE,
	ST_ERROR_INVALID_DATA_MODIFICATION

}status_t;

typedef unsigned char uchar;

#endif