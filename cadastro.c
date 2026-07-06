#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "cadastro.h"
#define MAX 100

/*
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
*/
int cadastrarCodigo(cadastro lista[], int total)
{
    int idCodigo;
    int valido;

    do
    {
        valido = 1; 

        printf("\n === CADASTRO DE ID/CÓDIGO === \n");
        printf("'ID/Código' do produto: ");

        if (scanf("%d", &idCodigo) != 1)
        {
            printf("Digite apenas números!\n");
            while (getchar() != '\n'); 
            valido = 0;
            continue; 
        }

        if (idCodigo <= 0)
        {
            printf("O código precisa ser maior que zero!\n");
            valido = 0;
        }

        for (int i = 0; i < total; i++)
        {
            if (lista[i].idCodigo == idCodigo)
            {
                printf("Esse código já foi cadastrado!\n");
                valido = 0;
                break; 
            }
        }

    } while (!valido);

    return idCodigo;
}

void cadastrarTitulo(cadastro *c)
{
    do
    {
    printf("\n === CADASTRO DE TITULO === \n");
    printf("Digite o Titulo do livro: ");
    getchar();
    fgets(c->titulo, sizeof c->titulo, stdin);
    c->titulo[strcspn(c->titulo, "\n")] = '\0';

    if (strlen(c->titulo) == 0)
    {
        printf("Titulo não pode ser vazio!\n");
    }

    }while (strlen(c->titulo) == 0);

}

void cadastrarAutor(cadastro *c)
{
    do
    {
        printf("\n === CADASTRO DE AUTOR! === \n");
        printf("Digite o nome do Autor: ");
        fgets(c->autor, sizeof c->autor, stdin);

        c->autor[strcspn(c->autor, "\n")] = '\0';

        if (strlen(c->autor) == 0)
        {
            printf("Nome do autor não pode ser vazio!\n");
        }

    } while (strlen(c->autor) == 0);

}

int cadastrarAno()
{
    int ano;

    printf("\n === ANO DE PUPLICAÇÃO === \n");
    printf("Digite o ano de puplicação: ");
    scanf("%d", &ano);

    return ano;
}

int quantidadeAcadastrar()
{
    int unidades; 

    printf("\n === Quantas unidades à cadastrar? === \n");
    printf("Digite aqui: ");
    scanf("%d", &unidades );

    return unidades;
}

int quantidadeDisponivel()
{
    int disponivel;

    printf("\n === Quantos livros estão disponiveis? === \n");
    printf("Digite aqui: ");
    scanf("%d", &disponivel);

    return disponivel;
}

void cadastrarCategoria( cadastro *c)
{
    do
    {
        printf("\n === CADASTRO DE CATEGORIA === \n");
        printf("Digite aqui: ");
        fgets(c->categoria, sizeof c->categoria, stdin);

        c->categoria[strcspn(c->categoria, "\n")] = '\0';

        if (strlen(c->categoria) == 0)
        {
            printf("Categoria não pode estar vazio!\n");
        }

    } while (strlen(c->categoria) == 0);

    
}

void cadastrarLivro(cadastro lista[], int *total)
{
    int i = *total;

   lista[i].idCodigo = cadastrarCodigo(lista, *total);
   getchar();

   cadastrarCategoria(&lista[i]);
   cadastrarTitulo(&lista[i]);
   cadastrarAutor(&lista[i]);

   lista[i].ano = cadastrarAno();
   lista[i].quantTotal = quantidadeAcadastrar();
   lista[i].quantDispo = quantidadeDisponivel();

   (*total)++;
    
}





