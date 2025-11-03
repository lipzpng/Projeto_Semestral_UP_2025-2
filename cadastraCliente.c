#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

typedef struct{
    char nome[31];
    char cpf[14]; // 000.000.000-00
    int idade;
}Cliente;

Cliente cliente[10];

void cadastraCliente() {
    int i = 0;
    do {
        processaCliente('nome');
        processaCliente('cpf');
        processaCliente('idade');

        printf("\nCadastrar novo cliente? (S/N): ");
        scanf("%c", maisClientes);

        i = (maisClientes == 'S' || maisClientes == 's') ? i + 1 : i;
    } while(i > 0);
    
    return 0;
}

void processaCliente(char campo) {
    switch(campo) {
        case 'nome':
            do {
                int loop = 1
                printf("Digite o %s do cliente: ", campo);
                scanf(" %30[^\n]", cliente[i].nome);

                if (lengh(cliente[i].nome) > 254) {
                    printf("\nNome do cliente deve ter no máximo 255 caracteres!");
                } else {
                    loop = 0;
                }
            } while(loop > 0);
        break;
        case 'cpf':
            do {
                int loop = 1
                printf("Digite o %s do cliente: ", campo);
                scanf(" %30[^\n]", cliente[i].cpf);

                if (cliente[i].cpf[3] != '.' || cliente[i].cpf[7] != '.' || cliente[i].cpf[11] != '-') {
                    printf("\nCpf deve ter o formato 000.000.000-00!");
                } else {
                    loop = 0;
                }
            } while(loop > 0);
        break;
        case 'idade':
            do {
                int loop = 1
                printf("Digite o %s do cliente: ", campo);
                scanf(" %30[^\n]", cliente[i].idade);

                if (lengh(cliente[i].nome) <= 0) {
                    printf("\nIdade deve ser maior que zero!");
                } else {
                    loop = 0;
                }
            } while(loop > 0);
        break;
    }
}