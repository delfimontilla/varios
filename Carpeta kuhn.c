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
*/

/*MEMORIA DINAMICA

memoria que se solicita en tiempo de ejecucion*/
/*como pedir memoria para un puntero */
int *p = (int *) malloc (sizeof(int));
float *q;
q=(float*) malloc(sizeof(float));
*p=2;
*q=2.3;
/*vector dinamico*/
int n;
scanf("%d", &n);
v=(int * ) malloc (sizeof(int)*n); /* o se puede v=(int*) calloc (n,sizeof(int)*n) que lo pone todo en 0*/

/*matriz semi dinamica*/
int main(){
	int * MS[10];
	int cantcol;
	scanf("%d", &cantcol);
	for(i=0; i<10; i++){
		MS[i]=(int *) malloc (sizeof(int)*cantcol);
	}
}

/*matriz dinamica*/

int main(){
	int **MD;
	int cf, cc;/*cantdidad de columnas y filas*/
	MD=(int**) malloc(sizeof(int*)*cf);
	scanf("%", &cc);
	for(i=0;i<cf;i++){
		MD[i]=(int *) malloc(sizeof(int)*cc);
	}
}

/*funcion para crear matriz dinamica con su main*/

int ** crear_mat_dim(int f, int c);/*prototitpo*/

int main(){
	int **MAT;
	int cf, cc;
	scanf("%d",&cf);
	scanf("%d",&cc);
	MAT = crear_mat_dim(cf,cc);
	crear_mat_dim2(&MAT,cf,cc);
	MAT[0][0]=5;
}

int ** crear_mat_dim(int f, int c){
	int c;
	int ** MC=(int**)malloc (sizeof(int*)*f);
	for(i=0; i<f; i++){
		MC[i]=(int*)malloc (sizeof(int*)*c);
	}	
	return MC;
}

void crear_mat_dim2(int**M, int f, int c){
	(*M)=(int **) malloc (sizeof(int)*f)
	int c; /****Que horrible esto*/
	for(i=0; i<f; i++){
		(*M[i])=(int *) malloc(sizeof(int)*c)
	}
}

/*liberar memoria*/
void liberar_mem_mat(int **M, int f, int c ){
	int i;
	for(i=0; i<f; i++){
		free(M[i]);
	}
	free(M);
}



/*********************ESTRUCTURAS**********************/

/*(*PP).NOM equivalente PP->NOM*/

typedef struct pers {
	char* NOM;
	long DNI;
	T_fecha fnac;
}T_PERS;

typedef struct FECHA{
	int dia, mes, año	
}T_fecha;

T_PERS A;
char cadena[20];
gets(CADENA);
A.NOM=(char*) malloc(sizeof(char)*(strlen(CADENA)+1));
strcpy(A.NOM, CADENA);
scanf("%", &A.fnac.dia);

/*Vector de punteros a estructura*/

T_PERS vec[5];
T_PERS *vp[4];
for(i=0; i<4;i++){
	vp[i]= (T_PERS*) malloc (sizeof(T_PERS));
}
T_PERS ** VC=NULL;


int cant;
scanf("%d", &cant);
VD=(T_PERS**) malloc(sizeof(T_PERS*)*cant);
scanf("%d", &cc);
for(i=o; i<cant;i++){
	VD[i]=(T_PERS*) malloc(sizeof(T_PERS*)*cc);
}


typedef struc area {
	char nom_area[20];
	T_PERS *lista;
}T_area;

T_area va[s];
for(i=0;i<s;i++){
	gets(va[i].nom_area);
	scanf("%d", va[i].cant);
	va[i].lista=(T_PERS*)malloc(sizeof(T_PERS*)va[i]*cant);
	leer_datos_pers(va[i]);
}


void leer_datos_pers(T_area x){
	int i;
	char * cad[20];
	for(i=0;i<x.cant;i++){
		gets(cad);
		(x.lista)[i].NOM=(char*)malloc(strlen(cad)+1);
		strcpy((x.lista)[i]nom.cad);
		scanf("%ld",&((x.lista)[i].DNI));
		scanf("%d", &(x.lista)[i],frac.dia);
		scanf("%d", &(x.lista)[i],frac.mes);
		scanf("%d", &(x.lista)[i],frac.año);
	}
}
/************************FUNCIONES RECURSIVAS************************/


int FACT (int n){
	if (n==0){
		return 1;
	}
	else
		return N*FACT(N-1);
}

/*Escribe funciones recursiva retoma el producto de dos nuemros positivos*/

int PROD(int a, int b){
	if(b==0 || a==0)
		return 0;
	else
		return PRODAUX(a,b)

	/*O
	if(a<b)
		reurn PRODAUX(b,a);
	else
		return PRODAUX(a,b);*/
}
int PRODAUX(int a, int b){
	if(B==0)
		return 0;
	else 
		return a+PRODAUX(a,b-1);
}




/*Escribe funciones recursiva retoma el producto de dos numeros, positivos o negativos*/



if(a< && b<0 || a>0 $$ b>0)
		return PROD(a,b);
else
		return -PROD(|a|,|b|);


int PRODPPAL(int a, int b){
	if(b==0 || a==0)
		return 0;
	else if (a<0)
		if(b<0)
			return PROD(-a,-b);
		else
			return -PROD(-a,b);
	else if (b<0)
		return -PROD(a,-b);
	else
		return PROD(a,b);
}


/*PROCEDIMIENTOS*/


/*IMPRIIR LA COMPONENTE DE UN V ETCTO DE FORMA RECURSIVA*/

void IMP_VEC(int v, int c){
	if(c<0)
		return EXIT_SUCCES;
	else 
		printf("%d\n", *[V]);
	IMP_VEC(            v++,        c--);
	return EXIT_FAILURE;
}


/*PUNTEROS*/

typedef struct PERS{
	char NOM[20];
	long DNI;
}T_PERS;

void crear_vector(T_PERS ***v, int cant)

T_PERS ** crear_vec_fun(int cant);
void llamar_vec_pers(T_PERS ** v, int cant)


int main(){
	T_PERS **vpp;
	int c;
	scanf("%d",&c);
	//crear_vector(&vpp,c);
	vpp=crear_vec_fun(c);
	llamar_vec_pers(vpp,c);
}

void crear_vector(T_PERS***v, int cant){
	size_t i;
	(*v)=(T_PERS**)malloc(sizeof(T_PERS*)*cant);
	for(i=0, i<cant ; i++)
		((*v)[i])=(T_PERS*)malloc(sizeof(T_PERS));
}
]T_PERS ** crear_vec_fun(int cant){
	T_PERS**v;
	int i;
	v=(T_PERS**)malloc(sizeof(T_PERS*cant));
	for(i=0; i<cant;i++)
		v[i]=(T_PERS*)malloc(sizeof(T_PERS));
	return v;
}

/**************************************************************/
/*PUNTERO A FUNCION*/

int CUAD(int x){
	return x*x;
}
int DOBLE(int x){
	return 2*x;
}
int CUBO(int x){
	return x*x*x;
}
typedef int(*pf)(int);

int main(){
	pf fmmat;
	fmmat=CUAD;
	printf("%d", fmmat(3));
	pf V[]={CUAD,CUBO,DOBLE};
	for(i=0; i<3; i++)
		print("%d", V[i](i));
}


/*Procedimiento que recibe una funcion*/

void IMP_TABLA(pffn, int d, int h){
	int i;
	for(i=d; u<=h, i++)
		printf("%d",fn(i) );
}

/*funcion que devuelve una funcion*/

pf select_fn(int i){
	switch(i){
		case 1: return CUAD;
		case 2: return CUBO;
		default:DOBLE;
	}
}
int main(){
	select_fn(1)(3);//la llama y vuelve a llamar
}


/*ARCHIVOS*/

int main(){
	FILE *pf;
	char CAD[&1];
	int i=0;
	char S[&1];
	if((pf=fopen("TEXTTO", "wb"))==NULL)
		printf("error");
	else{
		strcpy(CAD, "hola que tal");
		while(CAD[i])
			fputc(CADIH+,pf); /*QUE ES ESO_?????????????*/
		fclose(pf);
	}
	if(pf=fopen("TEXTO","rb")==NULL)
		printf("error");
	else{
		i=0;
		/*pato dice no hacer lo que sigue pero lo copio kuhn*/
		while(!feof(pf)){
			s[i++]=fgetc(pf);
			s[i]="\0";
		}
		return 1;
	}
}

/*Para leer cadenas de caracteres*/

int fputs(const char *CAD, FILE *pf)/*0 bien distinto de 0 error*/
char *fgets(char*CAD, int n, FILE *pf)/*null distinto de null*/
int fprintf(FILE *pf, const char* formato, arg)
int fscanf(FILE *pf, const char* formato, arg)



/*fne/s p/estructura*/

size_t fwrite( const void * b, size_t n, size_t c, FILE *p);
int fseek(FILE *pf, long desplaz, int os);
long ftell(FILE *pf)/*-1lerror*/
void rewind(FILE*pf);

/***********************************************************************/

#include <stdio.h>
#include <string.h>

typedef struct pers{
	long NOM[20];
	long DNI;
}T_PERS;

void leer_vec(T_PERS*v);
void limp_vec(T_PERS*v);

int main(){
	T_PERS vp[20];
	leer_vec(T_PERS*v){
		int c,i;
		char resp;
		FILE *pf;
		printf("%c",&reap);
		if(recu==!n){
			if((pf=fopen("personas","wb"))==NULL)
				printf("error");
			else{
				printf("infrese la cant de personas");
				fscanf(stdin, "%d",&c);
				for(i=0; i<c;i++){
					printf("ingrese nom:\n")
					fcanf(stdin, "%s";v[i].nom)
				}
			strcpy(v[i].nom."xxx")
			fwrite(&v[i], sizeof(T_PERS),1,pf);
			fclose(pf);
			}
		}
		else{
			if((pf=fopen("persona","rb"))==NULL)
				printf("error");
			else{
				i=o;
				while(!feof(pf))
					fread(&v[i++];sizeof(T_PERS),1,pf);
				fclose(pf);
			}/*falta limpiar buffer*/
		}
	}
}

/*si do reinas se pueden atacar (igual columna, fila o diagonal)*/

typedef enum{
	TRUE=1;
	FALSE=0;
}bool_t;

bool_t comer_reina(int MAT[][N], size_t n){
	size_t i, pos_x, pos_y, pos_1=0, found=0;
	for(i=0; i<n && found==0; i++){
		for(j=0;j<n && found==0;j++){
			if(pos_1==0){
				pos_x=i;
				pos_y=j;
				pos_1=1;/*para que sirve*/
			}
			else{
				if(pos_x==i || pos_y==j){
					found=TRUE;
				}
				else if(abs(pos_x-i)==abs(pos_y-j))
					found=TRUE;
				else
					return FALSE;
			}
			return TRUE;
		}
	}
}

typedef struct NODO{
	int val;
	struct NODO *sig;
}T_NODO;

int main(){
	T_NODO *L =NULL;
	L=(T_NODO) malloc(sizeof(T_NODO));
	scanf("%d", &L->val);
	L->sig=NULL;
	AUX=L;
	L=(T_NODO*) malloc(sizeof(T_NODO));
	scanf("%d", &L->val);
	L->sig=AUX;
}

/*dos maneras de crear lista*/

T_NODO crear_lista(){
	T_NODO *L=NULL, *AUX=NULL;
	int cant;
	scanf(cant>0);
	*L=(T_NODO*) malloc(sizeof(T_NODO));
	scanf("%d", &L->val);
	L->sig=AUX;
	AUX=L;
	cant--:
	return L;
}
 int main(){
 	T_NODO *LIS=NULL;
 	LIS = crear_lista(); //crear_lista(LIS);
 }

 /*la otra manera*/

void crear_lista(T_NODO**L){
	T_NODO *L=NULL, *AUX=NULL;
	int cant;
	scanf(cant>0);
	**L=(T_NODO*) malloc(sizeof(T_NODO));
	scanf("%d", &(*L)->val);
	(*L)->sig=AUX;
	AUX=(*L);
	cant--:
	return L;
}
 int main(){
 	T_NODO *LIS=NULL;
 	LIS = crear_lista(); //crear_lista(&LIS);
 }

 /*instertar al ifnal*/

 void insert_fin(T_NODO**L, int v){
 	T_NODO*AUX=(*L), AUX_2=(T_NODO*)malloc(sizeof(T_NODO*));
 	AUX_2->sig=NULL;
 	AUX_2->val=v;;
 	if(aux){
 		while(AUX->sig)
 			AUX=AUX->sig;
 		AUX->sig=AUX_2;
 	}
 	else 
 		(*L)=AUX_2;
 }

 /* escribir el insertar de forma  recursiva*/

 void insert_fin(T_NODO**L, int V){
 	if(*L==NULL){
 		*L=(T_NODO)malloc(sizeof(T_NODO));
 		(*L)->val=v;
 		*L->sig=NULL;
 	}
 	else
 		insert_fin(&(*L)->sig, v);
 }

 void IMPRIMIR_LISTA(T_NODO*L){
 	while(L){
 		printf("%d", L->val):
 		L=L->sig;
 	}
 	return ;
 }

 /*recursivo*/

 void IMPRIMIR_LISTA(T_NODO*L){
 	if(L){
 		printf("%d", L->val):
 		IMPRIMIR_LISTA(L->sig);
 	}
 	return ;
 }

 /*eliminar un valor de la lista*/

 void eliminar_lista(T_NODO**L, int v){
 	T_NODO *AUX=NULL;
 	if(*L){
 		if((*L)->val==v){
 			aux=(*L->sig);
 			free(aux);
 			eliminar_valor(L,V);
 		}
 		else
 			eliminar_valor(&(*L->sig),v);
 	}
 }