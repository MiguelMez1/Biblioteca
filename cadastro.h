#ifndef CADASTRO_H
#define CADASTRO_H

typedef struct 
{
    int idCodigo;
    char categoria[50];
    char titulo[50];
    char autor[50];
    int ano;
    int quantTotal;
    int quantDispo;
} cadastro;

void cadastrarLivro(cadastro lista[], int *total);

#endif