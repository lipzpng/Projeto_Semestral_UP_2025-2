#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

int inativarCliente() {
    FILE *file, *temp;
    char linha[MAX];
    int idBusca;
    
    printf("Informe o ID do cliente que deseja inativar: ");
    scanf("%d", &idBusca);

    file = fopen("dados/clientes.csv", "r");
    if (!file) {
        printf("Erro ao abrir dados/clientes.csv\n");
        return 1;
    }

    temp = fopen("dados/temp.csv", "w");
    if (!temp) {
        printf("Erro ao criar arquivo temporário\n");
        fclose(file);
        return 1;
    }

    // Lê o cabeçalho e copia diretamente
    if (fgets(linha, MAX, file)) {
        fputs(linha, temp);
    }

    // Processa cada linha do arquivo
    while (fgets(linha, MAX, file)) {
        int id;
        char nome[50], cpf[20], ativo;
        int idade;

        // Faz o parse da linha usando o delimitador ';'
        sscanf(linha, "%d;%49[^;];%19[^;];%d;%c", &id, nome, cpf, &idade, &ativo);

        // Se o ID for o buscado, altera para 'N'
        if (id == idBusca) {
            ativo = 'N';
        }

        // Escreve (possivelmente alterado) no arquivo temporário
        fprintf(temp, "%d;%s;%s;%d;%c\n", id, nome, cpf, idade, ativo);
    }

    fclose(file);
    fclose(temp);

    // Substitui o arquivo original
    remove("dados/clientes.csv");
    rename("dados/temp.csv", "dados/clientes.csv");

    printf("Cliente com ID %d foi inativado. Aperte ENTER para continuar...\n", idBusca);
    getchar();
    getchar(); // dois getchar para o programa esperar o usuario aperta o enter propriamente
    return 0;
}