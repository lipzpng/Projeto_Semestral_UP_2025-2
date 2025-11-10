#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_CLIENTE 10

typedef struct{
    int id;
    char nome[256]; // 255 chars + '\0'
    char cpf[15]; // "000.000.000-00" -> 14 + '\0'
    int idade;
    char ativo; // 'S'|'N'
}Cliente;
Cliente cliente[NUM_CLIENTE];

int i = 0, loop = 1;
typedef enum { NOME, CPF, IDADE } Campo;

static int validaCpf(const char *cpf) { // formato esperado: 000.000.000-00 (14 chars)
    int idx;
    if (strlen(cpf) != 14) return 0;
    for (idx = 0; idx < 14; idx++) {
        if (idx == 3 || idx == 7) {
            if (cpf[idx] != '.') return 0;
        } else if (idx == 11) {
            if (cpf[idx] != '-') return 0;
        } else {
            if (!isdigit((unsigned char)cpf[idx])) return 0;
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
                    puts("Entrada inv�lida. Tente novamente.");
                    continue;
                }

                size_t len = strlen(cliente[i].nome);
                if (len == 0) {
                    printf("\nNome n�o pode ser vazio!\n\n");
                    continue;
                }
                loop = 0;
            } while(loop > 0);
            break;

        case CPF:
            loop = 1;
            do {
                printf("Digite o CPF do cliente: ");
                scanf(" %14[^\n]", cliente[i].cpf);

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

int salvarDados() {

    FILE *arqv = fopen("clientes.csv", "a"); // cria se não existir
    if (!arqv) {
        perror("Erro ao abrir/criar arquivo");
        return 0;
    }
    
    char *linha = NULL;

    // Monta dinamicamente a linha "nome;cpf;idade\n"
    const size_t tamNome = strlen(cliente[i].nome); // pega o tamanho do nome
    const size_t tamCpf  = strlen(cliente[i].cpf);

    // Converte o número da idade em string e descobre quantos caracteres ela tem.
    char idadeBuffer[16]; // Buffer para transferir a idade INT para idade CHAR
    const int idadeLengh = snprintf(idadeBuffer, sizeof(idadeBuffer), "%d", cliente[i].idade); // snprintf() escrever o valor int para char no buffer. Retorna o numero de caracteres inseridos sem contar o \0.

    //                                ;            ;                       \n  \0
    const size_t tamLinha = tamNome + 1 + tamCpf + 1 + (size_t)idadeLengh + 1 + 1; // Calcula o tamanho total da linha que será gravada

    linha = (char *)malloc(tamLinha);
    if (!linha) {
        perror("Erro ao alocar memória");
        fclose(arqv);
        return 0;
    }

    snprintf(linha, tamLinha, "%s;%s;%d\n",
             cliente[i].nome, cliente[i].cpf, cliente[i].idade);

    if (fputs(linha, arqv) == EOF) {
        perror("Erro ao escrever no arquivo");
    }
    free(linha);
    fclose(arqv);

    return 1;
}

int cadastraCliente() {
    char maisClientes = 'S';

    while ((maisClientes == 'S' || maisClientes == 's')) {
        if (i >= NUM_CLIENTE) {
            printf("\n\nLimite de %i clientes atingido.", NUM_CLIENTE);
            break;
        }

        processaCliente(NOME);
        processaCliente(CPF);
        processaCliente(IDADE);

        salvarDados();

        i++;

        printf("\nCadastrar novo cliente? (S|N): ");
        scanf(" %c", &maisClientes);
    }

    return i-1;
}