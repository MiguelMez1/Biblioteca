#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// ==========================================
// LIMITES DO SISTEMA E DEFINIÇÕES
// ==========================================
#define MAX_LIVROS 100
#define MAX_USUARIOS 50
#define MAX_EMPRESTIMOS 200
#define TAM_TEXTO 100

// ==========================================
// ESTRUTURAS (STRUCTS)
// ==========================================
typedef struct {
    int idCodigo;
    char nome[50];
    int telefone;
    char email[50];
} Usuario;

typedef struct {
    int idCodigo;
    char categoria[50];
    char titulo[50];
    char autor[50];
    int ano;
    int quantTotal;
    int quantDispo;
    int vezesEmprestado; // Bônus: para o relatório de livro mais emprestado
} cadastro; // Estrutura de Livros

typedef struct {
    int idUsuario;
    int idLivro;
    int ativo; // 1 para emprestado, 0 para devolvido
} Emprestimo;

// ==========================================
// PROTÓTIPOS GERAIS
// ==========================================
void limparBuffer();

// ==========================================
// MÓDULO 1 - USUÁRIOS (ADAPTADO COM REGRAS)
// ==========================================
int cadastrarCodigoUsuario(Usuario lista[], int total) {
    int idCodigo, valido;
    do {
        valido = 1;
        idCodigo = rand() % 900000 + 100000;
        for (int i = 0; i < total; i++) {
            if (lista[i].idCodigo == idCodigo) {
                valido = 0; break;
            }
        }
    } while (!valido);
    return idCodigo;
}

void cadastrarUsuario(Usuario lista[], int *total) {
    if (*total >= MAX_USUARIOS) {
        printf("\nLimite máximo de %d usuários atingido!\n", MAX_USUARIOS);
        return;
    }
    int i = *total;
    lista[i].idCodigo = cadastrarCodigoUsuario(lista, *total);
    
    int valido;
    do {
        valido = 1;
        printf("\n === CADASTRO DE TELEFONE === \n");
        printf("Digite o telefone do usuario (somente números): ");
        if (scanf("%d", &lista[i].telefone) != 1 || lista[i].telefone <= 0) {
            printf("Telefone inválido! Digite apenas números.\n");
            limparBuffer();
            valido = 0;
        }
    } while (!valido);
    limparBuffer();

    do {
        printf("\n === CADASTRO DE NOME === \n");
        printf("Digite o nome do usuario: ");
        fgets(lista[i].nome, sizeof lista[i].nome, stdin);
        lista[i].nome[strcspn(lista[i].nome, "\n")] = '\0';
        if (strlen(lista[i].nome) == 0) printf("Nome não pode ser vazio!\n");
    } while (strlen(lista[i].nome) == 0);

    do {
        printf("\n === CADASTRO DE EMAIL === \n");
        printf("Digite o email do usuario: ");
        fgets(lista[i].email, sizeof lista[i].email, stdin);
        lista[i].email[strcspn(lista[i].email, "\n")] = '\0';
        if (strlen(lista[i].email) == 0) {
            printf("Email não pode ser vazio!\n");
        } else if (strchr(lista[i].email, '@') == NULL) {
            printf("Email inválido! Deve conter '@'.\n");
            lista[i].email[0] = '\0';
        }
    } while (strlen(lista[i].email) == 0);

    (*total)++;
    printf("\nUsuário cadastrado com sucesso! Código: %d\n", lista[i].idCodigo);
}

void exibirUsuario(Usuario usuario) {
    printf("\nCódigo: %d | Nome: %s | Tel: %d | Email: %s\n", 
           usuario.idCodigo, usuario.nome, usuario.telefone, usuario.email);
}

void excluirUsuario(Usuario usuarios[], int *totalUsuarios, Emprestimo emprestimos[], int totalEmprestimos) {
    int codigo, posicao = -1;
    printf("\nDigite o código do usuário que deseja excluir: ");
    scanf("%d", &codigo);
    limparBuffer();

    // REGRA DE NEGÓCIO: Não excluir usuário com empréstimos ativos
    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idUsuario == codigo && emprestimos[i].ativo == 1) {
            printf("\nERRO: Este usuário possui empréstimos ativos e não pode ser excluído!\n");
            return;
        }
    }

    for (int i = 0; i < *totalUsuarios; i++) {
        if (usuarios[i].idCodigo == codigo) {
            posicao = i; break;
        }
    }

    if (posicao == -1) {
        printf("\nUsuário não encontrado.\n"); return;
    }
    for (int i = posicao; i < *totalUsuarios - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }
    (*totalUsuarios)--;
    printf("\nUsuário excluído com sucesso!\n");
}

void listarUsuarios(Usuario usuarios[], int total) {
    if (total == 0) { printf("\nNenhum usuário cadastrado.\n"); return; }
    printf("\n==== LISTA DE USUÁRIOS ====\n");
    for (int i = 0; i < total; i++) exibirUsuario(usuarios[i]);
}

void gestaoUsuarios(Usuario usuarios[], int *totalUsuarios, Emprestimo emprestimos[], int totalEmprestimos) {
    int opcao;
    do {
        printf("\n==== GERENCIAR USUÁRIOS ====\n");
        printf("1 - Cadastrar novo usuário\n");
        printf("2 - Excluir usuário\n");
        printf("3 - Listar usuários\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }
        limparBuffer();

        switch (opcao) {
            case 1: cadastrarUsuario(usuarios, totalUsuarios); break;
            case 2: excluirUsuario(usuarios, totalUsuarios, emprestimos, totalEmprestimos); break;
            case 3: listarUsuarios(usuarios, *totalUsuarios); break;
            case 0: break;
            default: printf("\nOpção inválida!\n");
        }
    } while(opcao != 0);
}

// ==========================================
// MÓDULO 2 - LIVROS (ADAPTADO COM REGRAS)
// ==========================================
int cadastrarCodigoLivro(cadastro lista[], int total) {
    int idCodigo, valido;
    do {
        valido = 1;
        printf("\n'ID/Código' do livro: ");
        if (scanf("%d", &idCodigo) != 1 || idCodigo <= 0) {
            printf("Código inválido! Digite um número maior que zero.\n");
            limparBuffer(); valido = 0; continue;
        }
        for (int i = 0; i < total; i++) {
            if (lista[i].idCodigo == idCodigo) {
                printf("Esse código já foi cadastrado!\n");
                valido = 0; break;
            }
        }
    } while (!valido);
    return idCodigo;
}

void cadastrarLivro(cadastro lista[], int *total) {
    if (*total >= MAX_LIVROS) {
        printf("\nLimite máximo de livros atingido!\n"); return;
    }
    int i = *total;
    lista[i].idCodigo = cadastrarCodigoLivro(lista, *total);
    limparBuffer();

    do {
        printf("Título do livro: ");
        fgets(lista[i].titulo, sizeof lista[i].titulo, stdin);
        lista[i].titulo[strcspn(lista[i].titulo, "\n")] = '\0';
    } while (strlen(lista[i].titulo) == 0);

    do {
        printf("Autor: ");
        fgets(lista[i].autor, sizeof lista[i].autor, stdin);
        lista[i].autor[strcspn(lista[i].autor, "\n")] = '\0';
    } while (strlen(lista[i].autor) == 0);
    
    printf("Ano de publicação: ");
    scanf("%d", &lista[i].ano);

    do {
        printf("Quantidade total a cadastrar: ");
        scanf("%d", &lista[i].quantTotal);
        if(lista[i].quantTotal < 0) printf("A quantidade não pode ser negativa!\n");
    } while (lista[i].quantTotal < 0);

    lista[i].quantDispo = lista[i].quantTotal; // Disponível começa igual ao total
    lista[i].vezesEmprestado = 0; // Inicializa contador do relatório bônus

    (*total)++;
    printf("\nLivro cadastrado com sucesso!\n");
}

void exibirLivro(cadastro livro) {
    printf("\nCódigo: %d | Título: %s | Autor: %s | Ano: %d | Disp: %d/%d\n", 
           livro.idCodigo, livro.titulo, livro.autor, livro.ano, livro.quantDispo, livro.quantTotal);
}

void excluirLivro(cadastro lista[], int *totalLivros, Emprestimo emprestimos[], int totalEmprestimos) {
    int codigo, posicao = -1;
    printf("\nDigite o código do livro que deseja excluir: ");
    scanf("%d", &codigo);
    limparBuffer();

    // REGRA DE NEGÓCIO: Não excluir livro emprestado
    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idLivro == codigo && emprestimos[i].ativo == 1) {
            printf("\nERRO: Este livro possui exemplares emprestados e não pode ser excluído!\n");
            return;
        }
    }

    for (int i = 0; i < *totalLivros; i++) {
        if (lista[i].idCodigo == codigo) { posicao = i; break; }
    }

    if (posicao == -1) { printf("\nLivro não encontrado.\n"); return; }

    for (int i = posicao; i < *totalLivros - 1; i++) {
        lista[i] = lista[i + 1];
    }
    (*totalLivros)--;
    printf("\nLivro excluído com sucesso!\n");
}

void listarLivros(cadastro lista[], int total) {
    if (total == 0) { printf("\nNenhum livro cadastrado.\n"); return; }
    printf("\n==== LISTA DE LIVROS ====\n");
    for (int i = 0; i < total; i++) exibirLivro(lista[i]);
}

void gestaoLivros(cadastro livros[], int *totalLivros, Emprestimo emprestimos[], int totalEmprestimos) {
    int opcao;
    do {
        printf("\n==== GERENCIAR LIVROS ====\n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Excluir Livro\n");
        printf("3 - Listar Livros\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }
        limparBuffer();

        switch (opcao) {
            case 1: cadastrarLivro(livros, totalLivros); break;
            case 2: excluirLivro(livros, totalLivros, emprestimos, totalEmprestimos); break;
            case 3: listarLivros(livros, *totalLivros); break;
            case 0: break;
            default: printf("\nOpção inválida!\n");
        }
    } while(opcao != 0);
}

// ==========================================
// MÓDULO 3 - EMPRÉSTIMOS (NOVO)
// ==========================================
int buscarIndiceUsuario(Usuario usuarios[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (usuarios[i].idCodigo == codigo) return i;
    }
    return -1;
}

int buscarIndiceLivro(cadastro livros[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (livros[i].idCodigo == codigo) return i;
    }
    return -1;
}

void realizarEmprestimo(Usuario usuarios[], int totalUsuarios, cadastro livros[], int totalLivros, Emprestimo emprestimos[], int *totalEmprestimos) {
    if (*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("\nLimite máximo de empréstimos do sistema atingido!\n"); return;
    }

    int idUser, idLivro;
    printf("\nDigite o Código do Usuário: ");
    scanf("%d", &idUser);
    int idxUser = buscarIndiceUsuario(usuarios, totalUsuarios, idUser);
    if (idxUser == -1) { printf("\nUsuário não encontrado!\n"); return; }

    printf("Digite o Código do Livro: ");
    scanf("%d", &idLivro);
    int idxLivro = buscarIndiceLivro(livros, totalLivros, idLivro);
    if (idxLivro == -1) { printf("\nLivro não encontrado!\n"); return; }

    // REGRA: Há exemplares disponíveis?
    if (livros[idxLivro].quantDispo <= 0) {
        printf("\nNão há exemplares disponíveis deste livro no momento!\n"); return;
    }

    // REGRA: O mesmo usuário não pode pegar o mesmo livro duas vezes ao mesmo tempo
    for (int i = 0; i < *totalEmprestimos; i++) {
        if (emprestimos[i].idUsuario == idUser && emprestimos[i].idLivro == idLivro && emprestimos[i].ativo == 1) {
            printf("\nEste usuário já possui uma cópia deste livro emprestada!\n"); return;
        }
    }

    // Registra Empréstimo
    emprestimos[*totalEmprestimos].idUsuario = idUser;
    emprestimos[*totalEmprestimos].idLivro = idLivro;
    emprestimos[*totalEmprestimos].ativo = 1;
    (*totalEmprestimos)++;

    livros[idxLivro].quantDispo--;
    livros[idxLivro].vezesEmprestado++;

    printf("\nEmpréstimo realizado com sucesso!\n");
}

void devolverLivro(Usuario usuarios[], int totalUsuarios, cadastro livros[], int totalLivros, Emprestimo emprestimos[], int totalEmprestimos) {
    int idUser, idLivro;
    printf("\nDigite o Código do Usuário: ");
    scanf("%d", &idUser);
    printf("Digite o Código do Livro a devolver: ");
    scanf("%d", &idLivro);

    // Busca o empréstimo ativo
    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idUsuario == idUser && emprestimos[i].idLivro == idLivro && emprestimos[i].ativo == 1) {
            emprestimos[i].ativo = 0; // Desativa o empréstimo
            
            int idxLivro = buscarIndiceLivro(livros, totalLivros, idLivro);
            if (idxLivro != -1) livros[idxLivro].quantDispo++; // Devolve ao estoque

            printf("\nLivro devolvido com sucesso!\n");
            return;
        }
    }
    // REGRA: Só devolver livros realmente emprestados
    printf("\nNenhum empréstimo ativo encontrado para este usuário e livro!\n");
}

void gestaoEmprestimos(Usuario usuarios[], int totalUsuarios, cadastro livros[], int totalLivros, Emprestimo emprestimos[], int *totalEmprestimos) {
    int opcao;
    do {
        printf("\n==== EMPRÉSTIMOS ====\n");
        printf("1 - Registrar Empréstimo\n");
        printf("2 - Devolver Livro\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }
        limparBuffer();

        switch (opcao) {
            case 1: realizarEmprestimo(usuarios, totalUsuarios, livros, totalLivros, emprestimos, totalEmprestimos); break;
            case 2: devolverLivro(usuarios, totalUsuarios, livros, totalLivros, emprestimos, *totalEmprestimos); break;
            case 0: break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}

// ==========================================
// MÓDULO 4 - RELATÓRIOS (NOVO)
// ==========================================
void gestaoRelatorios(Usuario usuarios[], int totalUsuarios, cadastro livros[], int totalLivros, Emprestimo emprestimos[], int totalEmprestimos) {
    int opcao;
    do {
        printf("\n==== RELATÓRIOS ====\n");
        printf("1 - Todos os livros\n");
        printf("2 - Livros disponíveis\n");
        printf("3 - Livros emprestados\n");
        printf("4 - Usuários cadastrados\n");
        printf("5 - Usuários com empréstimos ativos\n");
        printf("6 - Quantidade total de livros no acervo\n");
        printf("7 - Livro mais emprestado (Bônus)\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }
        limparBuffer();

        switch (opcao) {
            case 1: // Todos os livros
                listarLivros(livros, totalLivros);
                break;
            case 2: // Livros disponíveis
                printf("\n--- Livros Disponíveis ---\n");
                for(int i=0; i<totalLivros; i++) {
                    if(livros[i].quantDispo > 0) exibirLivro(livros[i]);
                }
                break;
            case 3: // Livros emprestados
                printf("\n--- Livros Emprestados (Fora do estoque) ---\n");
                for(int i=0; i<totalLivros; i++) {
                    if(livros[i].quantDispo < livros[i].quantTotal) exibirLivro(livros[i]);
                }
                break;
            case 4: // Usuários cadastrados
                listarUsuarios(usuarios, totalUsuarios);
                break;
            case 5: // Usuários com empréstimos
                printf("\n--- Usuários com Empréstimos Ativos ---\n");
                for(int i=0; i<totalUsuarios; i++) {
                    int temEmprestimo = 0;
                    for(int j=0; j<totalEmprestimos; j++) {
                        if(emprestimos[j].idUsuario == usuarios[i].idCodigo && emprestimos[j].ativo == 1) {
                            temEmprestimo = 1; break;
                        }
                    }
                    if(temEmprestimo) exibirUsuario(usuarios[i]);
                }
                break;
            case 6: // Quantidade total
                {
                    int totalAcervo = 0;
                    for(int i=0; i<totalLivros; i++) totalAcervo += livros[i].quantTotal;
                    printf("\nQuantidade total de volumes no acervo: %d\n", totalAcervo);
                }
                break;
            case 7: // Bônus: Mais emprestado
                if (totalLivros == 0) { printf("\nNenhum livro cadastrado.\n"); break; }
                int maxIdx = 0;
                for(int i=1; i<totalLivros; i++) {
                    if(livros[i].vezesEmprestado > livros[maxIdx].vezesEmprestado) maxIdx = i;
                }
                if(livros[maxIdx].vezesEmprestado == 0) {
                    printf("\nNenhum livro foi emprestado ainda.\n");
                } else {
                    printf("\n--- Livro Mais Emprestado ---\n");
                    printf("Foi emprestado %d vezes!\n", livros[maxIdx].vezesEmprestado);
                    exibirLivro(livros[maxIdx]);
                }
                break;
            case 0: break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}

// ==========================================
// FUNÇÕES AUXILIARES
// ==========================================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu() {
    printf("\n============ BIBLIOTECA ============\n");
    printf("1 - Gerenciar Livros\n");
    printf("2 - Gerenciar Usuários\n");
    printf("3 - Empréstimos\n");
    printf("4 - Relatórios\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

// ==========================================
// MAIN
// ==========================================
int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand((unsigned int)time(NULL));

    // Arrays Principais
    Usuario listaUsuarios[MAX_USUARIOS];
    cadastro listaLivros[MAX_LIVROS];
    Emprestimo listaEmprestimos[MAX_EMPRESTIMOS];

    // Contadores
    int totalUsuarios = 0;
    int totalLivros = 0;
    int totalEmprestimos = 0;

    int opcao;

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = -1;
        } else {
            limparBuffer();
        }

        switch (opcao) {
            case 1:
                gestaoLivros(listaLivros, &totalLivros, listaEmprestimos, totalEmprestimos);
                break;
            case 2:
                gestaoUsuarios(listaUsuarios, &totalUsuarios, listaEmprestimos, totalEmprestimos);
                break;
            case 3:
                gestaoEmprestimos(listaUsuarios, totalUsuarios, listaLivros, totalLivros, listaEmprestimos, &totalEmprestimos);
                break;
            case 4:
                gestaoRelatorios(listaUsuarios, totalUsuarios, listaLivros, totalLivros, listaEmprestimos, totalEmprestimos);
                break;
            case 0:
                printf("\nPrograma encerrado. Até logo!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}