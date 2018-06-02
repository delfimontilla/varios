#define MAX_CADENA 256



char * copiadepato(char * s){
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

status_t leer_archivo_txt(simpletron_t ** simpletron, 
	parametros_t *argumentos, size_t * cant_palabras ,FILE *fentrada, palabra_t ** palabras)
 /*recibe los punteros: a la estructura de los argumentos para poder acceder al valor de cant_palabras (cantidad de instrucciones),
 a la estructura de simpletron para cargar las instrucciones en el vector palabras y 
 al archivo de entrada para poder */
{
	size_t i;
	char aux[MAX_LARGO_INGRESO];
	long instruccion;
	char *pc;
	instruccion = 0;

	palabra_t *paux;
	size_t used_size, alloc_size;

	if(simpletron==NULL || cant_palabras==NULL || argumentos == NULL || palabras==NULL )
		return ST_ERROR_PTR_NULO;
	*cant_palabras=0;
	simpletron->palabras=NULL;
	alloc_size=used_size=0;

	if (!(strcmp(argumentos->ia,OPCION_TXT))){

 		for(i=0; i<cant_palabras;i++){
	    	if(fgets(aux,MAX_LARGO_INGRESO,fentrada)==NULL){
	    		liberar_memoria(simpletron);
	    		return ST_ERROR_FUERA_RANGO;
	    	}

	    	instruccion = strtol(aux,&pc,10); 
	    
	    	if(*pc!='\0'&& *pc!='\n')
	    		return ST_ERROR_NO_NUMERICO;

	 		if(instruccion<MIN_PALABRA||instruccion>MAX_PALABRA)
	 			return ST_ERROR_FUERA_RANGO;



	 		while(fgets(aux, MAX_CADENA,stdin)!=NULL){
	 			if((pc==strrchr(aux,';'))!=NULL)
	 				*pc='\0';
	 			if(*copiadepato(aux)=='\0')
	 				continue;
	 			instruccion=strtol(aux, &pc,10);
	 			if(*pc!='\0'){
	 				free(simpletron->palabras);
	 				simpletron->palabras=NULL;
	 				return ST_ERROR_APERTURA_ARCHIVO;
	 			}
	 			if(instruccion<-9999/*en una macro*/ || instruccion > 9999){
					free(simpletron->palabras);
					simpletron->palabras = NULL;
					return ST_ERROR_PALABRA_INVALIDA;
	 			}
				if(used_size==alloc_size){
					if((paux=(palabra_t *)realloc(simpletron->palabras,sizeof(palabra_t)*alloc_size+CHOP_SUEY))==NULL){
					free(simpletron->palabras);
					simpletron->palabras = NULL;
					return ST_ERROR_NOMEM;
					}
				simpletron->palabras = paux;
				alloc_size+=CHOP_SUEY;
				}
				(*palabras)[used_size++]=instruccion;
			}
			if((paux=(palabra_t*)realloc(simpletron->palabras, sizeof(palabra_t) * used_size))=NULL){
				free(*palabras);
				*palabras = NULL;
				return ST_ERROR_NOMEM;
			}
			simpletron->palabras = paux;	
			*cant_palabras = used_size;

		 	simpletron->palabras[i]=instruccion;
		 	}

	 	printf("%s\n",MSJ_CARGA_COMPLETA);
	 	printf("%s\n",MSJ_COMIENZO_EJECUCION); 
	 
		return ST_OK;
	}

	else if (!(strcmp(argumentos->ia,OPCION_STDIN))){

{
 	

 	printf("%s\n",MSJ_BIENVENIDA);

 	for(i=0; i<cant_palabras;i++){
 		
 		printf("%2.i ? \n", i);
 	    
 	    if(fgets(aux,MAX_LARGO_INGRESO,stdin)==NULL){
 			liberar_memoria(simpletron);
    		return ST_ERROR_FUERA_RANGO;
	    }
	    
	    instruccion = strtol(aux,&pc,10);
	    
	    if(*pc!='\0'&& *pc!='\n')
			return ST_ERROR_NO_NUMERICO;
	 	
	 	if(instruccion==FIN)
	 		return ST_OK;
	 	
	 	if(instruccion<MIN_PALABRA||instruccion>MAX_PALABRA){
	 		liberar_memoria(simpletron);
	 		return ST_ERROR_FUERA_RANGO;
	 	}

	 	simpletron->palabras[i]=instruccion;
	 }

	 printf("%s\n",MSJ_CARGA_COMPLETA);
	 printf("%s\n",MSJ_COMIENZO_EJECUCION);	

	 return ST_OK;
}





}
