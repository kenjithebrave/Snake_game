#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

// Definições
#define LARGURA 30
#define ALTURA 10

int gameOver;
int x, y, frutaX, frutaY, pontuacao, maiorpontuacao = 0;
int caudaX[100], caudaY[100];
int nCauda;
enum Direcao { STOP = 0, ESQUERDA, DIREITA, CIMA, BAIXO };
enum Direcao direcao;

// Função para configuração inicial do jogo
void Inicializar() {
    gameOver = 0;
    direcao = STOP;
    x = LARGURA / 2;
    y = ALTURA / 2;
    frutaX = rand() % LARGURA;
    frutaY = rand() % ALTURA;
    pontuacao = 0;
    nCauda = 0;
}

// Função para desenhar o campo de jogo
void Desenhar() {
    system("cls");
    for (int i = 0; i < LARGURA + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("O");
            else if (i == frutaY && j == frutaX)
                printf("F");
            else {
                int isCauda = 0;
                for (int k = 0; k < nCauda; k++) {
                    if (caudaX[k] == j && caudaY[k] == i) {
                        printf("o");
                        isCauda = 1;
                    }
                }
                if (isCauda == 0)
                    printf(" ");
            }
            if (j == LARGURA - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < LARGURA + 2; i++)
        printf("#");
    printf("\n");
    printf("\n");
    printf("Pontuacao:%d", pontuacao);
    
    if(pontuacao > maiorpontuacao){
    	maiorpontuacao = pontuacao;
    	maiorpontuacao++;
	}
	printf("\n");
	printf("\n");
	printf("Recorde: %d", maiorpontuacao);
}

// Função para capturar entrada do teclado
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            direcao = ESQUERDA;
            break;
        case 'd':
            direcao = DIREITA;
            break;
        case 'w':
            direcao = CIMA;
            break;
        case 's':
            direcao = BAIXO;
            break;
        case 'x':
            gameOver = 1;
            break;
        }
    }
}

// Função principal do jogo
void JogoLoop() {
    while (!gameOver) {
        Desenhar();
        Input();

        // Lógica de movimento
        int prevX = caudaX[0];
        int prevY = caudaY[0];
        int prev2X, prev2Y;
        caudaX[0] = x;
        caudaY[0] = y;
        for (int i = 1; i < nCauda; i++) {
            prev2X = caudaX[i];
            prev2Y = caudaY[i];
            caudaX[i] = prevX;
            caudaY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        switch (direcao) {
        case ESQUERDA:
            x--;
            break;
        case DIREITA:
            x++;
            break;
        case CIMA:
            y--;
            break;
        case BAIXO:
            y++;
            break;
        default:
            break;
        }

        // Colisão com parede
        if (x >= LARGURA || x < 0 || y >= ALTURA || y < 0)
            gameOver = 1;

        // Colisão com a fruta
        if (x == frutaX && y == frutaY) {
            pontuacao += 10;
            frutaX = rand() % LARGURA;
            frutaY = rand() % ALTURA;
            nCauda++;
        }

        // Colisão com a própria cauda
        for (int i = 0; i < nCauda; i++)
            if (caudaX[i] == x && caudaY[i] == y)
                gameOver = 1;

        Sleep(150); // Controla a velocidade do jogo
    }
}

int main() {
    Inicializar();
    JogoLoop();
    return 0;
}