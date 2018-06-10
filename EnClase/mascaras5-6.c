punto A
El modo de comunicacion serie de un sistema embebido posee los registros UCSROA y UCSROC entre otros. Para el registro A es MSR(7) = [RXCP/TXCO/ / / / / / /]
RXCO para recepcion de datos y se encuentra en 0 hasta que externamente es puesto en 1 cuando hay un dato disponible para su lectura, el dato disponible se encuentra en una variable local UDR0 del tipo unsigned char.
Se pide una implementacion de una funcion que reciba puntero UCSROA y retorna el dato.

prototipo de la funcion
/*unsigned char uart_read(unsigned char * Reg,unsigned char ?? UDR)*/ pongo puntero porque quiero trabajar sobre el dato y devolver el dato


#include <stdio.h>
#include <stdlib.h>

#define MASK_RXCO 0x80*


unsigned char uart_read(unsigned char * Reg,unsigned char * UDR); 

/*punto A*/
unsigned char uart_read(unsigned char * Reg,unsigned char * UDR){
	if(!Reg)
		return -1;
	while(!(*Reg & MASK_RXCO)){

	}
	if(UDR){
		*UDR=UDR0/*UDR0 es global*/;
	}
	return UDR0;
}

/*punto B*/

para los registros del UCSROC que son UPM01 UPM00 el registro que es de la forma MSR(1)[ / /UPM01/UPM00/ / / / / ] 
forman un unico campo de dos bits.
Defina el tipo parity_t con los elementos paridad reservada.... paridad par y paridad impar.
UPM01 UPM00
  0		0	desactivado
  0		1	reservado
  1		0   activado paridad par
  1		1	activado paridad impar

  escriba una funcion que reciba un dato del tipo parity_t y modifique su registro. y otra que reciba un registro y devuelva el valor de la paridad
void UART_set_parity_mode(unsigned char * Reg, parity_t parity);
parity_t UART_get_parity_mode(unsigned char ?? Reg);


#define UPM00 4
#define UPM01 5
#define MASK_UPM 0x30/*00110000*/
#define SHIFT_UPM 4


typedef enum {
	PARIDAD_DESACTIVADO = 0x0,
	PARIDAD_RESERVADO = 0X1,
	PARIDAD_PAR = 0X2,
	PARIDAD_IMPAR = 0X3
}parity_t;

void UART_set_parity_mode(unsigned char * Reg, parity_t parity){
	if(!Reg)
		return ;
	*Reg & = ~MASK_UPM;
	*Reg|= (parity<<SHIFT_UPM); /*yo le estoy diciendo que paridad quiero que tenga */
}




parity_t UART_get_parity_mode(unsigned char /*va nada porque no tengo que cambiar nada, solo veo que hay */Reg){
	return (Reg & MASK_UPM)>> SHIFT_UPM;
}

/*.c*/
dar un ejemplo de funciones y un uso de las variables implentadas.

int main(void){
	parity_t paridad;
	unsigned char UDR;
	unsigned char UCSROA = 0xC0, UCSROC = 0xDE;
	printf("UDR0:  0x%02X\n", uart_read(&UCSROA, &UDR) );/*X es de hexa*/
	printf("UDR: 0x%02X\n",UDR);/*imprime lo mismo pero veo que sean iguales para confirmar*/
	printf("UPM: 0x%02X\n", UART_get_parity_mode(UCSROC));/*la pregunto, la seteo y la vuelvo a preguntar*/
	UART_set_parity_mode(&UCSROC, PARIDAD_PAR);
	printf("UPM: 0x%02X\n", UART_get_parity_mode(UCSROC) );
	return EXIT_SUCCES;

}