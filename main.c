#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "palavra.h"

int main(int argc, char *argv[]){
    //abre os arquivos de entrada, processamento e saída.
    FILE *wiktionary = fopen("palavras/wiktionary.txt", "r");
    if(!wiktionary){
        printf("Nao foi possivel abrir o arquivo %s", argv[1]);
        return 0;
    }
    FILE *consulta = fopen("palavras/consulta.txt", "r");
    if(!consulta){
        printf("Nao foi possivel abrir o arquivo %s", argv[2]);
        return 0;
    }
    FILE *saida = fopen("palavras/saida.txt", "w+");
    if(!saida){
        printf("Nao foi possivel abrir o arquivo %s", argv[3]);
        return 0;
    }

    ListaPalavra *listaEntrada = inicializaLista(); //lista de palavras de entrada
    int maximo = 5; //atoi(argv[4]);
    clock_t t1 = clock();

    listaEntrada = preencheListaPalavras(listaEntrada, consulta);
    //percorre a lista de palavras de entrada

    if(imprimeSaida(saida, wiktionary, maximo, listaEntrada))
        fprintf(saida, "\nTempo: %lf\n", (double)(clock() - t1) / CLOCKS_PER_SEC);

    fclose(saida);
    fclose(wiktionary);
    fclose(consulta);
    return 1;
}
