#include "palavra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//inicializa a lista de palavras
ListaPalavra* inicializaLista(void)
{
    return NULL;
}

//função padrão de inserção em uma lista simplesmente encadeada.
ListaPalavra* inserePalavra(ListaPalavra* l, Palavra dados)
{
    ListaPalavra* novo;
    ListaPalavra* ant = NULL;
    ListaPalavra* ptaux = l;

    novo = malloc(sizeof(ListaPalavra));
    novo->previsoes = NULL;
    novo->info = dados;

    while(ptaux != NULL)
    {
        ptaux->previsoes = NULL;
        ant = ptaux;
        ptaux = ptaux->proximo;
    }

    if(ant == NULL)
    {
        novo->proximo = l;
        l = novo;
        l->tamanho = 0;
    }
    else
    {
        novo->proximo = ptaux;
        ant->proximo = novo;
    }
    return l;
}

//função de inserção de palavras numa lista.
//recebe a lista e os dados e insere
//levemente modificada pois ela insere na lista de previsoes, nao na lista de proximos
//muito semelhante com a inserePalavras().
ListaPrevisoes* inserePrevisao(ListaPrevisoes *l, Palavra dados)
{
    ListaPrevisoes* novo;
    ListaPrevisoes* ant = NULL;
    ListaPrevisoes* ptaux = l;

    novo = malloc(sizeof(ListaPrevisoes));
    novo->info = dados;

    while(ptaux != NULL)
    {
        ant = ptaux;
        ptaux = ptaux->previsoes;
    }

    if(ant == NULL)
    {
        novo->previsoes = l;
        l = novo;
    }
    else
    {
        novo->previsoes = ptaux;
        ant->previsoes = novo;
    }
    return l;
}

//esta função recebe por referencia a lista de palavras de entrada a ser preenchida
//e o arquivo de consulta que será usado para preencher a lista
ListaPalavra *preencheListaPalavras(ListaPalavra *listaEntrada, FILE *consulta)
{
    //estrutura auxin auxilia na leitura do arquivo
    Palavra auxIn;
    //inicializa as variaveis da estrutura zeradas
    auxIn.impressoes = 0;
    auxIn.peso = 0;
    //percorre o arquivo de consulta
    while(!feof(consulta))
    {
        //le a primeira linha
        fscanf(consulta, "%s", auxIn.palavra);
        //insere a palavra
        listaEntrada = inserePalavra(listaEntrada, auxIn);
        //aumenta variavel de controle de tamanho
        listaEntrada->tamanho++;
        //inicializa a lista de previsoes como nula
        listaEntrada->previsoes = NULL;
    }
    return listaEntrada;
}

void preencheListaPrevisoes(FILE *wiktionary, int maximo, ListaPalavra *listaEntrada)
{
    //estrutura palavra auxiliar para ler do arquivo
    Palavra auxWiki;
    //variável auxiliar para converter de string p/ inteiro
    char linha1[20], *ptr;
    //variáveis para manter as estatisticas do programa
    int impressoes = 0;
    int iteracoes = -1;
    int testes = 0;
    //estrutura lista simplesmente encadeada auxiliar para percorrer as palavras de entrada
    ListaPalavra *auxiliarLista = listaEntrada;
    //total maximo calcula qual o máximo de impressões possíveis levando em consideração a entrada de ma´ximo do usuário e
    //o número de palavras recebidas para consulta
    int totalMaximo = maximo * auxiliarLista->tamanho;
    //pula a primeira linha que apenas registra o numero total de palavras
    fscanf(wiktionary, "%*[^\n]\n");
    //pervorre o arquivo de consulta enquanto ele não acaba ou
    //enquanto o numero total de impressões não ultrapassou o limite maximo
    while(!feof(wiktionary) && impressoes != totalMaximo)
    {
        //le a palavra do wik
        fscanf(wiktionary, "%s %s", linha1, auxWiki.palavra);
        //converte a string para inteiro e salva na variavel auxiliar auxwiki
        auxWiki.peso = strtod(linha1, &ptr);
        //pervorre a lista de palavras de entrada
        while(auxiliarLista != NULL)
        {
            testes++;
            //verifica se a palavra atual dá match com a palavra wiktionary atual
            //verifica também se a palavra atual já ultrapassou o limite de impressoes
            if(strncmp(auxWiki.palavra, auxiliarLista->info.palavra, strlen(auxiliarLista->info.palavra)) == 0 && auxiliarLista->info.impressoes < maximo)
            {
                //aumenta a variavel de controle de impressoes
                auxiliarLista->info.impressoes++;
                //insere esta palavra na lista de previsões da palavra atual
                auxiliarLista->previsoes = inserePrevisao(auxiliarLista->previsoes, auxWiki);
                //aumenta a variavel de impressoes total
                impressoes++;
            }
            //vai para a proxima palavra da lista de consulta
            auxiliarLista = auxiliarLista->proximo;
        }

        //aumenta a variavel de controle de interações totais
        iteracoes++;
        //volta a lista de palavras de entrada para o inicio
        auxiliarLista = listaEntrada;
    }

    printf("Relatorio de Processamento\nLeituras: %d\nTestes (if): %d\nMaximo de impressoes possivel: %d\nImpressoes: %d", iteracoes, testes, totalMaximo, impressoes);
}

//imprime no arquivo de saida a lista preenchida com as previsoes
void imprimeSaida(ListaPalavra* ptLista, FILE* saida)
{
    //ptaux é auxiliar para percorrer a lista de palavras
    ListaPalavra* ptaux;
    //prevaux é auxiliar para percorrer a lista de previsoes
    ListaPrevisoes* prevaux;
    //percorre a lista de palavras de maneira organizada para imprimir o resultado
    for (ptaux=ptLista; ptaux!=NULL; ptaux=ptaux->proximo)
    {
        //imprime no arquivo a palavra de entrada atual
        fprintf(saida, "%s\n", ptaux->info.palavra);
        //se o numero de impressoes for zero, continua e imprime que nao ha resultados
        if(ptaux->info.impressoes == 0)
        {
            fprintf(saida, "\tnenhum resultado encontrado\n");
            continue;
        }
        //percorre a lista de previsoes, imprimindo elas no arquivo uma por uma
        for (prevaux=ptaux->previsoes; prevaux!=NULL; prevaux=prevaux->previsoes)
        {
            fprintf(saida, "%15.0lf %s\n", prevaux->info.peso, prevaux->info.palavra);
        }
    }
}
