#include <stdio.h>
#include <stdlib.h>

typedef struct NODO {
	int val;
	struct NODO * sig;	
} T_NODO;

T_NODO *crear();
void crear_lista (T_NODO ** L);
void impr_lista (T_NODO * L);

int main(){
	T_NODO * LIS = NULL;
	LIS = crear();
	crear_lista(&LIS);
	impr_lista(LIS);
	return 0;
}


T_NODO * crear(){
	T_NODO *L = NULL, *AUX = NULL;
	int cant, i, int_aux;
	scanf("%d",&cant);
	L=(T_NODO *) calloc(1, sizeof(T_NODO));
	scanf("%d", &int_aux);
	L->val=int_aux;
	L->sig=NULL;
	AUX=L;
	for (i = 0; i < cant; i++){
		L->sig= (T_NODO*)calloc(1,sizeof(T_NODO));
		scanf("%d", &int_aux);
		AUX->sig->val = int_aux;
		AUX->sig->sig = NULL;
		AUX=AUX->sig;
	}
	return L;
}/*copiada en pizzaron*/


T_NODO * crear()/*la hice con kuhn*/{
	T_NODO *L = NULL, *AUX = NULL;
	int cant;
	scanf("%d",&cant);
	L=(T_NODO *) malloc(sizeof(T_NODO));
	scanf("%d", &L->val);
	L->sig=NULL;
	AUX=L;
	while(cant-1>0){
		AUX->sig = (T_NODO *)malloc(sizeof(T_NODO));
		scanf("%d", &AUX->sig->val);
		AUX->sig->sig=NULL;
		AUX= AUX->sig;
		cant--;
	}
	return L;
}

T_NODO * crear (){
	/*la hiizo una chica en el pizarron*/
	T_NODO * L=NULL, **AUX=NULL;
	int cant;
	scanf("%d",&cant);
	L=(T_NODO *) malloc(sizeof(T_NODO));
	scanf("%d", &L->val);
	L->sig=NULL;
	AUX=&(L->sig);
	/*if (cant>1){*/
		while(cant>1){
			(*AUX)=(T_NODO *) malloc(sizeof(T_NODO));
			scanf("%d", (*AUX)->val);
			(*AUX)->sig=NULL;
			AUX = &((*AUX)->sig);
			cant--;
		}
	/*}*/
	return L;
}

void impr_lista (T_NODO *L){

	while (L){
		printf("%d\n", L->val);
		L=L->sig:

	}
}



/************************7/6********/

T_NODO * crear_ORD();
void /*insertar ordenadamente*/ INS_ORD(T_NODO ** L, int val);

int main(){
	T_NODO * LIS = crear_ORD();
	impr_lista(LIS);
	return 0;
}
T_NODO * crear_ORD(){
	T_NODO * L = NULL;
	int CANT, v;
	scanf("%d", &CANT);
	while(CANT>0){
		scanf("%d", &v);
		INS_ORD(&L,v);
		CANT--;
	}
	return L;
}

/**iterativo**/
void INS_ORD(T_NODO ** L, int val){
	
	T_NODO * AUX=(*L), *AUX_2;
	if(!AUX || AUX->val > val){
		(*L) = (T_NODO *) malloc(sizeof(T_NODO));
		(*L)->val = val;
		(*L) = AUX;
	}
	else{
		while(AUX->sig && AUX->sig->val <= val)
			AUX = AUX->sig;
		AUX_2 = AUX->sig;
		AUX->sig = (T_NODO *) calloc(1, sizeof(T_NODO) );
		AUX->sig->val = val;
		AUX->sig->sig = AUX_2;
	}
}

/**recursivo**por kuhn**/
void INS_ORD_REC(T_NODO ** L, int valor){
	
	T_NODO * AUX;
	if(!*L){
		(*L) = (T_NODO *) malloc(sizeof(T_NODO));
		(*L)->val=valor;
		(*L)->sig=NULL;
	}
	else if{
		AUX=(*L);
		(*L) = (T_NODO *) malloc(sizeof(T_NODO));
		(*L)->val = valor;
		(*L)->sig = AUX;
	}
	else
		INS_ORD_REC(&(*L)->, valor);
}