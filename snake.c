#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Variáveis que serão usadas no programa
int x, y, altura = 20, largura = 20, comidaX, comidaY, pontos, recorde, fimloop;
int caudaX[100], caudaY[100];
int chkcauda;

FILE *arq; 

// Struct usado para armazenar o nome da pessoa que tem a maior pontuação
struct ranking {
    char nome[20];
};
struct ranking pessoa;

// Função responsável por criar as bordas do tabuleiro, a cobra "@", sua cauda "o", a comida "*"
void tabuleiro() {
    arq=fopen("recorde.txt", "r");
    fscanf(arq, "%d%s", &recorde, &pessoa.nome);
    fclose(arq);

    system("cls");
    // Printa as bordas laterais
    for(int i = 0; i < altura; i++) {
        printf("#");
        for(int k = 0; k < largura; k++) {
            // Printa as bordas superiores e inferiores
            if(i == 0 || i == altura-1) {
                printf("#");
            }else{
                if (i == x && k == y) { 
                    printf("@");
                } else if (i == comidaX && k == comidaY) { 
                    printf("*");
                } else { 
                    int print = 0;
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
        printf("#\n");
    }
    printf("Pontos: %d   Recorde: %d  -  %s\n\n", pontos, recorde, pessoa.nome);
}

// Função responsável por estabelecer as coordenadas da cobra, e da comida
void comida() {
    fimloop = 0;
    pontos = 0;

    // Coordenadas da cobra
    x = largura / 2;
    y = altura / 2;

    // Coordenadas da comida randomizadas
    comidaX = rand() % largura;
    comidaY = rand() % altura; 
   
}

// Função responsável por fazer o loop do jogo
void gameloop(int * tecla) {  
    // Estabelece a cauda e suas coordenadas
    for (int i = chkcauda; i>0; i--) {
        caudaX[i] = caudaX[i-1];
        caudaY[i] = caudaY[i-1];
    }
    caudaX[0] = x;
    caudaY[0] = y;
            break;
        case 's':
            *tecla = 3;
            break;
        case 'd':
            *tecla = 4;
            break;
        case 'y':
            fimloop = 1;
            break;
        default:
            break;
        }
    }

    switch (*tecla) {
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
        pontos++; 
        chkcauda++;
    }
}

int main() {
    int ptrTecla;
    inicio:
        comida();
        // Enquanto a variável fimloop estabelecida na função comida for 0 o loop do jogo contínua
        while (fimloop == 0) {
            tabuleiro();
            gameloop(&ptrTecla);
            // Se os pontos forem maior que o recorde ele vai se atualizando em tempo real sobreescrevendo o arquivo recorde.txt
            if (pontos>recorde) {
                arq=fopen("recorde.txt", "w");
                fprintf(arq,"%d\n",pontos);
                fclose(arq);
            }
        }
        // Se os pontos forem iguais ao recorde será pedido o nome do jogador após o fim do loop, e será estabelecido um novo recorde
        // printando então os pontos e nome do jogador no arquivo recorde.txt
        if (pontos == recorde) {
            printf("Digite seu nome: \n");
            scanf("%s", &pessoa.nome);
            arq=fopen("recorde.txt", "w");
            fprintf(arq,"%d %s", pontos, pessoa.nome);
            fclose(arq);
        }
        // Pede input do usuário se deseja jogar denovo voltando então ao ínicio do loop
        char replay;
        printf("Jogar novamente? Pressione Y: \n");
        while (fimloop == 1) {
            scanf("%c", &replay);
            if(replay=='y'||replay=='Y') {
                chkcauda = 0;
                Sleep(500);
                goto inicio;
            }
        }
}