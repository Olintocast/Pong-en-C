/* Solo se puede mover una paleta a la vez */

#include <graphics.h>
#include <mouse.h>
#include <conio.h>

typedef struct{
	int x1;
	int y1;
	int x2;
	int y2;
	int color;
} Paletas;

/* Variables configurables del juego */
int color_bola = 8, radio_bola = 7;
int color_del_fondo = 15;

/* Variables que determinan la direccion de la bola */
int cambioX = 2, cambioY = 1;

/* Variables de coordenadas de la bola */
int bolax, bolay;

/* Coordenadas iniciales de las paletas */
Paletas paleta1 = {10, 220, 20, 310, 9};
Paletas paleta2 = {620, 220, 630, 310, 9};

/* Prototipos de funciones generales */
void inicializar_graficos(void);
void fondo(int color);
void fotograma_Inicial(void);

/*  Prototipos de funciones del juego */
void dibujar_paleta1(void);
void dibujar_paleta2(void);
void dibujar_bola(void);

void borrar_paleta1(void);
void borrar_paleta2(void);
void borrar_bola(void);

void pantalla_Derrota(void);

void main(){
	/* Inicio del modo grafico */
	inicializar_graficos();

	/* Fotograma donde comienza el juego */
	fotograma_Inicial();

	/* Bucle del juego. Es un bucle que funciona tanto como escuchador de
	eventos asi como accionador de eventos pasivos */
	while(1){
		/* PARTE PASIVA (se ejecuta aunque no se toque nada) */
		/* Se verifica que la bola no este tocando los limites para moverla */
		if(bolax < 640 && bolax >= 0){
			borrar_bola();

			/* Cambio de direccion si la bola toca los bordes superior o inferior */
			if(bolay <= 0) cambioY = 1;
			if(bolay >= 480) cambioY = -1;

			/* Ccambio de direccion si la bola toca la paleta 1 */
			if(bolax < (22 + radio_bola) && bolay > (paleta1.y1 - radio_bola) && bolay < (paleta1.y2 + radio_bola)){
				cambioX = 2;
			}

            /* Cambio de direccion si la bola toca la paleta 2 */
			if(bolax > (618 - radio_bola) && bolay > (paleta2.y1 - radio_bola) && bolay < (paleta2.y2 + radio_bola)){
				cambioX = -2;
			}

			/* Se actualizan sus coordenadas */
			bolax += cambioX;
			bolay += cambioY;

			dibujar_bola();
		} else{
			/* La bola toco los limites y se termina el juego */
			pantalla_Derrota();
		}

		/* PARTE ESCUCHADORA DE EVENTOS */
		if(kbhit()){
			int c = getch();
			int cambio; /* Para sumar o restar a las coordenadas Y */

			/* Controles de la paleta 1 */
			if(c==87 || c==119 || c==83 || c==115){ /* W o w o S o s*/
				if(c==87 || c==119) cambio = -5; else cambio = 5; /* Se establece el movimiento segun la tecla (arriba/abajo) */
				if(paleta1.y1 + cambio >= 0 && paleta1.y2 + cambio <= 480){ /* Se mueve si hay espacio */
					/* Se borra la paleta */
					borrar_paleta1();

					/* Se actualizan coordenadas */
					paleta1.y1 += cambio;
					paleta1.y2 += cambio;

					/* Se redibuja */
					dibujar_paleta1();
				}
			}

			/* Controles de la paleta 2 */
			if(c==72 || c==80){ /* Flecha arriba o flecha abajo*/
				if(c==72) cambio = -5; else cambio = 5; /* Se establece el movimiento segun la tecla (arriba/abajo) */
				if(paleta2.y1 + cambio >= 0 && paleta2.y2 + cambio <= 480){ /* Se mueve si hay espacio */
					/* Se borra la paleta */
					borrar_paleta2();

					/* Se actualizan coordenadas */
					paleta2.y1 += cambio;
					paleta2.y2 += cambio;

					/* Se redibuja */
					dibujar_paleta2();
				}
			}

			if(c==27) break;
		}
	}

	closegraph();
}

void inicializar_graficos(void){
	int driver=DETECT, modo;

	initgraph(&driver, &modo, "C://TC20//BIN");
	if(graphresult() != 0){
		setcolor(4);
		outtextxy(10, 20, "Error al iniciar el modo grafico");
	}
}

void fondo(int color){
	setfillstyle(1, color);
	bar(0, 0, 640, 480);
}

void fotograma_Inicial(void){
	/* Coordenadas iniciales */
	bolax = 200;
	bolay = 300;

	/* Direccion de la bola */
	cambioX = 2, cambioY = 1;

	/* Dibujo de los elementos */
	/* Fondo */
	fondo(color_del_fondo);

	/* Dibuja las paletas */
	dibujar_paleta1(); dibujar_paleta2();
}

void dibujar_paleta1(void){
	setfillstyle(1, paleta1.color);
	bar(paleta1.x1, paleta1.y1, paleta1.x2, paleta1.y2);
}

void dibujar_paleta2(void){
	setfillstyle(1, paleta2.color);
	bar(paleta2.x1, paleta2.y1, paleta2.x2, paleta2.y2);
}

void dibujar_bola(void){
	setfillstyle(1, color_bola);
	fillellipse(bolax, bolay, radio_bola, radio_bola);
}

void borrar_paleta1(void){
	setfillstyle(1, color_del_fondo);
	bar(paleta1.x1, paleta1.y1, paleta1.x2, paleta1.y2);
}

void borrar_paleta2(void){
	setfillstyle(1, color_del_fondo);
	bar(paleta2.x1, paleta2.y1, paleta2.x2, paleta2.y2);
}

void borrar_bola(void){
	setcolor(15);
	setfillstyle(1, 15);
	fillellipse(bolax, bolay, radio_bola, radio_bola);
}

void pantalla_Derrota(void){
	/* Rectangulo de la pantalla */
	setcolor(1);
	setfillstyle(1, 1);
	bar(145, 150, 530, 280);

	/* Contorno del rectangulo */
	setcolor(9);
	setlinestyle(0, 0, 3);
	rectangle(145, 150, 530, 280);

	/* Texto de derrota */
	setcolor(7);
	settextstyle(1, 0, 5);
	outtextxy(155, 160, "JUEGO TERMINADO");

	/* Texto instructivo */
	settextstyle(1, 0, 2);
	outtextxy(180, 230, "Presiona 'espacio' para reiniciar");

	while(1){
		if(kbhit()){
			int c = getch();
			if(c==32){ /* Tecla presionada: espacio */
				fotograma_Inicial();
				break;
			}
		}
	}
}