#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 60

typedef char tString[5000];

typedef struct {
	int codigoTirada;
	tString lectura;
}tInterpretacion;

tInterpretacion interpretaciones[MAX]; 

void completarVector();
int buscarEnVector(int);
void mostrarInterpretacion(int);

FILE* archInterpretacion;


void completarVector(){
	archInterpretacion = fopen("interpretaciones2.txt", "r");	

	if (archInterpretacion != NULL){
		int i;
		for(i=0; i< MAX; i++){
			fscanf(archInterpretacion, "%d %[^\n]s", &interpretaciones[i].codigoTirada, &interpretaciones[i].lectura);
		}
		fclose(archInterpretacion);
	}
	else{
		printf("***ERROR, archivo no abierto***");
		exit(EXIT_FAILURE);
	}
}



int buscarEnVector(int elem){

	int result = -1, posMedia;
	int extInf = 0;
	int extSup = MAX;
	bool encontrado = false;
	
	while (!encontrado && extSup >= extInf){
		posMedia = (extSup + extInf) / 2;
		if (elem == interpretaciones[posMedia].codigoTirada){
			encontrado = true;
		}
		else{
			if(elem > interpretaciones[posMedia].codigoTirada){
				extInf = posMedia + 1;
			}
			else{
				extSup = posMedia - 1;
			}
		}
	}
	if (encontrado) {
		result = posMedia;
	}
	return result;	
}

void mostrarInterpretacion(int pCodTirada){
	completarVector();
	int posInterpretacion = buscarEnVector(pCodTirada);
	
	if(posInterpretacion != -1){
		printf("\nLa interpretacion de tus cartas es: \n**%s**\n", interpretaciones[posInterpretacion].lectura);
	}
	else{
		printf("\nNo se encontro Lectura");
	}
}
