#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_CLIENTE 10

typedef struct{
    char nome[256]; // 255 chars + '\0'
    char cpf[15]; // "000.000.000-00" -> 14 + '\0'
    int idade;
}Cliente;

Cliente cliente[NUM_CLIENTE];

int i = 0, loop = 1;
typedef enum { NOME, CPF, IDADE } Campo;

static int validaCpf(const char *s) { // formato esperado: 000.000.000-00 (14 chars)
    int idx;
    if (strlen(s) != 14) return 0;
    for (idx = 0; idx < 14; idx++) {
        if (idx == 3 || idx == 7) {
            if (s[idx] != '.') return 0;
        } else if (idx == 11) {
            if (s[idx] != '-') return 0;
        } else {
            if (!isdigit((unsigned char)s[idx])) return 0;
        }
    }
    return 1;
}

void processaCliente(Campo campo) {
    switch(campo) {
        case NOME:
            loop = 1;
            do {
                printf("\nDigite o nome do cliente: ");

                if (scanf(" %255[^\n]", cliente[i].nome) != 1) {
                    puts("Entrada inválida. Tente novamente.");
                    // // limpa possÃ­vel lixo atÃ© nova linha
                    // int c; while ((c = getchar()) != '\n' && c != EOF) {}
                    continue;
                }

                size_t len = strlen(cliente[i].nome);
                if (len == 0) {
                    printf("\nNome não pode ser vazio!\n\n");
                    continue;
                }
                loop = 0;
            } while(loop > 0);
            break;

        case CPF:
            loop = 1;
            do {
                printf("Digite o CPF do cliente: ");
                scanf(" %30[^\n]", cliente[i].cpf);

                if (!validaCpf(cliente[i].cpf)) {
                    printf("\nCPF deve ter o formato 000.000.000-00!\n\n");
                    continue;
                }
                loop = 0;
            } while(loop > 0);
            break;
            
        case IDADE:
            loop = 1;
            do {
                printf("Digite a idade do cliente: ");
                scanf("%i", &cliente[i].idade);

                if (cliente[i].idade <= 0) {
                    printf("\nIdade deve ser maior que zero!\n\n");
                    continue;
                }
                loop = 0;
            } while(loop > 0);
            break;
    }
}

int cadastraCliente(void) {
    char maisClientes = 'S';

    while ((maisClientes == 'S' || maisClientes == 's')) {
        if (i >= NUM_CLIENTE) {
            printf("\n\nLimite de %i clientes atingido.", NUM_CLIENTE);
            break;
        }

        processaCliente(NOME);
        processaCliente(CPF);
        processaCliente(IDADE);

        i++;

        printf("\nCadastrar novo cliente? (S/N): ");
        scanf(" %c", &maisClientes);
    }

    return i-1;
}
