/***Carpeta kuhn***/

/*Procedimiento que recibe una matriz cuadrada e imprime la diagonal secundaria*/

void IMP_DS(int MAT[][N], int cant){
	int i, j ;
	for ( i = 0; i < N , j<=0; i++, j--)
	{
		printf("%i", MAT[i][j] );
	}
}
/*Con una sola variable*/
void IMP_DS(int MAT[][N], int cant){
	int i;
	for(i=0; i<cant;i++){
		printf("%d\n",MAT[i][cant-1-i] );
	}
}
/*main para funcion que sigue*/
int main(){
	int M[100][100];
	int cf, cc;
	scanf("%d", &cf);
	scanf("%d", &cc);
	cargar_datos(M,&cf,&cc);
}

void cargar_datos(int MAT[][N], int *f, int *c){
	int i,j;
	scanf("%d",f);
	scanf("%d",c);
	for(i=0; i<*f; i++){
		for(j=0;j<*c;j++){
			scanf("%d",&MAT[i][j]);
			*f=-1;
			*c=-2;
		}
	}
}


/*Ordenamiento de vectores
	-Seleccion
	-burbujeto
	-inserccion
	-quicksort*/

void ORD_SEL(int V[N], int CANT){
	int i, j, MIN, POSMIN;
	for(j=0;j<cant-1;j++){
		if(V[i]<MIN){
			MIN=V[i];
			POSMIN=i;
		}
	}
	INTERC(&V[j], &V[POSMIN]);
}

void INTERC(int *x, int *y){
	int AUX=*x;
	*x=*y;
	*y=AUX;
} 

/***metodo del burbujeo****/

void ORD_BURBUJEO(int V[], int CANT){
	int i, j, ORDENADO=0;
	for(j=0; j<cant && !ORDENADO;j++){
		ORDENADO=1;
		for(i=0;i<=cant-1-j, i++){
			if (V[i]>V[i+1])
			{
				INTERC(&V[i],&V[i++]);
				ORDENADO=0;
			}
		}
	}
}

/*ESTRUCTURAS-> se pueden diefinir estructuras con datos distintos
 vectores-> conjuntos de datos donde el tipo de infromacion son iguales
*/
/*PUNTEROS
-operaciones validas para punteros
	-sumar o restar al puntero un numero entero
	-comparar punteros
-No se puede hacer V++ pero si V+4 porque sa un numero pero no cambia V
M equivalente &M[0]
*M equivalente M[0]

	