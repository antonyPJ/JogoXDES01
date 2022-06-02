#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int i, k, x, y, altura = 20, largura = 20, comidaX, comidaY, tecla, fimloop;
int caudax[100], tailY[100];
int chkcauda;


void tabuleiro() {
    system("cls");
    for(int i = 0; i < altura; i++) {
      printf("#");
        for(int k = 0; k < largura; k++) {
            if(i == 0 || i == altura-1) {
                printf("#");
            }else{
                    if (i == x && k == y) { 
                        printf("0");
                    } else if (i == comidaX && k == comidaY) { 
                        printf("*");
                    } else { 
                        printf(" ");
                    }
            }
        }
    printf("#\n");
  }
}
void comida() {
    fimloop = 0;

    // coordenadas da cobra
    x = largura / 2;
    y = altura / 2;

    // coordenadas da comida
    comidaX = rand() % largura;
    comidaY = rand() % altura;  
   
}

void controle() {
    if (kbhit()) {
        switch (getch()) {
        case 'w':
            tecla = 1;
            break;
        case 'a':
            tecla = 2;
            break;
        case 's':
            tecla = 3;
            break;
        case 'd':
            tecla = 4;
            break;
        default:
            break;
        }
    }
}

void gameloop() {
    Sleep(0.01);
    switch (tecla) {
    case 1:
        x--;
        break;
    case 2:
        y--;
        break;
    case 3:
        x++;
        break;
    case 4:
        y++;
        break;
    default:
        break;
    }

    // se a cobra ultrapassar os limites do tabuleiro acaba o loop
    if (x < 0 || x > largura || y < 0 || y > altura) fimloop = 1;

    // se a cobra chegar nas mesmas coordenadas que a comida gerar nova comida
    if (x == comidaX && y == comidaY) {
        comidaX = rand() % largura;
        comidaY = rand() % altura;     
    }
}

void main() {
    comida();
    while (!fimloop) {
        tabuleiro();
        controle();
        gameloop();
    }
}