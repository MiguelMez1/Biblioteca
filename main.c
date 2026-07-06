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
    printf("\n === MENU DE LIVROS === \n");
    
    printf("\n1. Cadastro de Livros.");
    printf("\n2. Buscar.");
    printf("\n3. Listar (cadastrados).");
    printf("\n4. Alterar itens.");
    printf("\n5. Excluir.\n");
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
            printf("alterar itens");
            break;

        case 5:
            printf("excluir");
            break;
        }
    } while (opcao !=0);
}