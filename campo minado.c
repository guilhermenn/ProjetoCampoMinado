#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int bomb;
    int open;
    int vizinho;
}celula;


//variáveis globais que serão utilizadas durante o código

celula campominado[10][20];
int l, c, linha = 10, coluna = 20;

//começar a matriz do campo minado

void startcampominado(){
    for(l = 0; l < linha; l++){
        for(c = 0; c < coluna; c++){
            campominado[l][c].bomb = 0;
            campominado[l][c].open = 0;
            campominado[l][c].vizinho = 0;
        }
    }
}

//procedimento de sorteio das posições das bombas 

void randombomb(int n){
    int i;
    srand(time(NULL));
    for(i = 1; i <= n; i++){
        l = rand() % linha;
        c = rand() % coluna;
        if(campominado[l][c].bomb == 0)
            campominado[l][c].bomb = 1;
        else
            i--;
    }
}

//função de validação de coordenadas, sendo 1 para válido e 2 para não válido

int coordenadavalidade(int l, int c){
    if(l >= 0 && l < linha && c >=0 && c < coluna)
        return 1;
    else
        return 0;
}

//função para retornar a quantidade de minas adjacentes considerando as 8 células ao redor de uma posição (vertical, horizontal e diagonais)

int quantbombvizinho(int l, int c){
    int quant = 0;

    if(coordenadavalidade(l - 1, c) && campominado[l-1][c].bomb)
        quant++;
    if(coordenadavalidade(l + 1, c) && campominado[l+1][c].bomb)
        quant++;
    if(coordenadavalidade(l, c - 1) && campominado[l][c-1].bomb)
        quant++;
    if(coordenadavalidade(l, c + 1) && campominado[l][c+1].bomb)
        quant++;
    if(coordenadavalidade(l - 1, c - 1) && campominado[l-1][c-1].bomb)
        quant++;
    if(coordenadavalidade(l - 1, c + 1) && campominado[l-1][c+1].bomb)
        quant++;
    if(coordenadavalidade(l + 1, c - 1) && campominado[l+1][c-1].bomb)
        quant++;
    if(coordenadavalidade(l + 1, c + 1) && campominado[l+1][c+1].bomb)
        quant++;
    return quant;
}

//contador de bombas nas adjacentes

void contarbomb(){
    for(l = 0; l < linha; l++){
        for(c = 0; c < coluna; c++)
            campominado[l][c].vizinho = quantbombvizinho(l, c);
    }
}

//impressão da interface do jogo

void imprimir(){

    printf("\n\n\t   ");
    for (c = 0; c < linha ; c++)
        printf("  %d ", c);
    for (c = linha; c < coluna; c++)
        printf("  %d", c);
    printf("\n");
    for(l = 0; l < linha; l++){
        printf("\t%d  |", l);
        for(c = 0; c < coluna; c++){
            if(campominado[l][c].open){
                if(campominado[l][c].bomb)
                    printf(" * ");
                else
                    printf(" %d ", campominado[l][c].vizinho);
            }
            else
                printf("   ");
            printf("|");
        }
        printf("\n");
    }
}

//procedimento para abrir a coordenada inserida pelo jogador na célula

void opencelula(int l, int c){
    if(coordenadavalidade(l, c) == 1 && campominado[l][c].open == 0){
        campominado[l][c].open = 1;
        if(campominado[l][c].vizinho == 0){
            opencelula(l - 1, c);
            opencelula(l + 1, c);
            opencelula(l, c - 1);
            opencelula(l, c + 1);
            opencelula(l - 1, c - 1);
            opencelula(l + 1, c - 1);
            opencelula(l - 1, c + 1);
            opencelula(l + 1, c + 1);
        }
    }
}

//função para verificar a vitória, onde n > 0 não ganhou ainda e 0 já ganhou

int winner(){
    int quantidade = 0;
    for(l = 0; l < linha; l++){
        for(c = 0; c < coluna; c++){
            if(campominado[l][c].open == 0 && campominado[l][c].bomb == 0)
                quantidade++;
        }
    }
    return quantidade;
}

//procedimento para realizar a leitura das coordenadas 

void play(time_t inicio){
    int linha, coluna;
    time_t fim;
    do{
        imprimir();
        do{
            printf("\nQual celula que deseja revelar?");
            printf("\nLinha (-1 sai):");
            printf("\nColuna:\n");
            scanf("%d%d", &linha, &coluna);

            if(coordenadavalidade(linha, coluna) == 0 || campominado[linha][coluna].open == 1)
                printf("\nCoordenada invalida! ou já aberta");
        }while(coordenadavalidade(linha, coluna) == 0 || campominado[linha][coluna].open == 1);

        opencelula(linha, coluna);
    }while(winner() != 0 && campominado[linha][coluna].bomb == 0);
    
    fim = time(NULL) -inicio;
    if(campominado[linha][coluna].bomb == 1)
        printf("\n\tBOOOM!! Perdeu em %d segundos! \n",fim);

    else
        
        printf("\n\tJá pode entrar para o esquadrão antibombas! Ganhou em %d segundos!",fim);
    
    imprimir();

}

//função main que faz o chamado das outras funções para rodar o jogo

int main(){
    time_t inicio;
    startcampominado();
    randombomb(40);
    contarbomb();
    printf("\n\t\t\t\t\t  CAMPO MINADO\n");
    inicio = time(NULL);
    play(inicio);

    return 0;
}