#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"
#include "tp1.h"
#include "funciones.h"
#include "metricas.h"
#include "idioma.h"

status_t procesar_errores (status_t err)
{
    switch (err)
    {
        case ST_PUNTERO_NULO:
            fprintf(stderr, "%s %s \n", MSJ_ERROR, MSJ_PUNTERO_NULO);
            break;

        case ST_OPCION_INVALIDA:
            fprintf(stderr, "%s %s \n", MSJ_ERROR, MSJ_OPCION_INVALIDA);
            break;

        default:
            break;
    }

    return ST_OK;
}

void imprimir_menu_principal(void)
{
    printf( "%s\n\n", MSJ_MENU_OPCIONES);
    printf( "%i%c%s\n", OPCION_MOD_REGISTRO, OPCION_DELIM_2, MSJ_MENU_MOD_REGISTRO);
    printf( "%i%c%s\n", OPCION_MOD_ASIG, OPCION_DELIM_2, MSJ_MENU_MOD_ASIG);
    printf( "%i%c%s\n", OPCION_METRICA, OPCION_DELIM_2, MSJ_MENU_METRICA);
    printf( "%i%c%s\n", OPCION_FINALIZAR, OPCION_DELIM_2, MSJ_MENU_FINALIZAR);
    printf( "%i%c%s\n", OPCION_SALIR, OPCION_DELIM_2, MSJ_MENU_SALIR);
}

void imprimir_menu_registro(void)
{
    printf( "\n%s\n", MSJ_MENU_OPCIONES);
    printf( "%i%c%s\n", OPCION_NOMBRE, OPCION_DELIM_2, MSJ_MENU_REG_NOMBRE);
    printf( "%i%c%s\n", OPCION_PADRON, OPCION_DELIM_2, MSJ_MENU_REG_PADRON);
    printf( "%i%c%s\n", OPCION_CARRERA, OPCION_DELIM_2, MSJ_MENU_REG_CARRERA);
    printf( "%i%c%s\n", OPCION_VOLVER, OPCION_DELIM_2, MSJ_MENU_VOLVER);
}

void imprimir_menu_metrica(void)
{
    printf( "%s\n\n", MSJ_MENU_OPCIONES);
    printf("%d%c%s\n", OPCION_PROMEDIO, OPCION_DELIM_2, MSJ_MENU_METRICA_PROMEDIO);
    printf("%d%c%s\n", OPCION_MAXIMO, OPCION_DELIM_2, MSJ_MENU_METRICA_MAXIMO );
    printf("%d%c%s\n", OPCION_MINIMO, OPCION_DELIM_2, MSJ_MENU_METRICA_MINIMO );
    printf("%d%c%s\n", OPCION_CANT_ASIG, OPCION_DELIM_2, MSJ_MENU_METRICA_CANT_ASIG );
    printf("%d%c%s\n", OPCION_APLAZOS, OPCION_DELIM_2, MSJ_MENU_METRICA_APLAZOS );
    printf("%d%c%s\n", OPCION_VOLVER, OPCION_DELIM_2, MSJ_MENU_VOLVER);
}

status_t leer_int (int * p)
{
    char s[MAX_STR], *temp;

	if (p == NULL)
    {
		return ST_PUNTERO_NULO;
	}

	if (fgets(s, MAX_STR,stdin) == NULL)
    {
		return ST_OPCION_INVALIDA;
	}
	*p = strtoul (s, &temp, 10);
	if (*temp && *temp != '\n')
	{
		return ST_OPCION_INVALIDA;
	}

	return ST_OK;
}

int largo_vector (int vector[MAX_STR])      /* En main se inicializan todos los elementos del vector de enteros "notas" con '\0' quedando:   */
{                                           /* '\0''\0'.....'\0'. Al ingresar, por ejemplo, 3 notas (un 9, un 6 y un 8) en este vector queda */
	size_t i;                               /* 9 6 8 '\0''\0'...'\0'. Al ejecutarse el ciclo, la variable i deja de contar al encontrarse el */
                                            /* primer '\0' del vector de enteros, representando el número de notas ingresadas en el vector.  */
	for (i = 0; vector[i] != '\0'; i++);

	return i;
}

void inicializar_vector(int vector [MAX_STR])           /* Mismo razonamiento que en la función largo_vector()  */
{
    memset(vector, '\0', MAX_STR);
}

void inicializar_vector_chars(char vector [MAX_STR])    /* Mismo razonamiento que en la función largo_vector()  */
{
    memset(vector, '\0', MAX_STR);
}

void inicializar_matriz(char matriz[][MAX_COL])
{
    size_t i, j;

    for(i = 0; i < MAX_FIL; i++)
    {
        for(j = 0; j < MAX_COL; j++)
        {
            matriz[i][j] = '\0';
        }
    }
}

float calcular_promedio(size_t usado, int notas[MAX_STR])
{
    size_t i;
    float promedio;

    for (i = 0, promedio = 0; i < usado ; i++){
        promedio += notas [i];
    }

    promedio /= usado ;

    return promedio;
}

int buscar_maximo(size_t usado,int notas [MAX_STR])
{
    size_t i;
    int max;

    max = notas[0];

    for (i = 0; i < usado; ++i)
    {
        if (notas [i] > max){
            max = notas[i];
        }
    }

    return max;
}

int buscar_minimo(size_t usado,int notas [MAX_STR])
{
    size_t i;
    int min;

    min = notas[0];

    for (i = 0; i < usado; ++i)
    {
        if (notas [i] < min){
            min = notas[i];
        }
    }

    return min;
}


int buscar_aplazos (size_t usado, int notas [MAX_STR])
{
    size_t i;
    int aplazos = 0;

    for(i = 0; i < usado; i++)
    {
        if (notas[i] < DESAPROBADO){
            aplazos++;
        }
    }
    return aplazos;
}
