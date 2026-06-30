
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define QTD_LIVROS 2
#define TAM_TEXTO 100

typedef struct {
    int codigo;
    char titulo[TAM_TEXTO];
    char autor[TAM_TEXTO];
    char categoria[TAM_TEXTO];
    int ano;
} Livro;

void cadastrarLivros(Livro livros[]);
void menu();
void limparBuffer();
void buscarPorCodigo(Livro livros[], int total);
void buscarPorTitulo(Livro livros[], int total);
void buscarPorAutor(Livro livros[], int total);
void buscarPorCategoria(Livro livros[], int total);
void buscarPorAno(Livro livros[], int total);
void exibirLivro(Livro livro);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Livro livros[QTD_LIVROS];
    int opcao;

    printf("===== CADASTRO DE LIVROS =====\n");
    cadastrarLivros(livros);

    do {
        menu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                buscarPorCodigo(livros, QTD_LIVROS);
                break;

            case 2:
                buscarPorTitulo(livros, QTD_LIVROS);
                break;

            case 3:
                buscarPorAutor(livros, QTD_LIVROS);
                break;

            case 4:
                buscarPorCategoria(livros, QTD_LIVROS);
                break;

            case 5:
                buscarPorAno(livros, QTD_LIVROS);
                break;

            case 0:
                printf("\nPrograma encerrado.\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

void menu() {
    printf("\n==== MENU DE BUSCA ====\n");
    printf("1 - Código\n");
    printf("2 - Título\n");
    printf("3 - Autor\n");
    printf("4 - Categoria\n");
    printf("5 - Ano\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarLivros(Livro livros[]) {
    for (int i = 0; i < QTD_LIVROS; i++) {

        printf("\n--- Livro %d ---\n", i + 1);

        printf("Código: ");
        scanf("%d", &livros[i].codigo);
        limparBuffer();

        printf("Título: ");
        fgets(livros[i].titulo, TAM_TEXTO, stdin);
        livros[i].titulo[strcspn(livros[i].titulo, "\n")] = '\0';

        printf("Autor: ");
        fgets(livros[i].autor, TAM_TEXTO, stdin);
        livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';

        printf("Categoria: ");
        fgets(livros[i].categoria, TAM_TEXTO, stdin);
        livros[i].categoria[strcspn(livros[i].categoria, "\n")] = '\0';

        printf("Ano: ");
        scanf("%d", &livros[i].ano);
        limparBuffer();
    }
}

void exibirLivro(Livro livro) {
    printf("\n==== LIVRO ENCONTRADO ====\n");
    printf("Código: %d\n", livro.codigo);
    printf("Título: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Categoria: %s\n", livro.categoria);
    printf("Ano: %d\n", livro.ano);
}

void buscarPorCodigo(Livro livros[], int total) {
    int codigo;
    int encontrado = 0;

    printf("\nDigite o código: ");
    scanf("%d", &codigo);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (livros[i].codigo == codigo) {
            exibirLivro(livros[i]);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\nLivro não encontrado!\n");
}

void buscarPorTitulo(Livro livros[], int total) {
    char titulo[TAM_TEXTO];
    int encontrado = 0;

    printf("\nDigite o título: ");
    fgets(titulo, TAM_TEXTO, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strstr(livros[i].titulo, titulo) != NULL) {
            exibirLivro(livros[i]);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("\nNenhum livro encontrado.\n");
}

void buscarPorAutor(Livro livros[], int total) {
    char autor[TAM_TEXTO];
    int encontrado = 0;

    printf("\nDigite o autor: ");
    fgets(autor, TAM_TEXTO, stdin);
    autor[strcspn(autor, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strstr(livros[i].autor, autor) != NULL) {
            exibirLivro(livros[i]);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("\nNenhum livro encontrado.\n");
}

void buscarPorCategoria(Livro livros[], int total) {
    char categoria[TAM_TEXTO];
    int encontrado = 0;

    printf("\nDigite a categoria: ");
    fgets(categoria, TAM_TEXTO, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strstr(livros[i].categoria, categoria) != NULL) {
            exibirLivro(livros[i]);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("\nNenhum livro encontrado.\n");
}

void buscarPorAno(Livro livros[], int total) {
    int ano;
    int encontrado = 0;

    printf("\nDigite o ano: ");
    scanf("%d", &ano);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (livros[i].ano == ano) {
            exibirLivro(livros[i]);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("\nNenhum livro encontrado.\n");
}