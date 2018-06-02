#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "idioma.h"
#include "tp1.h"
#include "funciones.h"
#include "metricas.h"
#include "carreras.h"
#include "tipos.h"
#include "setup.h"

int main (void)
{
    int opcion, padron, carrera, notas[MAX_STR], maximo, minimo, aplazos, usado = 0;
    char nombre[MAX_STR], asignaturas[MAX_FIL][MAX_COL];
    char *aux;
    size_t i;
    float promedio;

    status_t status;
    state_t state;
    state = ST_IDLE;
    status = ST_OK;

	inicializar_vector(notas);          /* pone a todos los elementos del vector de enteros en '\0' (explicado donde está la función)*/
    inicializar_matriz(asignaturas);    /* vector de punteros a vectores de char, pone todo los elementos del vector de char en '\0' */
    inicializar_vector_chars(nombre);   /* pone todos los elementos del vector "nombre" en '\0'                                      */
    padron = 0;

        do
        {
            switch(state)
            {
                case ST_IDLE:

                    system(CMD_BORRAR_PANTALLA);
                    printf( "%s ", MSJ_MENU_BIENVENIDO);
                    state = ST_MENU_PRINCIPAL;
                    status = ST_OK;
                    break;

                case ST_MENU_PRINCIPAL:

                    imprimir_menu_principal();

                    status = leer_int(&opcion);
                    if(status != ST_OK)
                    {
                        if(status == ST_PUNTERO_NULO)
                        {
                            procesar_errores(status);
                            return EXIT_FAILURE;
                        }
                        procesar_errores(status);
                        state = ST_MENU_PRINCIPAL;
                        status = ST_OK;
                        break;
                    }
                    switch(opcion)
                    {
                        case OPCION_MOD_REGISTRO:
                            state = ST_MOD_REGISTRO;
                            status = ST_OK;
                            break;

                        case OPCION_MOD_ASIG:
                            state = ST_MOD_ASIG;
                            status = ST_OK;
                            break;

                        case OPCION_METRICA:
                		 	state = ST_METRICA;
                		 	status = ST_OK;
                		 	break;

                        case OPCION_FINALIZAR:
                            state = ST_FINALIZAR;
                            status = ST_OK;
                            break;

                        case OPCION_SALIR:
                            state = ST_SALIR;
                            status = ST_OK;
                            break;

                        default:
                           procesar_errores(status);
                           state = ST_MENU_PRINCIPAL;
                           break;
                    }
                    break;

                case ST_MOD_REGISTRO:

                    imprimir_menu_registro();

                    status = leer_int(&opcion);
                    if(status != ST_OK)
                    {
                        if(status == ST_PUNTERO_NULO)   /* 2 tratamientos distintos porque consideramos un puntero nulo justificación suficiente */
                        {                               /* para terminar el programa, pero un error de ingreso de opciones, no                   */
                            procesar_errores(status);
                            return EXIT_FAILURE;
                        }
                        procesar_errores(status);
                        state = ST_MOD_REGISTRO;
                        status = ST_OK;
                        break;
                    }
                    switch(opcion)
                    {
                        case OPCION_NOMBRE:
                            state = ST_NOMBRE;
                            status = ST_OK;
                            break;

                        case OPCION_PADRON:
                            state = ST_PADRON;
                            status = ST_OK;
                            break;

                        case OPCION_CARRERA:
                            state = ST_CARRERA;
                            status = ST_OK;
                            break;

                        case OPCION_VOLVER:
                            state = ST_MENU_PRINCIPAL;
                            status = ST_OK;
                            break;

                        default:
                            procesar_errores(status);
                            state = ST_MENU_PRINCIPAL;
                            break;
                    }
                    break;

                case ST_NOMBRE:

                    printf( "%s \n", MSJ_MOD_NOMBRE);
                    fgets(nombre, MAX_STR, stdin);
                    if ((aux = strchr(nombre, '\n')) != NULL)
                    {
                       *aux = '\0';
                    }
                    state = ST_MOD_REGISTRO;
                    status = ST_OK;
                    break;

                case ST_PADRON:

                    printf( "%s \n", MSJ_MOD_PADRON);
                    status = leer_int(&padron);
                    if(status != ST_OK)
                    {
                        if(status == ST_PUNTERO_NULO)
                        {
                            procesar_errores(status);
                            return EXIT_FAILURE;
                        }
                        procesar_errores(status);
                    }
                    state = ST_MOD_REGISTRO;
                    status = ST_OK;
                    break;

                case ST_CARRERA:

                    printf( "%s \n\n", MSJ_MOD_CARRERA);

                    status = leer_int(&carrera);
                    if(status != ST_OK)
                    {
                        if(status == ST_PUNTERO_NULO)
                        {
                            procesar_errores(status);
                            return EXIT_FAILURE;
                        }
                        procesar_errores(status);
                    }
                    state = ST_MOD_REGISTRO;
                    status = ST_OK;
                    break;

                case ST_MOD_ASIG:

                    usado = largo_vector (notas);
                    if(usado == 0)
                    {
                        printf( "%s \n\n", MSJ_ASIG_VACIA);
                        printf( "%i%c%s\n", OPCION_NUEVA_ASIGNATURA, OPCION_DELIM_2, MSJ_NUEVA_ASIG);
                        printf( "%i%c%s\n", OPCION_VOLVER, OPCION_DELIM_2, MSJ_MENU_VOLVER);

                        status = leer_int(&opcion);
                        if(status != ST_OK)
                        {
                            if(status == ST_PUNTERO_NULO)
                            {
                                procesar_errores(status);
                                return EXIT_FAILURE;
                            }
                            procesar_errores(status);
                        }
                        switch(opcion)
                        {
                            case OPCION_NUEVA_ASIGNATURA:
                                state = ST_NUEVA_ASIG;
                                status = ST_OK;
                                break;
                            case OPCION_VOLVER:
                                state = ST_MENU_PRINCIPAL;
                                status = ST_OK;
                                break;
                            default:
                                procesar_errores(status);
                                state = ST_MENU_PRINCIPAL;
                                break;
                        }
                    }
                    else
                    {
                        printf("%s\n\n", MSJ_ASIG_CARGADAS);

                        for( i = 0; i < usado; i++){
                            printf("%c %s %c%d%c \n", CARACT_GUION, asignaturas[i], OPCION_DELIM_1, notas[i], OPCION_DELIM_2);
                        }
                        printf( "\n%s\n\n", MSJ_MENU_OPCIONES);
                        printf( "%i%c%s\n", OPCION_NUEVA_ASIG, OPCION_DELIM_2, MSJ_NUEVA_ASIG);
                        printf( "%i%c%s\n", OPCION_VOLVER, OPCION_DELIM_2, MSJ_MENU_VOLVER);

                        status = leer_int(&opcion);
                        if(status != ST_OK)
                        {
                            if(status == ST_PUNTERO_NULO)
                            {
                                procesar_errores(status);
                                return EXIT_FAILURE;
                            }
                            procesar_errores(status);
                        }
                        switch(opcion)
                        {
                            case OPCION_NUEVA_ASIG:
                                state = ST_NUEVA_ASIG;
                                status = ST_OK;
                                break;

                            case OPCION_VOLVER:
                                state = ST_MENU_PRINCIPAL;
                                status = ST_OK;
                                break;

                            default:
                                procesar_errores(status);
                                state = ST_MENU_PRINCIPAL;
                                break;
                        }
                    }
                    break;

                case ST_NUEVA_ASIG:

                    printf ("%s\n", MSJ_INGRESO_ASIG);
                    fgets(asignaturas[usado], MAX_COL, stdin);
                    if ((aux = strchr(asignaturas[usado], '\n')) != NULL)   /* fgets deja en el vector "xxxxxx\n\0                          */
                    {                                                       /* con esto, buscas el \n en el vector y lo reemplazas con '\0' */
                       *aux = '\0';
                    }

                    printf("%s\n", MSJ_INGRESO_NOTA);
					status = leer_int(&(notas[usado])); /*la variable "usado" no varía y es la misma para los 2 casos, entonces lo vuelvo a usar*/
                    if(status != ST_OK)
                    {
                        if(status == ST_PUNTERO_NULO)
                        {
                            procesar_errores(status);
                            return EXIT_FAILURE;
                        }
                        procesar_errores(status);
                    }
                    state = ST_MOD_ASIG;
                    break;

                case ST_METRICA:

                    imprimir_menu_metrica ();

                	status = leer_int(&opcion);
                    if(status != ST_OK)
                    {
                        procesar_errores(status);
                        state = ST_MENU_PRINCIPAL;
                    }
                    switch(opcion)
                    {
                        case OPCION_PROMEDIO:
                            state = ST_PROMEDIO;
                            status = ST_OK;
                            break;

                        case OPCION_MAXIMO:
                            state = ST_MAXIMO;
                            status = ST_OK;
                            break;

                        case OPCION_MINIMO:
                            state = ST_MINIMO;
                            status = ST_OK;
                            break;

                        case OPCION_CANT_ASIG:
                            state = ST_CANT_ASIG;
                            status = ST_OK;
                            break;

                        case OPCION_APLAZOS:
                            state = ST_APLAZOS;
                            status = ST_OK;
                            break;

                        case OPCION_VOLVER:
                            state = ST_MENU_PRINCIPAL;
                            status = ST_OK;
                            break;

                        default:
                           procesar_errores(status);
                           state = ST_MENU_PRINCIPAL;
                           break;
                    }
                    break;

                case ST_PROMEDIO:

                    promedio = calcular_promedio(usado, notas);
                    printf("%f\n", promedio);
                    state = ST_METRICA;
                    status = ST_OK;
                   	break;

                case ST_MAXIMO:

                    maximo = buscar_maximo(usado, notas);
                    printf("%d\n", maximo);
                    state = ST_METRICA;
                    status = ST_OK;
                    break;

                case ST_MINIMO:

                    minimo = buscar_minimo(usado, notas);
                    printf("%d\n", minimo);
                    state = ST_METRICA;
                    status = ST_OK;
                    break;

                case ST_CANT_ASIG:

                    printf("%d\n", usado);
                    state = ST_METRICA;
                    status = ST_OK;
                    break;

                case ST_APLAZOS:

                    aplazos = buscar_aplazos(usado, notas);
                    printf("%d\n", aplazos);
                    state = ST_METRICA;
                    status = ST_OK;
                    break;

                case ST_FINALIZAR:

                     /*nombre*/
                    if(nombre [0] == '\0')
                    {
                        if ((aux = strchr(nombre, '\n')) != NULL)   /* fgets deja en el vector "xxxxxx\n\0                          */
                        {                                           /* con esto, buscas el \n en el vector y lo reemplazas con '\0' */
                            *aux = '\0';
                        }
                        printf("%s%c ", MSJ_NO_DATA, DELIM_COMA);
                    }
                    else
                    {
                        printf("%s%c ", nombre, DELIM_COMA);
                    }

                    /*Padrón*/
                    if(padron == 0)
                    {
                        printf("%s%c ", MSJ_NO_DATA, DELIM_COMA);
                    }
                    else
                    {
                        printf("%i%c ", padron, DELIM_COMA);
                    }

                    /*Carrera*/
                    switch(carrera)
                    {
                        case CODIGO_ELECTRONICA:
                            printf("%s%c ", MSJ_ELECTRONICA, DELIM_COMA);
                            break;

                        case CODIGO_QUIMICA:
                            printf("%s%c ", MSJ_QUIMICA, DELIM_COMA);
                            break;

                        case CODIGO_INDUSTRIAL:
                            printf("%s%c ", MSJ_INDUSTRIAL, DELIM_COMA);
                            break;

                        case CODIGO_ALIMENTOS:
                            printf("%s%c ", MSJ_ALIMENTOS, DELIM_COMA);
                            break;

                        case CODIGO_MECANICA:
                            printf("%s%c ", MSJ_MECANICA, DELIM_COMA);
                            break;

                        default:
                            procesar_errores(status);                 /* si entra acá, es que carrera no es ninguna de las asignaturas */
                            printf("%s%c ", MSJ_NO_DATA, DELIM_COMA);
                            break;
                    }

                    /* Asignaturas, promedio y aplazos */
                    promedio = calcular_promedio(usado, notas);
                    aplazos = buscar_aplazos (usado, notas);
                    printf("%d%c %f%c %d\n\n", usado, DELIM_COMA, promedio, DELIM_COMA, aplazos);

                    inicializar_vector(notas);
                    inicializar_matriz(asignaturas);
                    inicializar_vector_chars(nombre);
                    padron = 0;
                    carrera = 0;
                    usado = 0;
                    aplazos = 0;

                    state = ST_MENU_PRINCIPAL;
                    status = ST_OK;
                    break;

                case ST_SALIR:

                    printf( "%s\n", MSJ_DESPEDIDA);
                    state = ST_SALIR;
                    status = ST_OK;
                    break;

                default:
                    fprintf( stderr, "%s%s'\n\n", MSJ_ERROR, MSJ_OPCION_INVALIDA);
                    return EXIT_FAILURE;
            }
        } while (state!= ST_SALIR);
    return EXIT_SUCCESS;
}
