#include <stdio.h>
#include <windows.h>
#include <string.h>

typedef struct cadastro
{
    int idCodigo;
    char titulo[50];
    char autor[50];
    int ano;
    int quantTotal;
    int quantDispo;
}cadastro;

int cadastrarCodigo(struct cadastro)
{
    int idCodigo;
    do
    {
        printf("\n === CADASTRO DE ID/CÓDIGO === \n");
        printf("'ID/Código' do produto:  ");
        scanf("%d", idCodigo);
        if("")
    } while (idCodigo <= 0);
    return idCodigo;   
}

void cadastrarTitulo(struct cadastro)
{
    do
    {
    printf("\n === CADASTRO DE TITULO === \n");
    printf("Digite o Titulo do livro: ");
    getchar();
    fgets(cadastro[i].titulo, sizeof cadastro[i].titulo, stdin);
    cadastro[i].titulo[strcspn(cadastro[i].titulo, "\n")] = '\0';

    if (strlen(cadastro[i].titulo) == 0)
    {
        printf("Titulo não pode ser vazio!\n");
    }

    }while (strlen(cadastro[i].titulo) == 0)
}

void autor(struct cadastro)
{
    do
    {
        getchar();
        printf("Digite o nome do Autor: ");
        fgets(cadastro[i].autor, sizeof cadastro[i].autor, stdin);

        cadastro[i].autor[strcspn(cadastro[i].autor, "\n")] = '\0';

        if (strlen(cadastro[i].autor) == 0)
        {
            printf("Nome do autor não pode ser vazio!\n");
        }

    } while (strlen(cadastro[i].autor) == 0);
}

void ano(struct cadastro)
{
    int ano;

    printf("\n === ANO DE PUPLICAÇÃO === \n");
    printf("Digite o ano de puplicação: ");
    scanf("%d", &ano);
}

void quantidadeTotal(struct cadastro)
{
    int total = 0;

}
