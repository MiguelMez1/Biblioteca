#include <stdio.h>
#include <string.h>
#include <windows.h>

#define QTD_USUARIOS 3
#define TAM_TEXTO 100

typedef struct {
    int codigo;
    char nome[TAM_TEXTO];
    char telefone[TAM_TEXTO];
    char email[TAM_TEXTO];
} Usuario;

void cadastrarUsuarios(Usuario usuarios[]);
void menu();
void limparBuffer();
void buscarPorCodigo(Usuario usuarios[], int total);
void buscarPorNome(Usuario usuarios[], int total);
void exibirUsuario(Usuario usuario);
void alterarUsuario(Usuario usuarios[], int total);
void excluirUsuario(Usuario usuarios[], int *total);
void listarUsuarios(Usuario usuarios[], int total);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Usuario usuarios[QTD_USUARIOS];
    int opcao;
    int totalUsuarios = QTD_USUARIOS;

    printf("===== CADASTRO DE USUÁRIOS =====\n");
    cadastrarUsuarios(usuarios);

    do {
        menu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                buscarPorCodigo(usuarios, totalUsuarios);
                break;

            case 2:
                buscarPorNome(usuarios, totalUsuarios);
                break;

            case 3:
                alterarUsuario(usuarios, totalUsuarios);
                break;

            case 4:
                excluirUsuario(usuarios, &totalUsuarios);
                break;

            case 5:
                listarUsuarios(usuarios, totalUsuarios);
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
    printf("\n==== MENU DE USUÁRIOS ====\n");
    printf("1 - Buscar por código\n");
    printf("2 - Buscar por nome\n");
    printf("3 - Alterar usuário\n");
    printf("4 - Excluir usuário\n");
    printf("5 - Listar usuários\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarUsuarios(Usuario usuarios[]) {
    for (int i = 0; i < QTD_USUARIOS; i++) {

        printf("\n--- Usuário %d ---\n", i + 1);

        printf("Código: ");
        scanf("%d", &usuarios[i].codigo);
        limparBuffer();

        printf("Nome: ");
        fgets(usuarios[i].nome, TAM_TEXTO, stdin);
        usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = '\0';

        printf("Telefone: ");
        fgets(usuarios[i].telefone, TAM_TEXTO, stdin);
        usuarios[i].telefone[strcspn(usuarios[i].telefone, "\n")] = '\0';

        printf("Email: ");
        fgets(usuarios[i].email, TAM_TEXTO, stdin);
        usuarios[i].email[strcspn(usuarios[i].email, "\n")] = '\0';
    }
}

void exibirUsuario(Usuario usuario) {
    printf("\n==== USUÁRIO ====\n");
    printf("Código: %d\n", usuario.codigo);
    printf("Nome: %s\n", usuario.nome);
    printf("Telefone: %s\n", usuario.telefone);
    printf("Email: %s\n", usuario.email);
}

void buscarPorCodigo(Usuario usuarios[], int total) {
    int codigo;
    int encontrado = 0;

    printf("\nDigite o código: ");
    scanf("%d", &codigo);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (usuarios[i].codigo == codigo) {
            exibirUsuario(usuarios[i]);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\nUsuário não encontrado.\n");
}

void buscarPorNome(Usuario usuarios[], int total) {
    char nome[TAM_TEXTO];
    int encontrado = 0;

    printf("\nDigite o nome: ");
    fgets(nome, TAM_TEXTO, stdin);
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

        if (usuarios[i].codigo == codigo) {

            printf("\n=== ALTERAÇÃO DE DADOS ===\n");

            printf("Novo nome: ");
            fgets(usuarios[i].nome, TAM_TEXTO, stdin);
            usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = '\0';

            printf("Novo telefone: ");
            fgets(usuarios[i].telefone, TAM_TEXTO, stdin);
            usuarios[i].telefone[strcspn(usuarios[i].telefone, "\n")] = '\0';

            printf("Novo email: ");
            fgets(usuarios[i].email, TAM_TEXTO, stdin);
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
        if (usuarios[i].codigo == codigo) {
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