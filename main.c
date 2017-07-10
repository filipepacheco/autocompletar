#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "palavra.h"

int main(int argc, char *argv[])
{
    if (argc!=5)
    {
        printf ("Numero incorreto de parametros.\nExemplo de chamada: autocompletar wiktionary.txt consulta.txt saida.txt 5");
        return 0;
    }
    //abre os arquivos de entrada, processamento e saída.
    FILE *wiktionary = fopen(argv[1], "r");
    if(!wiktionary)
    {
        printf("Nao foi possivel abrir o arquivo %s", argv[1]);
        return 0;
    }
    FILE *consulta = fopen(argv[2], "r");
    if(!consulta)
    {
        printf("Nao foi possivel abrir o arquivo %s", argv[2]);
        return 0;
    }

    fseek(consulta, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(consulta);
    if (len < 1)
    {
        printf("Arquivo de consulta vazio.");
        return 0;
    }
    rewind(consulta);

    FILE *saida = fopen(argv[3], "w+");
    if(!saida)
    {
        printf("Nao foi possivel abrir o arquivo %s", argv[3]);
        return 0;
    }

    //declaracao da lista de palavras de entrada
    ListaPalavra *listaEntrada = inicializaLista();
    //pega o numero maximo
    int maximo = atoi(argv[4]);
    //declara o relogio para calcular o tempo
    clock_t start, elapsed;
    //preenche a lista de entrada com o arquivo de consulta
    listaEntrada = preencheListaPalavras(listaEntrada, consulta);
    //fecha o arquivo pois nao sera mais necessario
    fclose(consulta);
    //inicia o relogio
    start = clock();
    //passa o arquivo de palavras, o numero maximo e a lista que sera preenchida
    preencheListaPrevisoes(wiktionary, maximo, listaEntrada);
    //para o relogio para marcar o tempo de processamento
    elapsed = 1000 * (clock() - start) / (CLOCKS_PER_SEC);
    //arquivo com as palavras e pesos nao sera mais necessario
    fclose(wiktionary);
    //passa a lista e o arquivo de saida para imprimir o resultado
    imprimeSaida(listaEntrada, saida);
    //salva no arquivo de said o tempo de processamento
    fprintf(saida, "\nTempo: %ldms", elapsed);
    //recha o arquivo
    fclose(saida);
    //retorna sucesso
    return 1;
}
