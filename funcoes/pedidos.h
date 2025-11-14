#include <stdio.h>
#include <stdlib.h>

int registrarPedido() {
    int idCliente;
    char produto[256];

    printf("\nDigite o id do cliente para realizar o pedido: ");
    scanf("%i", &idCliente);

    printf("Digite o produto: ");
    scanf(" %255[^\n]", produto);
    
    int cabecalho = 0;
    FILE *f = fopen("dados/pedidos.csv", "r");
    if (f == NULL) {
        cabecalho = 1;
    } else {
        fclose(f);
    }
    
    FILE *arquivo = fopen("dados/pedidos.csv", "a"); // abre em modo append
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    if (cabecalho) {
        fprintf(arquivo, "Id Cliente; Produto\n");
    }
    
    // Escreve no formato CSV: ID,Produto
    fprintf(arquivo, "%d;%s\n", idCliente, produto);
    fclose(arquivo);

    printf("\n\nPedido salvo com sucesso! Pressione ENTER para continuar...");
    getchar();
    getchar(); // dois getchar para o programa esperar o usuario aperta o enter propriamente

    return 0;
}