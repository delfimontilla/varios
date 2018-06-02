/****parcial****/
typedef long/int palabra_t;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CHOP_SUEY 3
#define MAX_STR 256

typedef enum {
	....
} status_t;

const char *errmsg[]={...};

typedef enum {
	OP_LEER=10,
	OP_ESCRIBIR=11,
	...
}opcode_t;

typedef struct simpletron {
	palabra_t acumulador;
	palabra_t * memoria;
	size_t memsize;
	size_t pc;
	palabra_t regi;
	opcode_t opcode;
	unsigned char operando;
}simpletron_t;

char * fulltrim_inplace(char*) /*para tomar solo lo que necesito sin los comentarios*/;

status_t cargar_txt(palabra_t **, size_t *);
status_t simpletron(simpletron_t **, palabra_t * , size_t);
void printf print_simpletron (const simpletron_t *);
void destruir(simpletron_t **);

int main(void){
	
	palabra_t * memoria;
	size_t n;
	simpletron_t * simply;
	status_t st;

	if ((st=cargar_txt(&memoria, &n))!=ST_OK){
		fprintf(stderr, "%s\n", errmsg[st] );
		return EXIT_FAILURE;
	}
	if ((st=simpletron(&simply, memoria,n))!=ST_OK){
		free(memoria);/*la memoria fue pedrida en simpletron*/
		fprintf(stderr, "%s\n", errmsg{st} );
		return EXIT_FAILURE;
	}
	free(memoria);
	print_simpletron(simply);
	destruir(&simply);
	return EXIT_SUCCES;
}

char * fulltrim_inplace(char * s){
	char * inicio, *fin;
	for (inicio = s; isspace(*inicio)/*implicito a poner distinto de 0*/ && *inicio!='\0'; inicio++){
	/*busco que apunte al \0*/		
	}
	if (*inicio=='\0'){
		*s='\0';/*equivalente a  s[0]='\0'*/
		return s;
	}
	for(fin = strlen(s)-1; isspace(*fin) && fin!=s;fin--){
		/*cuento desde atras, apunta al ultimo caracter antes de un espacio. isspacefin termina donde no haabia un espacio*/
	}
	*++fin='\0';
	return menmove(s,inicio,fin-inicio+1);
}

status_t cargar_txt(palabra_t ** memoria, size_t *n){
	char saux[MAX_STR], *perr;
	palabra_t * paux;
	size_t used_size, alloc_size;
	long palabra;

	if (memoria==NULL || n==NULL){
		return ST_ERROR_PTR_NULO;
	}
	*n=0;
	alloc_size=used_size=0;
	*memoria = NULL;
	while (fgets(saux, MAX_STR, stdin)!=NULL ){
		if((perr==strrchr(saux,';'))!=NULL)
			*perr='\0';
		if(*fulltrim_inplace(saux)=='\0')
			continue;
		palabra = strtol(saux, &perr , 10);
		if(*perr!='\0'){
			free(*memoria);
			*memoria = NULL;
			return ST_ERROR_ARCHIVO_CORRUPTO;
		}
		if(palabra<-9999/*en una macro*/ || palabra > 9999){
			free(*memoria);
			*memoria = NULL;
			return ST_ERROR_PALABRA_INVALIDA;
		}
		if(used_size==alloc_size){
			if((paux=(palabra_t *)realloc(*memoria,sizeof(palabra_t)*alloc_size+CHOP_SUEY))==NULL){
				free(*memoria);
				*memoria = NULL;
				return ST_ERROR_NOMEM;
			}
			*memoria = paux;
			alloc_size+=CHOP_SUEY;
		}
		(*memoria)[used_size++]=palabra;
	}
	/*************dos opciones*********/
	/************opcion 1************/
	if((paux=(palabra_t*)realloc(*memoria, sizeof(palabra_t) * used_size))=NULL){
		free(*memoria);
		*memoria = NULL;
		return ST_ERROR_NOMEM;
	}
	*memoria = paux;	
	*n = used_size;

	/***********opcion 2***********/
	while(used_size<alloc_size)
		(*memoria)[used_size++]=0;
	*n=used_size;
	/******************************/
	return ST_OK
}

status_t simpletron(simpletron_t ** simply, palabra_t* memoria, size_t){
	if(simply==NULL || memoria==NULL)
		return ST_ERROR_PTR_NULO;
	if(!n)
		return ST_ERROR_NADA_QUE_CARGAR;
	if((*simply= (simpletron_t *)calloc(sizeof(simpletron_t),1))==NULL)
		return ST_ERROR_NOMEM;
	if(((*simply)->memoria = (palabra_t *) malloc(sizeof(palabra_t)*n))=NULL){
		free(*simply);
		*simply=NULL;
		return ST_ERROR_NOMEM;
	}
	memcpy((*simply)->memoria, memoria, n*sizeof(palabra_t));
	(*simply)->memsize=0;
	(*simply)->acumulador=0;
	(*simply)->pc=0;
	(*simply)->regi=0;
	(*simply)->opcode=0;
	(*simply)->operando=0;
	return ST_OK;
}

void print_simpletron(const simpletron_t * simply){
	int i;
	i=0;
	/*falta la validacion del puntero que recibe*/
	puts("REGISTROS:");
	printf("         acumulador: %+5li\n", simply->acumulador );
	printf("         program counter:     %02lu\n",simply->pc );
	printf("         instruccion: %+5li\n",simply->regi );
	printf("         opcode:  %02li\n",simply->memoria[simply->pc]/100 );
	printf("         operando:   %02li\n", simply->memoria[simply->pc]%100 );
	puts("\n MEMORIA:");
	for(i=0; i<10 ; i++)
		printf("   %i", i );
	for(i=0; i<10; i++){
		if(i % 10 == 0)
			printf("\n%2i",i);
		printf("    %+05li\n",simply->memoria[i] );
	}
	puts("    ")
}


void destruir(simpletron_t ** simply){
	if(simply!=NULL && *simply!=NULL){
		free((*simply)->memoria);
		(*simply)->memoria=NULL;
		(*simply)->memsize=(*simply)->acumulador=0;
		(*simply)->pc=(*simply)->operando=0;
		(*simply)->opcode=(*simply)->operando=0
	}
	free(*simply);
	*simply=NULL;
}


/*********************************************************punto dos****************************************************/

status_t validar_argumentos (int argc, char * argv[], const char **pvieja, const char **pnueva, bool_t * todas){
	if(argv==NULL || !pvieja || !pnueva || !todas)
		return st....
	argv++;
	/****falta algo***/
	if(argc!=3 && arg!=4)
		return st.......
	if(argc==4)
		*todas=(!strcmp(*argv++,"-g"))? TRUE: FALSE;
	*pvieja=*argv++;
	*pnueva=*argv++;
	return (*argv==NULL) ? ST_OK : ST_ERROR;
}

int main(int argc, char const *argv[]){
	char linea [MAX_STR];
	const char * vieja, *nueva;
	bool_t todas = FALSE;
	status_t st;
	char *aux, *aguja;
	size_t len;
	if((st=validar_argumentos(argc, argv, &vieja, &nueva, &todas))!=ST_OK){
		.....
	}
	len = strlen(vieja);
	if(todas=TRUE){
		while(fgets(linea, MAX_STR,ST_OK)!=NULL){
			for(aux=linea; (aguja= strstr(aux,vieja)/*busca vieja dentro de aux*/)!=NULL; aux=aguja+len){
				*aguja='\0';
				printf("%s%s",aux, nueva );
			}
			printf("%s", aux);
		}
	}
	else{
		/*aca va el otro caso en vez de tener un for pone un if porque quiero que imprima una sola vez*/
	}


	return 0;
}



























































