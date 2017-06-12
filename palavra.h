struct dadosPalavra{
    double codigo;
    char nome[50];
}; typedef struct dadosPalavra dadosPalavra;

struct Palavra{
    dadosPalavra info;
    struct Palavra *proximo;
}; typedef struct Palavra Palavra;

Palavra* inserePalavra(Palavra* l, dadosPalavra dados);
Palavra* inicializa(void);
