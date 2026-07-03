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

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    srand((unsigned int)time(NULL)); // inicializa a semente antes de qualquer 'sorteio'

    Usuario lista[MAX];
    int total = 0;

    cadastrarUsuario(lista, &total);

    printf("\n=== Usuario cadastrado ===\n");
    printf("Codigo: %d\n", lista[0].idCodigo);
    printf("Nome: %s\n", lista[0].nome);
    printf("Telefone: %d\n", lista[0].telefone);
    printf("Email: %s\n", lista[0].email);

    return 0;
}