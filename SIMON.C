#include<dos.h>
#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<graphics.h>
#include<TIME.H>
 
//####################################
	int puntaje_record=0;
	int puntaje_actual=0;

	int juego_activo=1;
	char generado='0';
	int x=0; //Control de los arreglos

	char nombre_record[10]="DIANA";
	char arreglo_juego[100];
	char arreglo_jugador[100];

	int conta;
//####################################

void clrscr();
void rando();
void efecto(char r);
void esperar(int e);
void poscursor();
void cuadro();
//void poscursor(char x, char y);
int vcx=0;
int vcy=0;
int i=0;
int j=0;

//int coordx=0;
//int coordy=0;

char r=0;
char fila;
char columna;

void clrscr(){
	asm{
		mov ah,06h
		mov bh,09h
		mov al,0
		mov cx,0000H
		mov dx,184FH
		int 10H
	}
}

void poscursor(char x, char y){
	asm{
		mov ah,02h
		mov bh,00h
		mov dh,x
		mov dl,y
		int 10h
	}
}

void cuadro(char f1,char c1, char f2,char c2, char color ){
	asm{
		mov ah,06h
		mov al,00h
		mov cl,f1
		mov ch,c1
		mov dl,f2
		mov dh,c2
		mov bh,color
		int 10h
	}
}

//87 -- rosa
//03 negro-azul
void ventana(){
	cuadro(30, 10, 50, 15,52);
	poscursor(12,35);
	printf("Inicia Juego");
	poscursor(13,40);
	printf("Ok");
}

void iniciomouse(){
	asm{
		mov ax,00h
		int 33h
	}
}

void mostrarmouse(){
	asm{
		mov ax,01h
		int 33h
	}
}

void edomouse(){
	asm{
		mov ax,05h
		int 33h
	}
}

void ir(char x, char y){
     asm{
		mov ah, 02h
		mov bh, 00h
		mov dh, x
		mov dl, y
		int 10h
	 }
}

void fin(){
	asm{
		ret
	}
}

void menusalir(){
	if(vcx >=70){
		if(vcx <= 74){
			if(vcy == 22){
				fin();
			}
		}
	}
}

void meter_mouse(){
	asm{
		mov ax,00h
		int 33h
	}
		espera_click:
		asm{ 
			mov ax,01h
			int 33h

			mov ax,05h
			int 33h

			cmp bx,1 
			je  evaluar
			cmp bx,2 
			je salir
			jmp espera_click
		}

		evaluar:
		asm{
			     	mov ax,dx
			        mov bl,8
			        div bl
					mov fila, al

					mov ax,cx
			        mov bl,8
			        div bl
					mov columna, al
		}
			
		asm{
			cmp fila, 22
			JNE inici //espera_click
			cmp columna, 70
			JB espera_click
			cmp columna, 75
			JB salir
			//JMP espera_click
		}
	inici:
		asm{	
			cmp fila,4
			JNE empieza
			cmp columna,10
			JB espera_click
			cmp columna,17
			JB inicio
			jmp espera_click
			
			
		}
	empieza:
		asm{
			cmp fila,13
			JNE espera_click
			cmp columna,40
			JB espera_click
			cmp columna,42
			JB mostrar
			jmp espera_click
		}
		
	mostrar:
		//interfaz();
		
		goto espera_click;
		
	inicio:
		ventana();
		goto espera_click;
				
	salir:
		fin();
}
//###################################################
void pinta_encabezado(){
	poscursor(2,38);
	printf ("SIMON\n"); 

	poscursor(4,38);
	printf("Record:\n");

	poscursor(5,10);
	printf("Nombre:\n");

	poscursor(5,17);
	printf("%s",nombre_record);

	poscursor(5,30);
	printf("Puntaje:\n");

	poscursor(5,40);
	printf("%d",puntaje_record);

	poscursor(5,50);
	printf("Puntaje Actual:\n");

	poscursor(5,70);
	printf("%d",puntaje_actual);
}

void pinta_todos_colores(){
	cuadro(20,7,35,12,70);
	cuadro(45,7,60,12,20);
	cuadro(20,16,35,21,40);
	cuadro(45,16,60,21,99);
}

void limpia_zona_colores(){
	cuadro(20, 7, 60,21, 11);
}

void pinta_azul(){
	cuadro(45,7,60,12,20);
}

void pinta_verde(){
	cuadro(20,16,35,21,40);
}

void pinta_rojo(){
	cuadro(20,7,35,12,70);
}

void pinta_naranja(){
	cuadro(45,16,60,21,99);
}

char aleatorio(){
	char r;
	asm{
		mov ah,86h
		mov cx,10
		mov dx,10d
		int 15h
		
		mov ah,00h
		int 1ah
		mov ax,dx
		xor dx,dx
		mov cx,4
		div cx
		add dl,'1'
		mov r,dl
	}
	return r;
}

void simon_dice(){
	//Genera un numero aleatorio entre 1 y 4 para decir cual color se enciende
	limpia_zona_colores();
	generado=aleatorio();
	switch(generado){
		case '1':
			pinta_rojo();
			break;
		case '2':
			pinta_azul();
			break;
		case '3':
			pinta_verde();
			break;
		case '4':
			pinta_naranja();
			break;
		default:break;
	}
}

void reproduce_secuencia_previa(){
	for(i=0;i<x;i++){
		limpia_zona_colores();
		sleep(1);
		switch(arreglo_juego[i]){
			case '1':
				pinta_rojo();
				break;
			case '2':
				pinta_azul();
				break;
			case '3':
				pinta_verde();
				break;
			case '4':
				pinta_naranja();
				break;
			default:break;
		}
		sleep(1);
	}
}
//###################################################

void main(void){
	clrscr();
	pinta_encabezado();
	pinta_todos_colores();
	/*
	poscursor(4,10);
	printf("Iniciar\n");
	*/

	poscursor(22,70);
	printf("Salir\n");
	
/*Cambiar el valor del nombre y del puntaje
	memcpy(nombre_record, "MARCO Anto", 10);
	puntaje_record=10;
	puntaje_actual=5;
	pinta_encabezado();
*/
	//Inicio del juego
	printf("%s", "Empezando el juego");
	for(i=3;i>=1;i--){
		printf("%d", i);
		sleep(1);
	}
	//Inicialización del mouse
	iniciomouse();
	mostrarmouse();
	
	
	while(juego_activo==1){
		simon_dice(); //Genera un numero aleatorio
		arreglo_juego[x]=generado; //Almacena el numero generado en el arreglo del juego
		x++; //Incrementa el contador de iteraciones
		//puntaje_actual++;
		//pinta_encabezado();
		reproduce_secuencia_previa(); //Reproduce la secuencia generada
		pinta_todos_colores(); //Pinta todos los colores para ahora esperar los clicks del usuario
		conta=0;
		while(conta<x){ //Mientras el contador de clics correctos sea menor al numero de cuadros
		esperar_click:
			edomouse();
			asm{
				cmp bx, 1 //Si se da clic izquierdo se evalua
				JE evaluar
				JMP esperar_click
			}

			evaluar:
				asm{
					//Se obtiene el valor de la fila y de la columna en la que se dio clic
						mov ax,dx
						mov bl,8
						div bl
						mov fila, al

						mov ax,cx
						mov bl,8
						div bl
						mov columna, al
					//Una vez que se obtuvieron dichos valores, se procede a comparar si esas coordenadas están
					//entre las de cada cuadro
				//Validar que se encuentre entre las filas 7 y 12 para los primeros cuadros
				}
				//Validación del botón salir
				asm{
					cmp fila, 22
					JB validar_filas_1 //espera_click
					cmp columna, 70
					JB validar_columnas_1
					cmp columna, 75
					JMP acaba
				}


				validar_filas_1:
				asm{
					cmp fila, 7
					JB esperar_click
					cmp fila, 12
					JBE validar_columnas_1
					jmp validar_filas_2
				}
						//validación del Rojo (xi=20,yi=7,xf=35,yf=12);
						validar_columnas_1:
						asm{
							cmp columna, 20
							JB esperar_click
							cmp columna, 35
							JBE es_rojo
							JMP validar_columnas_2
						}

						//Validación del Azul (xi=45,yi=7,xf=60,yf=12);
						validar_columnas_2:
						asm{
							cmp columna, 45
							JB esperar_click
							cmp columna, 60
							JBE es_azul
							JMP esperar_click
						}

				//Validar que se encuentre entre las filas 16 y 21 para los otros dos cuadros
				validar_filas_2:
				asm{
					cmp fila, 16
					JB esperar_click
					cmp fila, 21
					JBE validar_columnas_3
					jmp esperar_click
				}

						//validación del Verde (xi=20,yi=16,xf=35,yf=21);
						validar_columnas_3:
						asm{
							cmp columna, 20
							JB esperar_click
							cmp columna, 35
							JBE es_verde
							JMP validar_columnas_4
						}

						//Validación del Naranja (xi=45,yi=16,xf=60,yf=21);
						validar_columnas_4:
						asm{
							cmp columna, 45
							JB esperar_click
							cmp columna, 60
							JBE es_naranja
							JMP esperar_click
						}

				es_rojo://Cuando es rojo el presionado se debe meter un valor 1 al arreglo jugador
					arreglo_jugador[conta]='1';
					conta++;
					asm{
						jmp seguir
					}

				es_azul://Cuando es rojo el presionado se debe meter un valor 2 al arreglo jugador
					arreglo_jugador[conta]='2';
					conta++;
					asm{
						jmp seguir
					}
				
				es_verde://Cuando es rojo el presionado se debe meter un valor 3 al arreglo jugador
					arreglo_jugador[conta]='3';
					conta++;
					asm{
						jmp seguir
					}
				
				es_naranja://Cuando es rojo el presionado se debe meter un valor 4 al arreglo jugador
					arreglo_jugador[conta]='4';
					conta++;
					asm{
						jmp seguir
					}

				seguir:
				//Entra a validar que la secuencia generada por el juego y la secuencia generada por el usuario sean correctas
					if(arreglo_jugador[conta-1]==arreglo_juego[conta-1]){
						asm{
							jmp seguir_2
						}
					}else{
						asm{
							jmp acaba
						}
					}


				seguir_2:
					
			}
			puntaje_actual++;
			pinta_encabezado();
		sleep(1);
	} //Finaliza el while de juego activo
	acaba:
		clrscr();
		poscursor(5,5);
		printf("%s","Se presiono Naranja: Juego Finalizado");
		poscursor(6,5);
		printf("%s", "Puntaje: ");
		printf("%d", puntaje_actual);
		printf("%s", "Arreglo Jugador: ");
		printf("%s", arreglo_jugador);
		printf("%s", "Arreglo Juego: ");
		printf("%s", arreglo_juego);
		getch();
}