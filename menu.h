#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "cadastra-cliente.h"

void menu(){
    int opcao;

    do {
    	system("cls"); // limpa a tela
        puts("*=*=*=*=*=MENU LOJA DE JOGOS=*=*=*=*=*");
        puts("1 - Cadastrar cliente ");
        puts("2 - Listar clientes");
        puts("3 - Consultar clientes");
        puts("4 - Desativar cliente");
        puts("5 - Registrar compra");
        puts("6 - Sair da loja");
        printf("\nDigite a op��o desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            cadastraCliente();
            break;
        case 2:
            // funcao listagem
            break;
        case 3:
            // funcao consulta
            break;
        case 4:
            // funcao desativação
            break;
        case 5:
            // funcao registro
            break;
        case 6:
            printf("\nDesligando sistema...");
            sleep(2);
            break;
        default:
            printf("\nOp��o inv�lida, escolha entre 1 e 6!\n");
            sleep(3);
            break;
        }
    } while (opcao != 6);
}
