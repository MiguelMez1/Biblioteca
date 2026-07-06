#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MAX 100
#define TAM_TEXTO 100
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

void menuPrincipal();
void menuDeBusca();
void limparBuffer();
void buscarPorCodigo(cadastro lista[], int total);
void buscarPorTitulo(cadastro lista[], int total);
void buscarPorAutor(cadastro lista[], int total);
void buscarPorCategoria(cadastro lista[], int total);
void buscarPorAno(cadastro lista[], int total);
void exibirLivro(cadastro livro);
void alterarLivro(cadastro lista[], int total);
void excluirLivro(cadastro lista[], int *total);
void listarLivros(cadastro lista[], int total);
void buscar(cadastro lista[], int total);


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

    } while (strlen(c->titulo) == 0);
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

    printf("\n === ANO DE PUBLICAÇÃO === \n");
    printf("Digite o ano de publicação: ");
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

void cadastrarCategoria(cadastro *c)
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
    if (*total >= MAX) {
        printf("\nLimite máximo de cadastros atingido!\n");
        return;
    }

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


int gestaoLivros() {
    SetConsoleOutputCP(CP_UTF8);
    cadastro lista[MAX];
    int totalLivros = 0;
    int opcao;

    do {
        menuPrincipal();
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("\nOpção inválida! Digite um número.\n");
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarLivro(lista, &totalLivros);
                break;

            case 2:
                buscar(lista, totalLivros);
                break;

            case 3:
                alterarLivro(lista, totalLivros);
                break;

            case 4:
                excluirLivro(lista, &totalLivros);
                break;  
                
            case 5:
                listarLivros(lista, totalLivros);
                break;
            
            case 0:
                printf("\nPrograma encerrado.\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }
    } while(opcao != 0);
 
    return 0;
}

// funções de operações: busca,
void menuPrincipal() {
    printf("\n==== MENU DE OPERAÇÕES ====\n");
    printf("1 - Cadastrar Livro\n");
    printf("2 - Buscar Livro\n");
    printf("3 - Alterar Livro\n");
    printf("4 - Excluir Livro\n");
    printf("5 - Listar Livros\n");
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
    printf("0 - Voltar ao Menu Principal\n");
    printf("Escolha uma opção: ");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void buscar(cadastro lista[], int total) {
    int opcao;

    do {
        menuDeBusca();
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("\nOpção inválida!\n");
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                buscarPorCodigo(lista, total);
                break;
            case 2:
                buscarPorTitulo(lista, total);
                break;
            case 3:
                buscarPorAutor(lista, total);
                break;
            case 4:
                buscarPorCategoria(lista, total);
                break;
            case 5:
                buscarPorAno(lista, total);
                break;
            case 0:
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}

void exibirLivro(cadastro livro) {
    printf("\n==== LIVRO ENCONTRADO ====\n");
    printf("Código: %d\n", livro.idCodigo);
    printf("Título: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Categoria: %s\n", livro.categoria);
    printf("Ano: %d\n", livro.ano);
    printf("Quantidade Total: %d\n", livro.quantTotal);
    printf("Quantidade Disponível: %d\n", livro.quantDispo);
}

void buscarPorCodigo(cadastro lista[], int total) {
    int codigo;
    int encontrado = 0;

    printf("\nDigite o código: ");
    scanf("%d", &codigo);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (lista[i].idCodigo == codigo) {
            exibirLivro(lista[i]);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\nLivro não encontrado!\n");
}

void buscarPorTitulo(cadastro lista[], int total) {
    char titulo[TAM_TEXTO];
    int encontrado = 0;

    printf("\nDigite o título: ");
    fgets(titulo, TAM_TEXTO, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strstr(lista[i].titulo, titulo) != NULL) {
            exibirLivro(lista[i]);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("\nNenhum livro encontrado.\n");
}

void buscarPorAutor(cadastro lista[], int total) {
    char autor[TAM_TEXTO];
    int encontrado = 0;

    printf("\nDigite o autor: ");
    fgets(autor, TAM_TEXTO, stdin);
    autor[strcspn(autor, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strstr(lista[i].autor, autor) != NULL) {
            exibirLivro(lista[i]);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("\nNenhum livro encontrado.\n");
}

void buscarPorCategoria(cadastro lista[], int total) {
    char categoria[TAM_TEXTO];
    int encontrado = 0;

    printf("\nDigite a categoria: ");
    fgets(categoria, TAM_TEXTO, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strstr(lista[i].categoria, categoria) != NULL) {
            exibirLivro(lista[i]);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("\nNenhum livro encontrado.\n");
}

void buscarPorAno(cadastro lista[], int total) {
    int ano;
    int encontrado = 0;

    printf("\nDigite o ano: ");
    scanf("%d", &ano);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (lista[i].ano == ano) {
            exibirLivro(lista[i]);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("\nNenhum livro encontrado.\n");
}

void alterarLivro(cadastro lista[], int total) {
    int codigo;
    int encontrado = 0;

    printf("\nDigite o código do livro que deseja alterar: ");
    scanf("%d", &codigo);
    limparBuffer();

    for(int i = 0; i < total; i++) {
        if(lista[i].idCodigo == codigo) {
            printf("\n=== ALTERAÇÃO DE DADOS ===\n");

            printf("Novo título: ");
            fgets(lista[i].titulo, sizeof(lista[i].titulo), stdin);
            lista[i].titulo[strcspn(lista[i].titulo, "\n")] = '\0';

            printf("Novo autor: ");
            fgets(lista[i].autor, sizeof(lista[i].autor), stdin);
            lista[i].autor[strcspn(lista[i].autor, "\n")] = '\0';

            printf("Nova categoria: ");
            fgets(lista[i].categoria, sizeof(lista[i].categoria), stdin);
            lista[i].categoria[strcspn(lista[i].categoria, "\n")] = '\0';

            printf("Novo ano: ");
            scanf("%d", &lista[i].ano);
            
            printf("Nova quantidade total: ");
            scanf("%d", &lista[i].quantTotal);
            
            printf("Nova quantidade disponível: ");
            scanf("%d", &lista[i].quantDispo);
            limparBuffer();

            printf("\nLivro alterado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if(!encontrado)
        printf("\nLivro não encontrado.\n");
}

void excluirLivro(cadastro lista[], int *total) {
    int codigo;
    int posicao = -1;

    printf("\nDigite o código do livro que deseja excluir: ");
    scanf("%d", &codigo);
    limparBuffer();

    for(int i = 0; i < *total; i++) {
        if(lista[i].idCodigo == codigo) {
            posicao = i;
            break;
        }
    }

    if(posicao == -1) {
        printf("\nLivro não encontrado.\n");
        return;
    }

    for(int i = posicao; i < *total - 1; i++) {
        lista[i] = lista[i + 1];
    }

    (*total)--;
    printf("\nLivro excluído com sucesso!\n");
}

void listarLivros(cadastro lista[], int total) {
    if(total == 0) {
        printf("\nNenhum livro cadastrado.\n");
        return;
    }

    printf("\n==== LISTA DE LIVROS ====\n");

    for(int i = 0; i < total; i++) {
        printf("\nLivro %d\n", i + 1);
        printf("Código: %d\n", lista[i].idCodigo);
        printf("Título: %s\n", lista[i].titulo);
        printf("Autor: %s\n", lista[i].autor);
        printf("Categoria: %s\n", lista[i].categoria);
        printf("Ano: %d\n", lista[i].ano);
        printf("Quantidade Total: %d\n", lista[i].quantTotal);
        printf("Quantidade Disponível: %d\n", lista[i].quantDispo);
    }
}