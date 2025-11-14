void listarCliente() {
    FILE *arq;
    Cliente *clientes = NULL;  // vetor dinâmico
    int qtd = 0;               // quantidade lida
    int capacidade = 0;        // capacidade do vetor
    int i, j, opcao;
    Cliente temp;
    char linha[512];

    arq = fopen("dados/clientes.csv", "r");
    if (!arq) {
        perror("Erro ao abrir arquivo dados/clientes.csv");
        return;
    }

    // Lê e descarta cabeçalho
    if (!fgets(linha, sizeof(linha), arq)) {
        printf("Arquivo vazio ou inválido.\n");
        fclose(arq);
        return;
    }

    // ---- Leitura dinâmica de TODOS os clientes ----
    while (fgets(linha, sizeof(linha), arq)) {

        // aumenta a capacidade do vetor quando necessário
        if (qtd == capacidade) {
            capacidade = (capacidade == 0) ? 10 : capacidade * 2;
            clientes = realloc(clientes, capacidade * sizeof(Cliente));
            if (!clientes) {
                perror("Erro ao realocar memória");
                fclose(arq);
                return;
            }
        }

        // Lê a linha
        if (sscanf(linha, " %d ; %255[^;] ; %14[^;] ; %d ; %c",
                   &clientes[qtd].id,
                   clientes[qtd].nome,
                   clientes[qtd].cpf,
                   &clientes[qtd].idade,
                   &clientes[qtd].ativo) == 5)
        {
            qtd++;
        }
    }

    fclose(arq);

    if (qtd == 0) {
        printf("Nenhum cliente encontrado.\n");
        free(clientes);
        return;
    }

    // ---- Escolha de ordenação ----
    printf("Deseja listar por : \n");
    printf("1 - NOME\n");
    printf("2 - CPF\n");
    printf("Escolha a opção desejada: ");
    scanf("%d", &opcao);

    // ---- Ordenação (bubble sort) ----
    for (i = 0; i < qtd - 1; i++) {
        for (j = i + 1; j < qtd; j++) {
            if (opcao == 1) {
                if (strcmp(clientes[i].nome, clientes[j].nome) > 0) {
                    temp = clientes[i];
                    clientes[i] = clientes[j];
                    clientes[j] = temp;
                }
            } else if (opcao == 2) {
                if (strcmp(clientes[i].cpf, clientes[j].cpf) > 0) {
                    temp = clientes[i];
                    clientes[i] = clientes[j];
                    clientes[j] = temp;
                }
            }
        }
    }

    // ---- Impressão ----
    printf("\n%-5s %-25s %-15s %-6s %-6s\n", "ID", "Nome", "CPF", "Idade", "Ativo");
    printf("-------------------------------------------------------------\n");

    for (i = 0; i < qtd; i++) {
        // Descomentar se quiser exibir somente os clientes ativos
        // if (clientes[i].ativo == 'S') {
            printf("%-5d %-25s %-15s %-6d %-6c\n",
                   clientes[i].id,
                   clientes[i].nome,
                   clientes[i].cpf,
                   clientes[i].idade,
                   clientes[i].ativo);
        // }
    }

    free(clientes);

    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar(); // dois getchar para o programa esperar o usuario aperta o enter propriamente
}