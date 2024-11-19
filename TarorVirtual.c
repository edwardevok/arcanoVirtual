//programa principal

#include "DibujosCarta.h"
#include "mostrarInterpretacion.h"
#include <locale.h>


typedef char tString50[50];

typedef struct{
	tString50 nombreYAp;
	short edad;
}tDatosJugador;

typedef struct{
	tDatosJugador datosJugador;
	tCartasResultantes cartasResultantes;
}tDatosTirada;

typedef struct nodo{
	tDatosTirada datosTirada;
	struct nodo* siguiente;
}tNodoReg;

typedef struct{
	tNodoReg* principio;
	tNodoReg* final;
}tColaReg;

void abrirArchivoAgregar(FILE**);
void abrirArchivoLeer(FILE**);
void recuperarRegistro(FILE*);
void cerrarArch(FILE**);
void guardarRegEnArch(FILE**, tDatosTirada);
tDatosJugador pedirDatosJug();
void registrarTirada();

void inicializarCola();
void agregarRegistroEnCola(tDatosTirada);
bool colaVacia();

void mostrarRegistros();

void menu();
int concatenarCartas(tCartasResultantes pCartasResultantes);

tColaReg colaReg;

FILE* archRegistroTirada;

int main(){
	setlocale(LC_ALL, "spanish");
	menu();
}

void abrirArchivoAgregar(FILE** pArch){
	*pArch = fopen("registroTiradas.dat", "ab");
}

void abrirArchivoLeer(FILE** pArch){
	*pArch = fopen("registroTiradas.dat", "rb");
}

void recuperarRegistro(FILE* pArch){
	inicializarCola();
	abrirArchivoLeer(&archRegistroTirada);
	tDatosTirada regDatos;
	fread(&regDatos, sizeof(tDatosTirada), 1, archRegistroTirada);
	while(!feof(archRegistroTirada)){
		agregarRegistroEnCola(regDatos);
		fread(&regDatos, sizeof(tDatosTirada), 1, archRegistroTirada);	
	}
	cerrarArch(&archRegistroTirada);
	
}

void cerrarArch(FILE** pArch){
	fclose(*pArch);
}

void guardarRegEnArch(FILE** pArch, tDatosTirada pDatos){
	fwrite(&pDatos, sizeof(tDatosTirada), 1, archRegistroTirada);
}

tDatosJugador pedirDatosJug(){
	tDatosJugador datos;
	printf("Ingrese Nombre y Apellido: ");
	fflush(stdin);
	gets (datos.nombreYAp);
	printf("Ingrese su edad: ");
	scanf("%d", &datos.edad);
	return datos;
}

void registrarTirada(){
	abrirArchivoAgregar(&archRegistroTirada);
	
	tDatosJugador datosJugdor = pedirDatosJug();
	tCartasResultantes cartasResltantes = barajarYTirar();//devulve un struct compuesto de 3 string, a la vez muestra la animacion

	tDatosTirada datosTirada;
	datosTirada.datosJugador = datosJugdor;//asignacion del struct, se rellena con los datos del jugador y las cartas que le salieron
	datosTirada.cartasResultantes = cartasResltantes;//asignacion del struct
	
	guardarRegEnArch(&archRegistroTirada, datosTirada);//guarda el registro en el archivo
	
	int codTirada = concatenarCartas(cartasResltantes);//a partir de 3 int llega a un numero de tres cifras, que encuadra con el archivo de significados
	setColor(4);
	mostrarInterpretacion(codTirada);
	setColor(7);
	cerrarArch(&archRegistroTirada);
	
}

//implementacion de funciones para la cola dinamica

void inicializarCola(){
	colaReg.final = NULL;
	colaReg.principio = NULL;	
}

void agregarRegistroEnCola(tDatosTirada pDatos){
	tNodoReg* nuevoReg = (tNodoReg*) malloc (sizeof(tNodoReg));
	if (colaVacia(colaReg)){
		nuevoReg->datosTirada = pDatos;
		nuevoReg->siguiente = NULL;
		colaReg.final = nuevoReg;
		colaReg.principio = nuevoReg;
	}
	else{
		nuevoReg->datosTirada = pDatos;
		nuevoReg->siguiente = NULL; 
		colaReg.final->siguiente = nuevoReg;
		colaReg.final = nuevoReg;
	}
}

bool colaVacia(tColaReg pColaReg){
	return (colaReg.principio == NULL && colaReg.final == NULL);
}

void mostrarRegistros(){
	recuperarRegistro(archRegistroTirada);
	setColor(5);
	printf("\t\t\t***Registro de jugadores***\n\n");
	if(!colaVacia(colaReg)){
		tNodoReg* colaAux = colaReg.principio;
		while(colaAux != NULL){
			setColor(4);
			printf("\n\t\tNombre del jugador: %s\n\t\tEdad %d a%cos\n", colaAux->datosTirada.datosJugador.nombreYAp, colaAux->datosTirada.datosJugador.edad, 164);
			printf("Resultado obtenido:\n");
			//muestra las cartas obtenidas
			setColor(2);
			dibujarCarta(colaAux->datosTirada.cartasResultantes.carta1, 1, 1); //flag = 1, primerta muestra
			dibujarCarta(colaAux->datosTirada.cartasResultantes.carta2, 2, 2); //flag = 1, segunda muestra
			dibujarCarta(colaAux->datosTirada.cartasResultantes.carta3, 3, 3); //flag = 1, tercera muestra
			//muestra la interpretacion
			setColor(5);
			int codTirada = concatenarCartas(colaAux->datosTirada.cartasResultantes);
			mostrarInterpretacion(codTirada);
			colaAux = colaAux->siguiente;
			setColor(7);
			printf("\n------------------------------------------------------------------------------------------------\n");
		}
	}
	else{
		printf("\n**No existen registros de jugadores**\n");
		sleep(2);
		system("cls");
		menu();
	}
}

void menu(){
	int op;
	setColor(3);
	printf("\n\t\t\t\t****BIENVENIDO AL ARCANO VIRTUAL****\n\n");
	printf("\t\t1- Iniciar tirada\n\t\t2- Ver registro de jugadores\n\t\t3- Salir\n");
	setColor(7);
	scanf("%d", &op);
	switch (op){
		case 1: {
			system("cls");
			registrarTirada();
			menu();
			break;
		}
		case 2 :{
			system("cls");
			mostrarRegistros();
			menu();
			break;
		}
		case 3: {
			system("cls");
			printf("\n\t\t**Gracias por haber participado en nustro Tarot virtual**\n");
			break;
		}
	}
}

int concatenarCartas(tCartasResultantes pCartasResultantes){
	return ((pCartasResultantes.carta1 * 100) + (pCartasResultantes.carta2 * 10) + pCartasResultantes.carta3);
}

