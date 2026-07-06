// Cadastro de usuario - Código, nome, telefone e email.

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100

typedef struct
{
    int idCodigo;
    char nome[50];
    int telefone;
    char email[50];
} Usuario;

// ==========================================
// FUNÇÕES DO CÓDIGO 1 (INALTERADAS)
// ==========================================

// Gera um Id/Código aleatório de 6 dígitos 
int cadastrarCodigo(Usuario lista[], int total)
{
    int idCodigo;
    int valido;

    do
    {
        valido = 1;
        idCodigo = rand() % 900000 + 100000; // Id de 6 dígitos

        for (int i = 0; i < total; i++)
        {
            if (lista[i].idCodigo == idCodigo)
            {
                valido = 0; // já existe, sorteia outro
                break;
            }
        }
    } while (!valido);

    return idCodigo;
}

void cadastrarNome(Usuario *u)
{
    do
    {
        printf("\n === CADASTRO DE NOME === \n");
        printf("Digite o nome do usuario: ");
        fgets(u->nome, sizeof u->nome, stdin);
        u->nome[strcspn(u->nome, "\n")] = '\0';

        if (strlen(u->nome) == 0)
        {
            printf("Nome não pode ser vazio!\n");
        }
    } while (strlen(u->nome) == 0);
}

int cadastrarTelefone()
{
    int telefone;
    int valido;

    do
    {
        valido = 1;
        printf("\n === CADASTRO DE TELEFONE === \n");
        printf("Digite o telefone do usuario (somente números): ");

        if (scanf("%d", &telefone) != 1)
        {
            printf("Digite apenas números!\n");
            while (getchar() != '\n');
            valido = 0;
            continue;
        }

        if (telefone <= 0)
        {
            printf("Telefone inválido!\n");
            valido = 0;
        }
    } while (!valido);

    return telefone;
}

void cadastrarEmail(Usuario *u)
{
    do
    {
        printf("\n === CADASTRO DE EMAIL === \n");
        printf("Digite o email do usuario: ");
        fgets(u->email, sizeof u->email, stdin);
        u->email[strcspn(u->email, "\n")] = '\0';

        if (strlen(u->email) == 0)
        {
            printf("Email não pode ser vazio!\n");
        }
        else if (strchr(u->email, '@') == NULL)
        {
            printf("Email inválido! Deve conter '@'.\n");
            u->email[0] = '\0'; // força repetir o loop
        }
    } while (strlen(u->email) == 0);
}

void cadastrarUsuario(Usuario lista[], int *total)
{
    int i = *total;

    lista[i].idCodigo = cadastrarCodigo(lista, *total);
    lista[i].telefone = cadastrarTelefone();
    getchar(); // limpa o \n deixado pelo scanf antes dos fgets
    cadastrarNome(&lista[i]);
    cadastrarEmail(&lista[i]);

    (*total)++;
}

// ==========================================
// FUNÇÕES DO CÓDIGO 2 (ADAPTADAS PARA O CÓDIGO 1)
// ==========================================

void menu() {
    printf("\n==== MENU DE USUÁRIOS ====\n");
    printf("1 - Buscar por código\n");
    printf("2 - Buscar por nome\n");
    printf("3 - Alterar usuário\n");
    printf("4 - Excluir usuário\n");
    printf("5 - Listar usuários\n");
    printf("6 - Cadastrar novo usuário\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirUsuario(Usuario usuario) {
    printf("\n==== USUÁRIO ====\n");
    printf("Código: %d\n", usuario.idCodigo);
    printf("Nome: %s\n", usuario.nome);
    printf("Telefone: %d\n", usuario.telefone);
    printf("Email: %s\n", usuario.email);
}

void buscarPorCodigo(Usuario usuarios[], int total) {
    int codigo;
    int encontrado = 0;

    printf("\nDigite o código: ");
    scanf("%d", &codigo);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (usuarios[i].idCodigo == codigo) {
            exibirUsuario(usuarios[i]);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\nUsuário não encontrado.\n");
}

void buscarPorNome(Usuario usuarios[], int total) {
    char nome[50];
    int encontrado = 0;

    printf("\nDigite o nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strstr(usuarios[i].nome, nome) != NULL) {
            exibirUsuario(usuarios[i]);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("\nUsuário não encontrado.\n");
}

void alterarUsuario(Usuario usuarios[], int total) {
    int codigo;
    int encontrado = 0;

    printf("\nDigite o código do usuário que deseja alterar: ");
    scanf("%d", &codigo);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (usuarios[i].idCodigo == codigo) {

            printf("\n=== ALTERAÇÃO DE DADOS ===\n");

            printf("Novo nome: ");
            fgets(usuarios[i].nome, sizeof(usuarios[i].nome), stdin);
            usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = '\0';

            printf("Novo telefone (somente números): ");
            scanf("%d", &usuarios[i].telefone);
            limparBuffer();

            printf("Novo email: ");
            fgets(usuarios[i].email, sizeof(usuarios[i].email), stdin);
            usuarios[i].email[strcspn(usuarios[i].email, "\n")] = '\0';

            printf("\nUsuário alterado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\nUsuário não encontrado.\n");
}

void excluirUsuario(Usuario usuarios[], int *total) {
    int codigo;
    int posicao = -1;

    printf("\nDigite o código do usuário que deseja excluir: ");
    scanf("%d", &codigo);
    limparBuffer();

    for (int i = 0; i < *total; i++) {
        if (usuarios[i].idCodigo == codigo) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("\nUsuário não encontrado.\n");
        return;
    }

    for (int i = posicao; i < *total - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }

    (*total)--;

    printf("\nUsuário excluído com sucesso!\n");
}

void listarUsuarios(Usuario usuarios[], int total) {
    if (total == 0) {
        printf("\nNenhum usuário cadastrado.\n");
        return;
    }

    printf("\n==== LISTA DE USUÁRIOS ====\n");
    for (int i = 0; i < total; i++) {
        exibirUsuario(usuarios[i]);
    }
}


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    srand((unsigned int)time(NULL)); // Inicializa a semente para geração do código aleatório

    Usuario lista[MAX];
    int total = 0;
    int opcao;

    // Realiza o primeiro cadastro obrigatório idêntico ao fluxo do Código 1
    printf("===== CADASTRO INICIAL =====\n");
    cadastrarUsuario(lista, &total);

    // Exibe o primeiro usuário cadastrado para manter o comportamento visual do Código 1
    printf("\n=== Usuario cadastrado ===\n");
    printf("Codigo: %d\n", lista[0].idCodigo);
    printf("Nome: %s\n", lista[0].nome);
    printf("Telefone: %d\n", lista[0].telefone);
    printf("Email: %s\n", lista[0].email);

    // Entra no sistema de Menu interativo trazido do Código 2
    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = -1; // Força cair no default caso digitem letras
        } else {
            limparBuffer();
        }

        switch (opcao) {
            case 1:
                buscarPorCodigo(lista, total);
                break;

            case 2:
                buscarPorNome(lista, total);
                break;

            case 3:
                alterarUsuario(lista, total);
                break;

            case 4:
                excluirUsuario(lista, &total);
                break;

            case 5:
                listarUsuarios(lista, total);
                break;

            case 6:
                if (total >= MAX) {
                    printf("\nLimite máximo de %d usuários atingido!\n", MAX);
                } else {
                    cadastrarUsuario(lista, &total);
                }
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