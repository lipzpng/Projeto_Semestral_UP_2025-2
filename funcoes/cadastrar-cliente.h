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

    int cabecalho = 0;
    FILE *f = fopen("dados/clientes.csv", "r");
    if (f == NULL) {
        cabecalho = 1;
    } else {
        fclose(f);
    }
    
    FILE *arqv = fopen("dados/clientes.csv", "a"); // cria se nÃ£o existir
    if (!arqv) {
        perror("Erro ao abrir/criar arquivo");
        return 0;
    }
    
    char *linha = NULL;

    // Monta dinamicamente a linha "id;nome;cpf;idade;S\n"
    const size_t tamId   = 12;  // espaÃ§o suficiente p/ int convertido em texto
    const size_t tamNome = strlen(cliente[i].nome); // pega o tamanho do nome
    const size_t tamCpf  = strlen(cliente[i].cpf);

    // Converte o número da idade em string e descobre quantos caracteres ela tem.
    char idadeBuffer[16]; // Buffer para transferir a idade INT para idade CHAR
    const int idadeLengh = snprintf(idadeBuffer, sizeof(idadeBuffer), "%d", cliente[i].idade); // snprintf() escrever o valor int para char no buffer. Retorna o numero de caracteres inseridos sem contar o \0.

    // Converte ID para string
    char idBuffer[16];
    const int idLength = snprintf(idBuffer, sizeof(idBuffer), "%d", cliente[i].id);

    // Flag de ativo
    char ativo = 'S';

    // Calcula o tamanho total da linha que serÃ¡ gravada
    // id; nome; cpf; idade; flag\n\0
    const size_t tamLinha =
        idLength + 1 +
        tamNome + 1 +
        tamCpf + 1 +
        idadeLengh + 1 +
        1 + 1;

    linha = (char *)malloc(tamLinha);
    if (!linha) {
        perror("Erro ao alocar memória");
        fclose(arqv);
        return 0;
    }

    if (cabecalho) {
        fprintf(arqv, "Id; Nome; Cpf; Idade; Ativo\n");
    }

    snprintf(linha, tamLinha, "%s;%s;%s;%d;%c\n",
            idBuffer, cliente[i].nome, cliente[i].cpf, cliente[i].idade, ativo);

    if (fputs(linha, arqv) == EOF) {
        perror("Erro ao escrever no arquivo");
    }
    
    free(linha);
    fclose(arqv);

    return 1;
}

int retornaUltimoId() {
    FILE *arquivo = fopen("dados/clientes.csv", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char linha[256];
    int maiorId = 0;
    int idAtual;

    // Lê e descarta o cabeçalho
    fgets(linha, sizeof(linha), arquivo);

    // Lê as linhas seguintes
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Extrai o ID antes do primeiro ';'
        char *token = strtok(linha, ";");
        if (token != NULL) {
            idAtual = atoi(token);
            if (idAtual > maiorId) {
                maiorId = idAtual;
            }
        }
    }

    fclose(arquivo);
    return maiorId;
}

int cadastraCliente() {
    char maisClientes = 'S';

    while ((maisClientes == 'S' || maisClientes == 's')) {
        if (i >= NUM_CLIENTE) {
            printf("\n\nLimite de %i clientes atingido.", NUM_CLIENTE);
            break;
        }
        
        int id = retornaUltimoId();
        cliente[i].id = id + 1;

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