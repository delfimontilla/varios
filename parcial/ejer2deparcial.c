#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CANT_ARG_SG 5
#define CANT_ARG_CG 6
#define MAX_CADENA 200
#define POS_VIEJA 1
#define POS_NUEVA 2
#define POS_ARCHIVO 3
#define POS_TIPO_ARCH 4
#define POS_SIEMPRE 5
#define TIPO_TXT "txt"
#define TIPO_BIN "bin"

typedef enum{
	ST_OK,
	ST_ERROR_ARG,
	ST_ERROR_ARG_INV,
	ST_AP_ARCHIVO,
	ST_LECTURA
}status_t;

/*argumentos posicionales ./reemplazar svieja snueva archivo tipo_arch (siempre)*/

status_t validar_argumentos(int argc, char *argv[], char * svieja, char * snueva,FILE ** pf){

	if (argv==NULL || (argc!= CANT_ARG_CG && argc!=CANT_ARG_SG)){	
		return ST_ERROR_ARG;
	}

		if(strcpy(svieja,argv[POS_VIEJA])==NULL){
			return ST_ERROR_ARG_INV;
		}
		if(strcpy(snueva,argv[POS_NUEVA])==NULL){
			return ST_ERROR_ARG_INV;
		}

		if(!(strcmp(argv[POS_TIPO_ARCH], TIPO_TXT))){
			if((*pf=fopen(argv[POS_ARCHIVO], "rt+"))==NULL){
				return ST_AP_ARCHIVO;
			}
		}

		else if (!(strcmp(argv[POS_TIPO_ARCH], TIPO_BIN))) {
			if((*pf=fopen(argv[POS_ARCHIVO], "rb+"))==NULL){
				return ST_AP_ARCHIVO;
			}
		}

		else
			return ST_AP_ARCHIVO;


	return ST_OK;
}

status_t leer_archivos(char *argv[], char * cadena, FILE *pf){

	if(!(strcmp(argv[POS_TIPO_ARCH], TIPO_TXT))){
		if (fgets(cadena, MAX_CADENA, pf)==NULL)
			return ST_LECTURA;
	}
		
	if(!(strcmp(argv[POS_TIPO_ARCH], TIPO_BIN))){
		if(fread(cadena,sizeof(char),MAX_CADENA, pf)!=1)
			return ST_LECTURA;	
	}

	return ST_OK;
}

status_t reemplazar_una(char * cadena, char * svieja, char * snueva){
	char *aux;
	int  largo_svieja;

	if((aux=strstr(cadena, svieja))==NULL){
		printf("%s\n", cadena);
		return ST_OK;
	}
	*aux='\0';
	largo_svieja=strlen(svieja);
	aux+=largo_svieja;
	printf("%s%s%s\n",cadena , snueva, aux);
	return ST_OK;
}

status_t reemplazar_todos(char * cadena, char * svieja, char * snueva){
	char  * aux;

	aux=strtok(cadena," ");
	while(aux!=NULL){
		if(strcmp(aux,svieja)==0){
			printf("%s ",snueva );
		}
		else 
			printf("%s ",aux );
		aux=strtok(NULL, " ");
	}
	printf("\n");
	return ST_OK;
}

/*
status_t reemplazar_todos(char * cadena, char * svieja, char *snueva){
	char *aux, *ptrviejo;
	int  largo_svieja;

	largo_svieja=strlen(svieja);
	for(aux=cadena;(ptrviejo=strstr(aux, svieja))!= NULL; aux=ptrviejo+largo_svieja) {
		ptrviejo='\0';
		printf("%s\n",aux );
	}
	return ST_OK;
}

*/
int main(int argc, char *argv[])
{
	char svieja[MAX_CADENA], snueva[MAX_CADENA], cadena[MAX_CADENA];
	FILE * pf;
	status_t st;

	if ((st=validar_argumentos(argc, argv, svieja, snueva, &pf))!= ST_OK){
		fprintf(stderr, "%s\n", "error argumentos");
		return EXIT_FAILURE;
	}

	if((st=leer_archivos(argv, cadena, pf))!=ST_OK){
		fprintf(stderr, "%s\n", "error lectura" );
		return EXIT_FAILURE;
	}

	if (argc==CANT_ARG_SG){
		if((st=reemplazar_una(cadena, svieja, snueva))!=ST_OK){
			fprintf(stderr, "%s\n", "error reemplazar");
			return EXIT_FAILURE;
		}	
	}

	if(argc==CANT_ARG_CG){
		if((st=reemplazar_todos(cadena, svieja, snueva))!=ST_OK){
			fprintf(stderr, "%s\n", "error reemplazar todos");
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}