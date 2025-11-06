#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura representando um "array associativo"
typedef struct {
    const char *nome;
    const char *cpf;
    int idade;
} Dados;

// Enum representando os tipos de arquivo possíveis
typedef enum { CLIENTES, PRODUTOS, PEDIDOS } Arquivos;

// Função que mapeia o enum para o caminho real do arquivo
const char *obterCaminhoArquivo(Arquivos tipo) {
    switch (tipo) {
        case CLIENTES:
            return "clientes.txt";
        case PRODUTOS:
            return "produtos.txt";
        case PEDIDOS:
            return "pedidos.txt";
        default:
            return NULL;
    }
}

void salvarDados(Arquivos tipoArquivo, const Dados *dados) {
    if (!dados || !dados->nome || !dados->cpf) {
        fprintf(stderr, "Parâmetros inválidos em salvarDados.\n");
        return;
    }

    const char *caminhoArquivo = obterCaminhoArquivo(tipoArquivo);
    if (!caminhoArquivo) {
        fprintf(stderr, "Tipo de arquivo inválido.\n");
        return;
    }

    FILE *arquivo = fopen(caminhoArquivo, "a"); // cria se não existir
    if (!arquivo) {
        perror("Erro ao abrir/criar arquivo");
        return;
    }

    // Monta dinamicamente a linha "nome;cpf;idade\n"
    const size_t tamNome = strlen(dados->nome); // pega o tamanho do nome
    const size_t tamCpf  = strlen(dados->cpf);

    // Converte o número da idade em string e descobre quantos caracteres ela tem.
    char idadeBuffer[16]; // Buffer para transferir a idade INT para idade CHAR
    const int idadeLengh = snprintf(idadeBuffer, sizeof(idadeBuffer), "%d", dados->idade); // snprintf() escrever o valor int para char no buffer. Retorna o numero de caracteres inseridos sem contar o \0.

    //                                ;            ;                       \n  \0
    const size_t tamLinha = tamNome + 1 + tamCpf + 1 + (size_t)idadeLengh + 1 + 1; // Calcula o tamanho total da linha que será gravada

    char *linha = (char *)malloc(tamLinha);
    if (!linha) {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        return;
    }

    snprintf(linha, tamLinha, "%s;%s;%d\n", dados->nome, dados->cpf, dados->idade);

    if (fputs(linha, arquivo) == EOF) {
        perror("Erro ao escrever no arquivo");
    }

    free(linha);
    fclose(arquivo);
}