#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_LIVROS 100
#define MAX_USUARIOS 50
#define MAX_EMPRESTIMOS 200
#define TAM_TEXTO 100

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
    int vezesEmprestado;
} Livro;

typedef struct {
    int idUsuario;
    int idLivro;
    int ativo;
} Emprestimo;

void limparBuffer();

// gestão de usuarios

int cadastrarCodigoUsuario(Usuario lista[], int total) {
    int idCodigo, valido;
    do {
        valido = 1;
        idCodigo = rand() % 900000 + 100000; //cria id aleatorio
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

void alterarUsuario(Usuario usuarios[], int total) {
    int codigo, encontrado = 0;
    
    printf("\nDigite o código do usuário que deseja alterar: ");
    scanf("%d", &codigo);
    limparBuffer(); // Limpa o \n deixado pelo scanf

    for(int i = 0; i < total; i++) {
        if(usuarios[i].idCodigo == codigo) {
            printf("\n=== ALTERAÇÃO DE DADOS DO USUÁRIO ===\n");

            // Leitura do Nome (String)
            printf("Novo nome: ");
            fgets(usuarios[i].nome, sizeof(usuarios[i].nome), stdin);
            usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = '\0';

            // Leitura do Telefone (Int)
            printf("Novo telefone: ");
            scanf("%d", &usuarios[i].telefone);
            limparBuffer(); // Essencial aqui antes do próximo fgets!

            // Leitura do E-mail (String)
            printf("Novo e-mail: ");
            fgets(usuarios[i].email, sizeof(usuarios[i].email), stdin);
            usuarios[i].email[strcspn(usuarios[i].email, "\n")] = '\0';

            printf("\nUsuário alterado com sucesso!\n");
            encontrado = 1;
            break; // Sai do loop pois já encontrou e alterou o usuário
        }
    }
    
    if(!encontrado) {
        printf("\nUsuário não encontrado.\n");
    }
}

void buscarUsuarioPorTelefone(Usuario usuarios[], int total) {
    int telBusca, encontrado = 0;
    
    printf("\nDigite o telefone: ");
    scanf("%d", &telBusca);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (usuarios[i].telefone == telBusca) {
            exibirUsuario(usuarios[i]);
            encontrado = 1;
        }
    }
    
    if (!encontrado) {
        printf("\nNenhum usuário encontrado com este telefone.\n");
    }
}

void buscarUsuarioPorId(Usuario usuarios[], int total) {
    int idBusca, encontrado = 0;
    
    printf("\nDigite o código (ID) do usuário: ");
    scanf("%d", &idBusca);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (usuarios[i].idCodigo == idBusca) {
            exibirUsuario(usuarios[i]);
            encontrado = 1;
            break; // Opcional: break porque o ID é único, então não precisa continuar buscando
        }
    }
    
    if (!encontrado) {
        printf("\nNenhum usuário encontrado com este código.\n");
    }
}

void buscarUsuarioPorNome(Usuario usuarios[], int total) {
    char nomeBusca[50];
    int encontrado = 0;
    
    printf("\nDigite o nome (ou parte dele) para busca: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        // strstr verifica se 'nomeBusca' está contido dentro do nome cadastrado
        if (strstr(usuarios[i].nome, nomeBusca) != NULL) {
            exibirUsuario(usuarios[i]); 
            encontrado = 1;
        }
    }
    
    if (!encontrado) {
        printf("\nNenhum usuário encontrado com este nome.\n");
    }
}

void menuBuscaUsuarios(Usuario usuarios[], int total) {
    int opcao;
    
    do {
        printf("\n==== MENU DE BUSCA DE USUÁRIOS ====\n");
        printf("1 - Buscar por Código (ID)\n");
        printf("2 - Buscar por Nome\n");
        printf("3 - Buscar por Telefone\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        
        if (scanf("%d", &opcao) != 1) { 
            limparBuffer(); 
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1: 
                buscarUsuarioPorId(usuarios, total); 
                break;
            case 2: 
                buscarUsuarioPorNome(usuarios, total); 
                break;
            case 3: 
                buscarUsuarioPorTelefone(usuarios, total); 
                break;
            case 0: 
                break;
            default: 
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}

void gestaoUsuarios(Usuario usuarios[], int *totalUsuarios, Emprestimo emprestimos[], int totalEmprestimos) {
    int opcao;
    do {
        printf("\n==== GERENCIAR USUÁRIOS ====\n");
        printf("1 - Cadastrar novo usuário\n");
        printf("2 - Excluir usuário\n");
        printf("3 - Listar usuários\n");
        printf("4 - Alterar usuários\n");
        printf("5 - Buscar usuários\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }
        limparBuffer();

        switch (opcao) {
            case 1: cadastrarUsuario(usuarios, totalUsuarios); break;
            case 2: excluirUsuario(usuarios, totalUsuarios, emprestimos, totalEmprestimos); break;
            case 3: listarUsuarios(usuarios, *totalUsuarios); break;
            case 4: alterarUsuario(usuarios, *totalUsuarios); break;
            case 5: menuBuscaUsuarios(usuarios, *totalUsuarios); break;
            case 0: break;
            default: printf("\nOpção inválida!\n");
        }
    } while(opcao != 0);
}

//gestão de livros =========

int cadastrarCodigoLivro(Livro lista[], int total) {
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

void cadastrarLivro(Livro lista[], int *total) {
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

    do {
        printf("Categoria: ");
        fgets(lista[i].categoria, sizeof lista[i].categoria, stdin);
        lista[i].categoria[strcspn(lista[i].categoria, "\n")] = '\0';
    } while (strlen(lista[i].categoria) == 0);
   
    printf("Ano de publicação: ");
    scanf("%d", &lista[i].ano);

    do {
        printf("Quantidade total a cadastrar: ");
        scanf("%d", &lista[i].quantTotal);
        if(lista[i].quantTotal < 0) printf("A quantidade não pode ser negativa!\n");
    } while (lista[i].quantTotal < 0);

    lista[i].quantDispo = lista[i].quantTotal; 
    lista[i].vezesEmprestado = 0; 

    (*total)++;
    printf("\nLivro cadastrado com sucesso!\n");
}

void exibirLivro(Livro livro) {
    printf("\nCódigo: %d | Título: %s | Autor: %s | Categoria: %s | Ano: %d | Disp: %d/%d\n",
           livro.idCodigo, livro.titulo, livro.autor, livro.categoria, livro.ano, livro.quantDispo, livro.quantTotal);
}

void excluirLivro(Livro lista[], int *totalLivros, Emprestimo emprestimos[], int totalEmprestimos) {
    int codigo, posicao = -1;
    printf("\nDigite o código do livro que deseja excluir: ");
    scanf("%d", &codigo);
    limparBuffer();

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

void listarLivros(Livro lista[], int total) {
    if (total == 0) { printf("\nNenhum livro cadastrado.\n"); return; }
    printf("\n==== LISTA DE LIVROS ====\n");
    for (int i = 0; i < total; i++) exibirLivro(lista[i]);
}

void alterarLivro(Livro livros[], int total) {
    int codigo, encontrado = 0;
    printf("\nDigite o código do livro que deseja alterar: ");
    scanf("%d", &codigo);
    limparBuffer();

    for(int i = 0; i < total; i++) {
        if(livros[i].idCodigo == codigo) {
            printf("\n=== ALTERAÇÃO DE DADOS ===\n");

            printf("Novo título: ");
            fgets(livros[i].titulo, sizeof(livros[i].titulo), stdin);
            livros[i].titulo[strcspn(livros[i].titulo, "\n")] = '\0';

            printf("Novo autor: ");
            fgets(livros[i].autor, sizeof(livros[i].autor), stdin);
            livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';

            printf("Nova categoria: ");
            fgets(livros[i].categoria, sizeof(livros[i].categoria), stdin);
            livros[i].categoria[strcspn(livros[i].categoria, "\n")] = '\0';

            printf("Novo ano: ");
            scanf("%d", &livros[i].ano);
            
            printf("Nova quantidade total: ");
            int antigaQuantTotal = livros[i].quantTotal;
            scanf("%d", &livros[i].quantTotal);
            livros[i].quantDispo += (livros[i].quantTotal - antigaQuantTotal); 
            limparBuffer();

            printf("\nLivro alterado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if(!encontrado) printf("\nLivro não encontrado.\n");
}

void buscarPorCodigo(Livro livros[], int total) {
    int codigo, encontrado = 0;
    printf("\nDigite o código: ");
    scanf("%d", &codigo);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (livros[i].idCodigo == codigo) {
            exibirLivro(livros[i]);
            encontrado = 1; break;
        }
    }
    if (!encontrado) printf("\nLivro não encontrado!\n");
}

void buscarPorTitulo(Livro livros[], int total) {
    char titulo[TAM_TEXTO];
    int encontrado = 0;
    printf("\nDigite o título: ");
    fgets(titulo, TAM_TEXTO, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strstr(livros[i].titulo, titulo) != NULL) {
            exibirLivro(livros[i]); encontrado = 1;
        }
    }
    if (!encontrado) printf("\nNenhum livro encontrado.\n");
}

void buscarPorAutor(Livro livros[], int total) {
    char autor[TAM_TEXTO];
    int encontrado = 0;
    printf("\nDigite o autor: ");
    fgets(autor, TAM_TEXTO, stdin);
    autor[strcspn(autor, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strstr(livros[i].autor, autor) != NULL) {
            exibirLivro(livros[i]); encontrado = 1;
        }
    }
    if (!encontrado) printf("\nNenhum livro encontrado.\n");
}

void buscarPorCategoria(Livro livros[], int total) {
    char categoria[TAM_TEXTO];
    int encontrado = 0;
    printf("\nDigite a categoria: ");
    fgets(categoria, TAM_TEXTO, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strstr(livros[i].categoria, categoria) != NULL) {
            exibirLivro(livros[i]); encontrado = 1;
        }
    }
    if (!encontrado) printf("\nNenhum livro encontrado.\n");
}

void buscarPorAno(Livro livros[], int total) {
    int ano, encontrado = 0;
    printf("\nDigite o ano: ");
    scanf("%d", &ano);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (livros[i].ano == ano) {
            exibirLivro(livros[i]); encontrado = 1;
        }
    }
    if (!encontrado) printf("\nNenhum livro encontrado.\n");
}

void menuBuscaLivros(Livro livros[], int total) {
    int opcao;
    do {
        printf("\n==== MENU DE BUSCA DE LIVROS ====\n");
        printf("1 - Buscar por Código\n");
        printf("2 - Buscar por Título\n");
        printf("3 - Buscar por Autor\n");
        printf("4 - Buscar por Categoria\n");
        printf("5 - Buscar por Ano\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }
        limparBuffer();

        switch (opcao) {
            case 1: buscarPorCodigo(livros, total); break;
            case 2: buscarPorTitulo(livros, total); break;
            case 3: buscarPorAutor(livros, total); break;
            case 4: buscarPorCategoria(livros, total); break;
            case 5: buscarPorAno(livros, total); break;
            case 0: break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}

void gestaoLivros(Livro livros[], int *totalLivros, Emprestimo emprestimos[], int totalEmprestimos) {
    int opcao;
    do {
        printf("\n==== GERENCIAR LIVROS ====\n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Alterar Livro\n");
        printf("3 - Excluir Livro\n");
        printf("4 - Listar Livros\n");
        printf("5 - Buscar Livros\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }
        limparBuffer();

        switch (opcao) {
            case 1: cadastrarLivro(livros, totalLivros); break;
            case 2: alterarLivro(livros, *totalLivros); break;
            case 3: excluirLivro(livros, totalLivros, emprestimos, totalEmprestimos); break;
            case 4: listarLivros(livros, *totalLivros); break;
            case 5: menuBuscaLivros(livros, *totalLivros); break;
            case 0: break;
            default: printf("\nOpção inválida!\n");
        }
    } while(opcao != 0);
}

//emprestimos

int buscarIndiceUsuario(Usuario usuarios[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (usuarios[i].idCodigo == codigo) return i;
    }
    return -1;
}

int buscarIndiceLivro(Livro livros[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (livros[i].idCodigo == codigo) return i;
    }
    return -1;
}

void realizarEmprestimo(Usuario usuarios[], int totalUsuarios, Livro livros[], int totalLivros, Emprestimo emprestimos[], int *totalEmprestimos) {
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

    if (livros[idxLivro].quantDispo <= 0) {
        printf("\nNão há exemplares disponíveis deste livro no momento!\n"); return;
    }

    for (int i = 0; i < *totalEmprestimos; i++) {
        if (emprestimos[i].idUsuario == idUser && emprestimos[i].idLivro == idLivro && emprestimos[i].ativo == 1) {
            printf("\nEste usuário já possui uma cópia deste livro emprestada!\n"); return;
        }
    }

    emprestimos[*totalEmprestimos].idUsuario = idUser;
    emprestimos[*totalEmprestimos].idLivro = idLivro;
    emprestimos[*totalEmprestimos].ativo = 1;
    (*totalEmprestimos)++;

    livros[idxLivro].quantDispo--;
    livros[idxLivro].vezesEmprestado++;

    printf("\nEmpréstimo realizado com sucesso!\n");
}

void devolverLivro(Usuario usuarios[], int totalUsuarios, Livro livros[], int totalLivros, Emprestimo emprestimos[], int totalEmprestimos) {
    int idUser, idLivro;
    printf("\nDigite o Código do Usuário: ");
    scanf("%d", &idUser);
    printf("Digite o Código do Livro a devolver: ");
    scanf("%d", &idLivro);

    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idUsuario == idUser && emprestimos[i].idLivro == idLivro && emprestimos[i].ativo == 1) {
            emprestimos[i].ativo = 0; 
           
            int idxLivro = buscarIndiceLivro(livros, totalLivros, idLivro);
            if (idxLivro != -1) livros[idxLivro].quantDispo++; 

            printf("\nLivro devolvido com sucesso!\n");
            return;
        }
    }
    printf("\nNenhum empréstimo ativo encontrado para este usuário e livro!\n");
}

void gestaoEmprestimos(Usuario usuarios[], int totalUsuarios, Livro livros[], int totalLivros, Emprestimo emprestimos[], int *totalEmprestimos) {
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

//relatorios

void gestaoRelatorios(Usuario usuarios[], int totalUsuarios, Livro livros[], int totalLivros, Emprestimo emprestimos[], int totalEmprestimos) {
    int opcao;
    do {
        printf("\n==== RELATÓRIOS ====\n");
        printf("1 - Todos os livros\n");
        printf("2 - Livros disponíveis\n");
        printf("3 - Livros emprestados\n");
        printf("4 - Usuários cadastrados\n");
        printf("5 - Usuários com empréstimos ativos\n");
        printf("6 - Quantidade total de livros no acervo\n");
        printf("7 - Livro mais emprestado\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }
        limparBuffer();

        switch (opcao) {
            case 1: 
                listarLivros(livros, totalLivros);
                break;
            case 2: 
                printf("\n--- Livros Disponíveis ---\n");
                for(int i=0; i<totalLivros; i++) {
                    if(livros[i].quantDispo > 0) exibirLivro(livros[i]);
                }
                break;
            case 3: 
                printf("\n--- Livros Emprestados ---\n");
                for(int i=0; i<totalLivros; i++) {
                    if(livros[i].quantDispo < livros[i].quantTotal) exibirLivro(livros[i]);
                }
                break;
            case 4: 
                listarUsuarios(usuarios, totalUsuarios);
                break;
            case 5: 
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
            case 6: 
                {
                    int totalAcervo = 0;
                    for(int i=0; i<totalLivros; i++) totalAcervo += livros[i].quantTotal;
                    printf("\nQuantidade total de volumes no acervo: %d\n", totalAcervo);
                }
                break;
            case 7:
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

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menuPrincipal() {
    printf("\n============ BIBLIOTECA ============\n");
    printf("1 - Gerenciar Livros\n");
    printf("2 - Gerenciar Usuários\n");
    printf("3 - Empréstimos e Devoluções\n");
    printf("4 - Relatórios do Sistema\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand((unsigned int)time(NULL));

    Usuario listaUsuarios[MAX_USUARIOS];
    Livro listaLivros[MAX_LIVROS];
    Emprestimo listaEmprestimos[MAX_EMPRESTIMOS];

    int totalUsuarios = 0;
    int totalLivros = 0;
    int totalEmprestimos = 0;

    int opcao;

    do {
        menuPrincipal();
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
                printf("\nPrograma encerrado.\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}