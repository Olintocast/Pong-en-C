/* Solo se puede mover una paleta a la vez. Al llegar a las esquinas ya no
pueden seguir moviendo */

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

int color_del_fondo = 15;

Paletas paleta1 = {10, 220, 20, 310, 9};
Paletas paleta2 = {620, 220, 630, 310, 9};

/* Prototipos de funciones generales */
void inicializar_graficos(void);
void fondo(int color);

/*  Prototipos de funciones del juego */
void dibujar_paleta1(void);
void dibujar_paleta2(void);
void borrar_paleta1(void);
void borrar_paleta2(void);

void main(){
	/* Inicio del modo grafico */
	inicializar_graficos();

	/* Fondo */
	fondo(color_del_fondo);

	/* Dibuja las paletas */
	dibujar_paleta1(); dibujar_paleta2();

	while(1){
		if(kbhit()){
			int c = getch();
			int cambio; /* Para sumar o restar a las coordenadas Y */

			/* Controles de la paleta 1 */
			if(c==87 || c==119 || c==83 || c==115){ /* W o w o S o s*/
				if(paleta1.y1 > 10){

					/* Se borra la paleta */
					borrar_paleta1();

					/* Se actualizan coordenadas */
					if(c==87 || c==119) cambio = -5; else cambio = 5;
					paleta1.y1 -= 5;
					paleta1.y2 -= 5;

					/* Se redibuja */
					dibujar_paleta1();
				}
			}

			/* Controles de la paleta 2 */
			if(c==72 || c==80){ /* Flecha arriba o flecha abajo*/
				if(paleta2.y1 > 10 && paleta2.y2 < 470){
					/* Se borra la paleta */
					borrar_paleta2();

					/* Se actualizan coordenadas */
					if(c==72) cambio = -5; else cambio = 5;
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

void dibujar_paleta1(void){
	setfillstyle(1, paleta1.color);
	bar(paleta1.x1, paleta1.y1, paleta1.x2, paleta1.y2);
}

void dibujar_paleta2(void){
	setfillstyle(1, paleta2.color);
	bar(paleta2.x1, paleta2.y1, paleta2.x2, paleta2.y2);
}

void borrar_paleta1(void){
	setfillstyle(1, color_del_fondo);
	bar(paleta1.x1, paleta1.y1, paleta1.x2, paleta1.y2);
}

void borrar_paleta2(void){
	setfillstyle(1, color_del_fondo);
	bar(paleta2.x1, paleta2.y1, paleta2.x2, paleta2.y2);
}