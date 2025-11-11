void listarCliente(Cliente cliente[]){

    int i, j, opcao;
    Cliente temp; // variavel temporaria para fazer a troca no strcmp

    printf("Deseja listar por : \n");
    printf("1 - NOME\n");
    printf("2 - CPF\n");
    printf("Escolha a opção desejada: ");
    scanf("%d", &opcao);
    //bublle sort para ordenação dos nomes
    for ( i = 0; i < NUM_CLIENTE - 1; i++) {
        for( j = i + 1; j < NUM_CLIENTE; j++) {
           if (opcao == 1) {
                // compara e troca as strings de acordo a com ordem alfabética
            if (strcmp(cliente[i].nome, cliente[j].nome) > 0) {
                    temp = cliente[i];
                    cliente[i] = cliente[j];
                    cliente[j] = temp;
                }
           }else if(opcao == 2) {
                 
            if (strcmp(cliente[i].cpf, cliente[j].cpf) > 0) {
                    temp = cliente[i];
                    cliente[i] = cliente[j];
                    cliente[j] = temp;
                }
           }
                
        }
    }
        printf("\n%-5s %-25s %-15s %-6s %-6s\n", "ID", "Nome", "CPF", "Idade", "Ativo");
        printf("-------------------------------------------------------------\n");
        for (i = 0; i < NUM_CLIENTE; i++) {
            if (cliente[i].ativo == 'S') {  //print somente nos clientes que estão ativos
                printf("%-5d %-25s %-15s %-6d %-6c\n", cliente[i].id, cliente[i].nome, cliente[i].cpf, cliente[i].idade, cliente[i].ativo);
        }
    }
}
    