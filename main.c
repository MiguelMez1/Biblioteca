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
    printf("\n === MENU PRINCIPAL === \n");
    
    printf("\n1. Gestão de Livros.");
    printf("\n2. Gestão de Usuarios.");
    printf("\n3. Emprestimos");
    printf("\n4. Relatorio.");
    printf("\n5. Sair.\n");
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
            gestaoLivros(lista, &total);          
            break;
            
        case 2:
            printf("usuario");
            break;

        case 3:
            printf("emprestimo");
            break;


        case 4:
            printf("relatorio");
            break;

        case 5:
            printf("sair");
            break;
        }
    } while (opcao !=0);
}