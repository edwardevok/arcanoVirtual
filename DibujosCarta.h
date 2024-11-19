/* Indicaciones para el manejo del TAD
funciones a usar:
	dibujarCarta() dibuja una sola carta pasada por parametro, y la ubicacion que se pide.
	sus parametros son :(por orden de izq a der) 
			carta a dibujar, 
			posicion (0,1,2) desplazamiento sobre eje x,
	 		flag :  1 para primer uso, 2 para siguientes uso(usos de seguido)
	 		
	barajarYTirar(): se usa para mezclar las cartas y devuelve efecto visual y una variable de tipo tCartasResultantes, con las 3 cartas que salieron
	
	mostrarTresCartas(tCartasResultantes): sirve para mostrar las 3 cartas que se pasen por parametro en forma de variable de tipo tCartasResultantes
		util para al tomar el archivo de registros de lecturas usarlo para imprimir las cartas
		
		
TENER EN CUENTA:
	este TAD incluye un nuevo tipo de variable, tCartasResultantes, por lo que NO se debe ni tiene que crear con typedef , el TAD lo incluye, usenlo como cualquier tipo
	
	chau me voy a dormir la siesta*/ 
	
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct{
	int carta1, carta2, carta3;
}tCartasResultantes;


//delaracion / parte publica

void dibujarCarta(int, int, int);
tCartasResultantes barajarYTirar();
void gotoxy(int, int);
void setColor(int color);
COORD obtenerPosicionCursor();
void mostrarTresCartas(tCartasResultantes); //esta funcion se va a usar para mostrar las cartas pasando por parametro, util para visualizar en el registro de lecturas

//implementacion / parte privada

void dibujarCarta(int pCarta, int pOrden, int flag){ //colocar valor 1 en la primer iteracion
	COORD coorActual = obtenerPosicionCursor();
	int y;
	if (flag == 1){
		y = coorActual.Y +1;  // para que la impresion parta un renglon abajo de donde estaba el cursor	y no interfiera con lo que esta ya escrito
		//para ayudar a que al mostrar el registro de lecturas de tarot se pueda mostrar las cartas de cada participante registrado
	}
	else{
		y = coorActual.Y -6;//imprime 6 niveles debajo, que 6 es el alto de la carta, asi la imprime de forma contigua
	}
	int x = 20 * pOrden;
	gotoxy (x,y);
	printf("----------\n");
	switch (pCarta){
		case 1 :{
			gotoxy(x,y+1);
			printf("|        |\n");
			gotoxy(x,y+2);
    		printf("|   EL   |\n");			
			gotoxy(x,y+3);
    		printf("|  MAGO  |\n");
			gotoxy(x,y+4);
    		printf("|        |\n");			
			break;
		}
		case 2:{
 			gotoxy(x,y+1);
  			printf("|   LA   |\n");
			gotoxy(x,y+2);
    		printf("| SACER- |\n");
			gotoxy(x,y+3);
    		printf("| DOTISA |\n");
			gotoxy(x,y+4);
    		printf("|        |\n");			
			break;
		}
		case 3:{
 			gotoxy(x,y+1);
  			printf("|   EL   |\n");
			gotoxy(x,y+2);
    		printf("| EMPERA-|\n");
			gotoxy(x,y+3);
    		printf("|  DOR   |\n");
			gotoxy(x,y+4);
    		printf("|        |\n");			
			break;
		}
		case 4:{
 			gotoxy(x,y+1);
  			printf("|   LA   |\n");
			gotoxy(x,y+2);
    		printf("| EMPERA-|\n");
			gotoxy(x,y+3);
    		printf("|  TRIZ  |\n");
			gotoxy(x,y+4);
    		printf("|        |\n");			
			break;
		}
		case 5:{
 			gotoxy(x,y+1);
  			printf("|   EL   |\n");
			gotoxy(x,y+2);
    		printf("| HIERO- |\n");
			gotoxy(x,y+3);
    		printf("| FANTE  |\n");
			gotoxy(x,y+4);
    		printf("|        |\n");			
			break;
		}
		case 6:{
			gotoxy(x,y+1);
  			printf("|   LOS  |\n");
			gotoxy(x,y+2);
    		printf("|ENAMORA-|\n");
			gotoxy(x,y+3);
    		printf("|  DOS   |\n");
			gotoxy(x,y+4);
    		printf("|        |\n");	
			break;
		}
		case 7:{
			gotoxy(x,y+1);
  			printf("|        |\n");
			gotoxy(x,y+2);
    		printf("|   LA   |\n");
			gotoxy(x,y+3);
    		printf("| FUERZA |\n");
			gotoxy(x,y+4);
    		printf("|        |\n");	
			break;
		}
		case 8:{
			gotoxy(x,y+1);
			printf("|        |\n");
			gotoxy(x,y+2);
    		printf("|   EL   |\n");
			gotoxy(x,y+3);
    		printf("|  CARRO |\n");
			gotoxy(x,y+4);
    		printf("|        |\n");	
			break;
		}
		case 9:{
			gotoxy(x,y+1);
  			printf("|   EL   |\n");
			gotoxy(x,y+2);
    		printf("| ERMITA-|\n");
			gotoxy(x,y+3);
    		printf("|   NIO  |\n");
			gotoxy(x,y+4);
    		printf("|        |\n");	
			break;
		}
		case 10:{
			gotoxy(x,y+1);
  			printf("|   LA   |\n");
			gotoxy(x,y+2);
    		printf("|  RUEDA |\n");
			gotoxy(x,y+3);
    		printf("|  DE LA |\n");
			gotoxy(x,y+4);
    		printf("| FORTUNA|\n");
			break;
		}
	}
	gotoxy(x,y+5);
	printf("----------\n");
}

tCartasResultantes barajarYTirar(){
	srand(time(NULL));
	tCartasResultantes cartas;
	int carta, i;
	long int sleep = 70000;
	//carta 1
	for (i=0; i < 15; i++){
		carta = (rand() % 5) + 1;//carta aleatoria/  va +1 para que sea numero del 1 al 10
		if (i == 0){	
			setColor((rand() % 14) + 1);
			dibujarCarta(carta, 0, 1);//se ejecuta por primera vez/ rand da un valor desde 0 a 9 en este caso
		}
		else{
			setColor((rand() % 15) + 1);//color aleatorio del 1 al 15
			dibujarCarta(carta, 0, 2);//ya es una segunda ejecucion
		}
		cartas.carta1 = carta;
		usleep (sleep);
	}
	//carta 2
	for (i=0; i < 15; i++){
		carta = (rand() % 5) + 1;//carta aleatoria
		if(carta != cartas.carta1){
			setColor((rand() % 15) + 1);//color aleatorio del 1 al 15
			dibujarCarta(carta, 1, 2);//se ejecura por segunda vez, va 2 / tambien se actualiza posicion
			usleep (sleep);
			cartas.carta2 = carta;
		}
	}
	//carta 3
	for (i=0; i < 15; i++){
		setColor((rand() % 15) + 1);//color aleatorio del 1 al 15
		carta = (rand() % 5) + 1;//carta aleatoria
		if(carta != cartas.carta1  && carta != cartas.carta2){
			dibujarCarta(carta, 2, 2);//se ejecura por tercera vez, va 2/ tambien se actualiza posicion 
			cartas.carta3 = carta;
		}
		usleep (sleep);
	}
	setColor(7);//vuelve a blanco
	return cartas;
}

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD obtenerPosicionCursor(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.dwCursorPosition;
}

void setColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void mostrarTresCartas(tCartasResultantes pCartas){
	dibujarCarta(pCartas.carta1, 0, 1);
	dibujarCarta(pCartas.carta2, 1, 2);
	dibujarCarta(pCartas.carta3, 2, 2);
}

	