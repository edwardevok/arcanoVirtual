#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct{
	int carta1, carta2, carta3;
}tCartasResultantes;


void dibujarCarta(int, int, int);
tCartasResultantes barajarYTirar();
void gotoxy(int, int);
void setColor(int color);
COORD obtenerPosicionCursor();
void mostrarTresCartas(tCartasResultantes); 


void dibujarCarta(int pCarta, int pOrden, int flag){ 
	COORD coorActual = obtenerPosicionCursor();
	int y;
	if (flag == 1){
		y = coorActual.Y +1;  
	}
	else{
		y = coorActual.Y -6;
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
		carta = (rand() % 5) + 1;
		if (i == 0){	
			setColor((rand() % 14) + 1);
			dibujarCarta(carta, 0, 1);
		}
		else{
			setColor((rand() % 15) + 1);
			dibujarCarta(carta, 0, 2);
		}
		cartas.carta1 = carta;
		usleep (sleep);
	}
	//carta 2
	for (i=0; i < 15; i++){
		carta = (rand() % 5) + 1;
		if(carta != cartas.carta1){
			setColor((rand() % 15) + 1);
			dibujarCarta(carta, 1, 2);
			usleep (sleep);
			cartas.carta2 = carta;
		}
	}
	//carta 3
	for (i=0; i < 15; i++){
		setColor((rand() % 15) + 1);
		carta = (rand() % 5) + 1;
		if(carta != cartas.carta1  && carta != cartas.carta2){
			dibujarCarta(carta, 2, 2); 
			cartas.carta3 = carta;
		}
		usleep (sleep);
	}
	setColor(7);
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

	
