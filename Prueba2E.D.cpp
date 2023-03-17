#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// NOTA: Si se desea, se pueden comentar las lineas 84-87, 91, 93, 98-99, 102-103, 108-109 y 116, para mostrar solo los requisitos del problema.

/* -------------------------------------------------------------------------------------------------------------
------------------------------------------- ESTRUCTURA Y FUNCIONES DE LA PILA ----------------------------------
------------------------------------------------------------------------------------------------------------- */

typedef struct PilaNoAceptados{
	int dato;
	struct PilaNoAceptados *sgte;
}PilaNoAceptados;

typedef struct PilaNoAceptados *pila;

//INSERTAR EN LA PILA
void push_pila(pila *top,int dato){
	pila nuevo = (pila)malloc(sizeof(PilaNoAceptados));
	nuevo->dato=dato;
	nuevo->sgte=*top;							//el nuevo nodo se ingresa siempre en el cima de la pila
	*top=nuevo;
}

//ELIMINAR DE LA PILA
int pop_pila(pila *top){				
	pila eliminar=*top;
	int valor;
	
	if(!eliminar) return 0;		//caso de que la pila este vacía
	valor=eliminar->dato;
	*top=eliminar->sgte;		//se elimina siempre el nodo en la cima de la pila
	free(eliminar);
	return valor;
}

/* -------------------------------------------------------------------------------------------------------------
------------------------------------------- ESTRUCTURA Y FUNCIONES DE LA LISTA ---------------------------------
------------------------------------------------------------------------------------------------------------- */

typedef struct ListaNumerosStormer{
	int dato;
	struct ListaNumerosStormer *sgte;
	struct ListaNumerosStormer *ant;
}ListaNumerosStormer;

typedef struct ListaNumerosStormer *lista;

//INSERTAR EN LA LISTA
void push_lista(lista *cabeza, int dato){
	lista nuevo;
	nuevo = (lista)malloc(sizeof(ListaNumerosStormer));
	nuevo->dato = dato;
	nuevo->ant = nuevo->sgte = NULL;
	
	if(*cabeza){								// Ingresamos al inicio de la lista sin importar lo demas.
		nuevo->sgte = *cabeza;
		(*cabeza)->ant = nuevo;
	}
	
	*cabeza = nuevo;
}

//MOSTRAR LISTA
void mostrarlista(lista *cabeza){
	lista aux= *cabeza;
	printf("\nLista de Numeros de Stormer: ");
	while(aux){
		printf("%d  ",aux->dato);
		aux=aux->sgte;
	}
}

int main(){
	pila top = NULL, topAux = NULL;
	lista cabeza = NULL;
	int n, a, cont; 
	
	for (n = 1; n <= 50; n++){
		int ec, i, p;
		ec = pow(n, 2) + 1; // primera ecuacion (n^2 + 1)
		
		printf ("\n Numero: %d", n); // se muestra el numero que queremos saber si es o no se un numero de Stormer
		printf ("\n (n^2 + 1)  =  (%d^2 + 1)  =  %d", n, ec); // se muestra el resultado de (n^2 + 1)
		printf ("\n\n");
		printf (" Factores primos de %d =  ", ec);
		
		for (i = 2; ec > 1; i++){       // Con este for
			while (ec % i == 0){        // y este while
				printf ("%d", i);    // podemos econtrar los factores primos del numero resultante de (n^2 + 1)
				ec = ec / i;            // Se divide este numero por el valor de "i" para ahora analizar el cociente
				if (ec != 1) printf(" * ");
			}
		}
	
		p = i-1;
		printf ("\n Factor primo mas grande: %d", p);
		printf ("\n\n Se comprueba si  p >= 2n");
			
		if (p >= 2*n){            // Caso en el que se cumpla que p >= 2n
			printf ("\n Se cumple que %d >= 2 * %d", p, n);
			printf ("\n Entonces %d SI es un numero de Stormer", n);
			push_lista(&cabeza,n);   // Se inserta el dato en la lista en caso de que el numero sea un numero de Stormer
		}
		
		else{                     // Caso en el que NO se cumpla que p >= 2n
			printf ("\n No se cumple que %d >= 2 * %d", p, n);
			printf ("\n Entonces %d NO es un numero de Stormer", n);
			cont = 0;
			for(a = 1; a <= n; a++){     // for y contador para saber
				if(n % a == 0) cont++;   // si el dato es un numero primo
			}
			if (cont == 2) push_pila(&top,n);			  // Se inserta el dato en la pila en caso de que el numero NO sea un numero de Stormer y sea un numero primo
		}                                                 // El número es primo si el contador es igual a 2 (se puede dividir solo dos veces, por 1 y por sí mismo) 
		printf ("\n\n------------------------------------\n");
	}
	
	
	//-----------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------
	
	
	// Mostrando los datos de la pila
	printf ("Pila de No Aceptados: ");
	while(top){
		push_pila(&topAux,top->dato);   // Para mostrar los datos de la pila de No Aceptados, primero debemos guardar el dato en una pila auxiliar
		printf("%d  ",pop_pila(&top));  // Luego se muestra el dato eliminado de la pila original
	}
	while(topAux){			// Devolvemos los datos de la pila auxiliar a la pila original
		push_pila(&top,topAux->dato);
		pop_pila(&topAux);
	}
	
	// Mostrando los datos de la lista
	mostrarlista(&cabeza);
	
	return 0;
}
