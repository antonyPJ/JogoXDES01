#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Variáveis que serão usadas no programa
int i, k, j, x, y, altura = 20, largura = 20, comidaX, comidaY, tecla, fimloop;
int caudaX[100], caudaY[100];
int chkcauda, print;

// Função responsável por criar as bordas do tabuleiro, a cobra "@" e sua cauda "o" e a comida "*"
void tabuleiro() {
    system("cls");
    for(int i = 0; i < altura; i++) {
        printf("$");
        for(int k = 0; k < largura; k++) {
            if(i == 0 || i == altura-1) {
                printf("$");
            }else{
                if (i == x && k == y) { 
                    printf("@");
                } else if (i == comidaX && k == comidaY) { 
                    printf("*");
                } else { 
                    print = 0;
                    for (int j = 0; j < chkcauda; j++) {
                        if (caudaX[j] == k && caudaY[j] == i) {
                            printf("o");
                            print = 1;
                        }

                    }
                    if (!print) printf(" ");
                }
            }
        }
        printf("$\n");
  }
}

// Função responsável por estabelecer as coordenadas da cobra, e da comida
void comida() {
    fimloop = 0;

    // Coordenadas da cobra
    x = largura / 2;
    y = altura / 2;

    // Coordenadas da comida randomizadas
    comidaX = rand() % largura;
    comidaY = rand() % altura;  
   
}

// Função responsável por receber o input do usuário
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

// Função responsável por fazer o loop do jogo
void gameloop() {  
    int posX = caudaX[0];
    int posY = caudaY[0];
    int pos2x, pos2y;
    caudaX[0] = y;
    caudaY[0] = x;

    // Estabelece a cauda e suas coordenadas
    for (int i = 1; i<chkcauda; i++) {
        pos2x = caudaX[i];
        pos2y = caudaY[i];
        caudaX[i] = posX;
        caudaY[i] = posY;
        posX = pos2x;
        posY = pos2y;
    }

    Sleep(0.01);

    // Switch recebe a variavel tecla, e adiciona ou subtrai as coordenadas da cobra de acordo com a tecla
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

    // Se a cobra ultrapassar os limites do tabuleiro acaba o loop
    if (x < 1 || x > largura - 2|| y < 0 || y > altura - 1) fimloop = 1;
    
    // Se a cobra encostar em sua cauda acaba o loop
    for (int i = 0; i<chkcauda; i++)
        if (caudaX[i] == y && caudaY[i] == x) fimloop = 1;
            
    // Se a cobra chegar nas mesmas coordenadas que a comida gerar nova comida
    if (x == comidaX && y == comidaY) {
        comidaX = rand() % largura;
        comidaY = rand() % altura;     
        chkcauda++;
    }
}

void main() {
    comida();
    // Enquanto a variável fimloop estabelecida na função comida não for 0 o loop do jogo contínua
    while (!fimloop) {
        tabuleiro();
        controle();
        gameloop();
    }
}