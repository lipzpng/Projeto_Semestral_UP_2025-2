#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 300

int consultarCliente() {
    FILE *arq;
    char linha[TAM];
    int idBuscado, idArquivo, idade, encontrado = 0;
    char nome[256], cpf[15], ativo;

    printf("Digite o ID do cliente: ");
    scanf("%d", &idBuscado);

    arq = fopen("dados/clientes.csv", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo dados/clientes.csv\n");
        return 1;
    }

    // Lê a primeira linha (cabeçalho) e ignora
    fgets(linha, TAM, arq);

    // Lê linha por linha do arquivo
    while (fgets(linha, TAM, arq) != NULL) {
        // Tenta extrair os campos
        if (sscanf(linha, "%d;%255[^;];%14[^;];%d;%c",
                   &idArquivo, nome, cpf, &idade, &ativo) == 5) {

            if (idArquivo == idBuscado) {
                printf("\n--- Cliente encontrado ---\n");
                printf("   ID: \t %d\n", idArquivo);
                printf(" Nome: \t %s\n", nome);
                printf("  CPF: \t %s\n", cpf);
                printf("Idade: \t %d\n", idade);
                printf("Ativo: \t %c\n", ativo);
                encontrado = 1;
                break;
            }
        }
    }

    fclose(arq);

    if (!encontrado) {
        printf("Cliente com ID %d não encontrado.\n", idBuscado);
    }

    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar(); // dois getchar para o programa esperar o usuario aperta o enter propriamente
    
    return 0;
}
