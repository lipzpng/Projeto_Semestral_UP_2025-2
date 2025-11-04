#include <stdio.h>
#include <unistd.h>

void MenuLoja(){
    int opcao;

    do
    {
    printf("\n*=*=*=*=*=MENU LOJA DE JOGOS=*=*=*=*=*\n");
    printf("\n1 - Cadastrar cliente \n");
    printf("\n2 - Listar clientes\n");
    printf("\n3 - Consultar clientes\n");
    printf("\n4 - Desativar cliente\n");
    printf("\n5 - Registrar compra\n");
    printf("\n6 - Sair da loja\n");
    printf("\nDigite a opção desejada: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        // funcao cadastro 
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
        printf("\nOpção inválida, escolha entre 1 e 6!\n");
        sleep(3);
        break;
    }
    } while (opcao != 6);
    
}
int main(){
    MenuLoja();

    return 0;
}
