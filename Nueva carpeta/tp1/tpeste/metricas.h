#ifndef METRICAS__H
#define METRICAS__H

#define DESAPROBADO 4

float calcular_promedio(size_t usado, int notas[MAX_STR]);
int buscar_maximo(size_t usado, int notas [MAX_STR]);
int buscar_minimo(size_t usado, int notas [MAX_STR]);
void imprimir_menu_metrica(void);
int buscar_aplazos (size_t usado, int notas [MAX_STR]);

#endif