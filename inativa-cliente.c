void inativaCliente(Cliente cliente[]) {
    int idbusca;
    int i;
    int encontrado = 0;

    printf("Digite o ID do cliente que deseja inativar: ");
    scanf("%d", &idbusca);

    for (i = 0; i < NUM_CLIENTE; i++) {
        if (cliente[i].id == idbusca) {
            cliente[i].ativo = 'N';
            encontrado = 1;
            printf("Cliente com ID %d foi inativado.\n", idbusca);
            break;
        }
    }

    if (!encontrado) {
        printf("ID não encontrado, tente novamente!\n");
    }
}
