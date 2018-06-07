#include <stdio.h>
#include <stdlib.h>

typedef struct NODO {
	int val;
	struct NODO * sig;
} T_NODO;

T_NODO *crear();
void crear_lista (T_NODO ** L);
void impr_lista (T_NODO * L);
T_NODO * crear_ord();
void ins_ord(T_NODO ** L, int val);

int main(){
	T_NODO * LIS = crear_ord();
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


/*T_NODO * crear()/*la hice con kuhn{
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
	/*la hiizo una chica en el pizarron
	T_NODO * L=NULL, **AUX=NULL;
	int cant;
	scanf("%d",&cant);
	L=(T_NODO *) malloc(sizeof(T_NODO));
	scanf("%d", &L->val);
	L->sig=NULL;
	AUX=&(L->sig);
	/*if (cant>1){
		while(cant>1){
			(*AUX)=(T_NODO *) malloc(sizeof(T_NODO));
			scanf("%d", (*AUX)->val);
			(*AUX)->sig=NULL;
			AUX = &((*AUX)->sig);
			cant--;
		}
	  }
	return L;
}*/

void impr_lista (T_NODO *L){

	while (L){
		printf("%d \t", L->val);
		L=L->sig;

	}
}

T_NODO * crear_ord()
{
	T_NODO * L=NULL;
	int cant, v;
	scanf("%d", &cant);
	while(cant>0)
	{
		scanf("%d", &v);
		ins_ord(&L, v);
		cant--;
	}
	return L;
}

void ins_ord(T_NODO ** L, int valor)
{
  T_NODO *AUX_1 = *L, *AUX_2;


	if (!AUX_1 || AUX_1 -> val > valor) {
		(*L) = (T_NODO*)calloc(1, sizeof(T_NODO));
		(*L) -> val = valor;
		(*L) -> sig = AUX_1;
	}
	else {
		while (AUX_1 -> sig && AUX_1 -> sig -> val <= valor){
			AUX_1 = AUX_1 -> sig;
		}
		AUX_2 = AUX_1 -> sig;
		AUX_1 -> sig = (T_NODO*)calloc(1, sizeof(T_NODO));
		AUX_1 -> sig -> val = valor;
		AUX_1 -> sig -> sig = AUX_2;
	}
}
