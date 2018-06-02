#ifndef FUNCIONES__H
#define FUNCIONES__H

#include "setup.h"
#include "tipos.h"

#define MAX_STR 40

void imprimir_menu_principal(void);
void imprimir_menu_registro(void);
status_t leer_int (int * p);
status_t procesar_errores (status_t err);
int largo_vector (int vector[MAX_STR]);
size_t largo_matriz (char matriz[][MAX_COL]);
void inicializar_vector(int vector [MAX_STR]);
void inicializar_vector_chars(char vector [MAX_STR]);
void inicializar_matriz(char matriz[][MAX_COL]);

#endif