#include <stdio.h>
#include <windows.h>
#include <string.h>

#define QTD_LIVROS 3
#define TAM_NOME 50

typedef struct {
    int id;
    char livro[TAM_NOME];
    int codigo;
} Livro;

// Protótipos
void cadastrarLivros(Livro livros[]);
void menuProduto();
void buscarCodigo(Livro livros[], int total);

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    Livro livros[QTD_LIVROS];
    int opcao;
    int total = QTD_LIVROS;

    printf("=== CADASTRO DE LIVROS ===\n");
    cadastrarLivros(livros);

    do
    {
        menuProduto();
        scanf("%d", &opcao);

        while(getchar() != '\n');

        switch(opcao)
        {
            case 1:
                buscarCodigo(livros, total);
                break;

            case 2:
                
                break;

            case 3:
                
                break;

            case 4:
                
                break;

            case 5:
                
                break;

            case 0:
                printf("\nPrograma encerrado.\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    }while(opcao != 0);

    return 0;
}

void menuProduto()
{
    printf("\n===== MENU =====\n");
    printf("1 - Buscar por código\n");
    printf("2 - Buscar por título\n");
    printf("3 - Buscar por autor\n");
    printf("4 - Buscar por categoria\n");
    printf("5 - Buscar por ano\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

void cadastrarLivros(Livro livros[])
{
    for(int i = 0; i < QTD_LIVROS; i++)
    {
        printf("\n--- Livro %d ---\n", i + 1);

        livros[i].id = i + 1;

        printf("Título: ");
        fgets(livros[i].livro, TAM_NOME, stdin);
        livros[i].livro[strcspn(livros[i].livro, "\n")] = '\0';

        printf("Código: ");
        scanf("%d", &livros[i].codigo);

        while(getchar() != '\n');
    }
}

void buscarCodigo(Livro livros[], int total)
{
    int codBusca;
    int encontrado = 0;

    printf("\nDigite o código do livro: ");
    scanf("%d", &codBusca);

    while(getchar() != '\n');

    for(int i = 0; i < total; i++)
    {
        if(livros[i].codigo == codBusca)
        {
            printf("\n===== LIVRO ENCONTRADO =====\n");
            printf("ID: %d\n", livros[i].id);
            printf("Título: %s\n", livros[i].livro);
            printf("Código: %d\n", livros[i].codigo);

            encontrado = 1;
            break;
        }
    }

    if(!encontrado)
    {
        printf("\nLivro não encontrado!\n");
    }
}