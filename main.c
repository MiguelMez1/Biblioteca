//MENU MAIN - Integrações de todas as 'partes' do trabalho, neste menu, inves de chamar funções, ele chama arquivos.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "cadastro.h"
#define MAX 100

cadastro lista[MAX];

int total = 0;
//Função para exibir MENU.
void menu()
{
    printf("\n === MENU DE OPÇÕES === \n");
    
    printf("\n1. Cadastro de Livros.");
    printf("\n2. Buscar.");
    printf("\n3. Listar (cadastrados).");
    printf("\n4. Empréstimos.");
    printf("\n5. Alterar itens.");
    printf("\n6. Excluir.\n");
}

int main()
{ 
    SetConsoleOutputCP(CP_UTF8);
    int opcao;
    menu();
    printf("\nDigite aqui: ");
    scanf("%d", &opcao);
    
    do
    {
        switch (opcao)
        {
        case 1:
            cadastrarLivro(lista, &total);          
            break;
            
        case 2:
            printf("buscar");
            break;

        case 3:
            printf("lista");
            break;
        
        case 4:
            printf("emprestimo");
            break;

        case 5:
            printf("alterar itens");
            break;
        }
    } while (opcao !=0);
}