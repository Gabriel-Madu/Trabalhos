#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#define NUM_PALAVRAS 16
#define TAM 100

char const tabelaDePalavras[NUM_PALAVRAS][TAM] = {
    "BATATA$É um tubérculo",
    "AIPIM$Usa-se para fazer sagu",
    "COMPUTACAO$Melhor curso do mundo",
    "CHIMARRAO$Se toma numa cuia",
    "LAGARTO$Lacoste de elo baixo",
    "MARACUJA$Parece sua cara quando acorda",
    "SOCORRO$Pedido de ajuda",
    "TATU$Tem na terra e no seu nariz",
    "FLORESTA$Amazônia",
    "ARARA$Papagaio vip",
    "PNEUMOULTRAMICROSCOPICOSSILICOVULCANOCONIOTICO$Maior palavra da língua portuguesa",
    "DINOSSAUROS$Extintos há milhões de anos",
    "ARGENTINA$Último país campeão do mundo de futebol",
    "PLAYSTATION2$Console mais vendido do mundo",
    "SUPERMAN$Herói mais famoso das HQ's",
    "QUIROPRAXIA$Estrala ossos"
};

typedef struct{
    char palavraEscolhida[TAM];
    char palavraImpressa[TAM];
    char dica[TAM];
    int letrasRestantes;
    int chancesRestantes;
} MatchData;

MatchData Forca;
char letraRepetida[TAM];
int lugar = 0;

void inicializarDados(MatchData *dest);
void processarLetra(MatchData *data, char letra);

int main(){

    system ("chcp 65001 > NUL");
    inicializarDados(&Forca);
    char c;
    
    for(;;){
        printf("Dica: %s", Forca.dica);
        printf("\nChances Restantes: %d | Letras Restantes: %d", Forca.chancesRestantes, Forca.letrasRestantes);
        printf("\n%s", Forca.palavraImpressa);
        printf("\nPalpite: ");
        scanf("%c", &c);
        getchar();
        c = toupper(c);

        switch(c){
            case '0':
                exit(0);
            default:
                system("cls");
                processarLetra(&Forca, c);
        }
    }
}

void inicializarDados(MatchData *dest){

    int dadoAleatorio, tamanho, i;
    char *palavraEscolhida, *dica, palavraSorteada[TAM];

    srand(time(NULL));
    dadoAleatorio = rand() % NUM_PALAVRAS;
    strcpy(palavraSorteada, tabelaDePalavras[dadoAleatorio]);
    palavraEscolhida = strtok(palavraSorteada, "$");
    tamanho = strlen(palavraEscolhida);
    dica = strtok(NULL, "");
    dest->letrasRestantes = strlen(palavraEscolhida);
    dest->chancesRestantes = 10;
    strcpy(dest->dica, dica);
    strcpy(dest->palavraEscolhida, palavraEscolhida);
    
    for(i = 0; i < tamanho; i++){
        dest->palavraImpressa[i] = '-';
    }
}

void processarLetra(MatchData *data, char letra){

    int i, tamanho = strlen(data->palavraImpressa), teste = 0, teste2 = 0;

    for(i = 0; i < (lugar + 1); i++){
        if(letraRepetida[i] == letra)
            teste2++;
    }

    letraRepetida[lugar] = letra;
    lugar++;

    for(i = 0; i < tamanho; i++){
        if(letra == data->palavraEscolhida[i]){
            if(data->palavraImpressa[i] == letra){
                data->letrasRestantes++;
            }
            data->palavraImpressa[i] = letra;
            data->letrasRestantes--;
            teste++;
        }
    }

    if(teste2 != 0){
        printf("Essa letra já foi utilizada\n");
        data->chancesRestantes++;
        if(teste != 0)
            data->chancesRestantes--;
    }

    if(teste == 0){
        data->chancesRestantes--;
        if(data->chancesRestantes == 0){
            printf("A palavra era %s.\nVocê perdeu!", data->palavraEscolhida);
            exit(0);
        }
    }

    if(data->letrasRestantes == 0){
        printf("A palavra era %s.\nParabéns, você venceu!", data->palavraImpressa);
        exit(0);
    }
}