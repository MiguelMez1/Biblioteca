
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define QTD_LIVROS 3
#define TAM_TEXTO 100

typedef struct {
    int codigo;
    char titulo[TAM_TEXTO];
    char autor[TAM_TEXTO];
    char categoria[TAM_TEXTO];
    int ano;
} Livro;

void cadastrarLivros(Livro livros[]);
void menuDeAlterecoes();
void menuDeBusca();
void limparBuffer();
void buscarPorCodigo(Livro livros[], int total);
void buscarPorTitulo(Livro livros[], int total);
void buscarPorAutor(Livro livros[], int total);
void buscarPorCategoria(Livro livros[], int total);
void buscarPorAno(Livro livros[], int total);
void exibirLivro(Livro livro);
void alterarLivro(Livro livros[], int total);
void excluirLivro(Livro livros[], int *total);
void listarLivros(Livro livros[], int total);
void buscar(Livro livros[], int total);


int main() {
    SetConsoleOutputCP(CP_UTF8);
    int opcao;
    int totalLivros = QTD_LIVROS;

    Livro livros[QTD_LIVROS];



    printf("===== CADASTRO DE LIVROS =====\n");
    cadastrarLivros(livros);

    do{
        menuDeAlterecoes();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao){
        case 1:
            buscar(livros, totalLivros);
            break;

        case 2:
            alterarLivro(livros, totalLivros);
            break;

        case 3:
            excluirLivro(livros, &totalLivros);
            break;  
                
        case 4:
            listarLivros(livros, totalLivros);
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

void buscar(Livro livros[], int total){
    int opcao;
    /*int totalLivros = QTD_LIVROS;*/

   do {
        menuDeBusca();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                buscarPorCodigo(livros, total);
                break;

            case 2:
                buscarPorTitulo(livros, total);
                break;

            case 3:
                buscarPorAutor(livros, total);
                break;

            case 4:
                buscarPorCategoria(livros, total);
                break;

            case 5:
                buscarPorAno(livros, total);
                break;

            case 0:
                printf("\nPrograma encerrado.\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

}

void menuDeAlterecoes() {
    printf("\n==== MENU DE OPERAÇÕES ====\n");
    printf("1 - buscar livro\n");
    printf("2 - alterar livro\n");
    printf("3 - excluir Livro\n");
    printf("4 - listar Livros\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

void menuDeBusca() {
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

void alterarLivro(Livro livros[], int total) 
{
    int codigo;
    int encontrado = 0;

    printf("\nDigite o código do livro que deseja alterar: ");
    scanf("%d", &codigo);
    limparBuffer();

    for(int i = 0; i < total; i++)
    {
        if(livros[i].codigo == codigo)
        {
            printf("\n=== ALTERAÇÃO DE DADOS ===\n");

            printf("Novo título: ");
            fgets(livros[i].titulo, TAM_TEXTO, stdin);
            livros[i].titulo[strcspn(livros[i].titulo, "\n")] = '\0';

            printf("Novo autor: ");
            fgets(livros[i].autor, TAM_TEXTO, stdin);
            livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';

            printf("Nova categoria: ");
            fgets(livros[i].categoria, TAM_TEXTO, stdin);
            livros[i].categoria[strcspn(livros[i].categoria, "\n")] = '\0';

            printf("Novo ano: ");
            scanf("%d", &livros[i].ano);
            limparBuffer();

            printf("\nLivro alterado com sucesso!\n");

            encontrado = 1;
            break;
        }
    }

    if(!encontrado)
        printf("\nLivro não encontrado.\n");
}

void excluirLivro(Livro livros[], int *total)
{
    int codigo;
    int posicao = -1;

    printf("\nDigite o código do livro que deseja excluir: ");
    scanf("%d", &codigo);
    limparBuffer();

    for(int i = 0; i < *total; i++)
    {
        if(livros[i].codigo == codigo)
        {
            posicao = i;
            break;
        }
    }

    if(posicao == -1)
    {
        printf("\nLivro não encontrado.\n");
        return;
    }

    for(int i = posicao; i < *total - 1; i++)
    {
        livros[i] = livros[i + 1];
    }

    (*total)--;

    printf("\nLivro excluído com sucesso!\n");
}

void listarLivros(Livro livros[], int total)
{
    if(total == 0)
    {
        printf("\nNenhum livro cadastrado.\n");
        return;
    }

    printf("\n==== LISTA DE LIVROS ====\n");

    for(int i = 0; i < total; i++)
    {
        printf("\nLivro %d\n", i + 1);
        printf("Código: %d\n", livros[i].codigo);
        printf("Título: %s\n", livros[i].titulo);
        printf("Autor: %s\n", livros[i].autor);
        printf("Categoria: %s\n", livros[i].categoria);
        printf("Ano: %d\n", livros[i].ano);
    }
}