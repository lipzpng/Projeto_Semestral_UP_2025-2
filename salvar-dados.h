#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastra-cliente.h"

// Estrutura representando um "array associativo"
typedef struct {
    // Cliente
    const int id_Cliente;
    const char *nome_Cliente;
    const char *cpf_Cliente;
    const int idade_Cliente;
    const char ativo_Cliente;

    // Produto
    // Pedido
} Dados;

// Enum representando os tipos de arquivo possíveis
typedef enum { CLIENTES, PRODUTOS, PEDIDOS } Arquivo;

// Função que mapeia o enum para o caminho real do arquivo
const char *obterCaminhoArquivo(Arquivo arquivo) {
    switch (arquivo) {
        case CLIENTES: return "clientes.csv";
        case PRODUTOS: return "produtos.csv";
        case PEDIDOS:  return "pedidos.csv";
        default:       return NULL;
    }
}

void salvarDados(Arquivo arquivo, const Dados *dados) {
    if (!dados) {
        fprintf(stderr, "Parâmetros inválidos em salvarDados.\n");
        return;
    }

    const char *caminhoArquivo = obterCaminhoArquivo(arquivo);
    if (!caminhoArquivo) {
        fprintf(stderr, "Tipo de arquivo inválido.\n");
        return;
    }

    FILE *arqv = fopen(caminhoArquivo, "a"); // cria se não existir
    if (!arqv) {
        perror("Erro ao abrir/criar arquivo");
        return;
    }
    
    char *linha = NULL;

    switch (arquivo) {
        case CLIENTES: {
            // Monta dinamicamente a linha "nome;cpf;idade\n"
            const size_t tamNome = strlen(dados->nome_Cliente); // pega o tamanho do nome
            const size_t tamCpf  = strlen(dados->cpf_Cliente);
        
            // Converte o número da idade em string e descobre quantos caracteres ela tem.
            char idadeBuffer[16]; // Buffer para transferir a idade INT para idade CHAR
            const int idadeLengh = snprintf(idadeBuffer, sizeof(idadeBuffer), "%d", dados->idade_Cliente); // snprintf() escrever o valor int para char no buffer. Retorna o numero de caracteres inseridos sem contar o \0.
        
            //                                ;            ;                       \n  \0
            const size_t tamLinha = tamNome + 1 + tamCpf + 1 + (size_t)idadeLengh + 1 + 1; // Calcula o tamanho total da linha que será gravada
        
            linha = (char *)malloc(tamLinha);
            if (!linha) {
                perror("Erro ao alocar memória");
                fclose(arqv);
                return;
            }
        
            snprintf(linha, tamLinha, "%s;%s;%d\n",
                     dados->nome_Cliente, dados->cpf_Cliente, dados->idade_Cliente);
            break;
        }

        case PRODUTOS:

            break;

        case PEDIDOS:

            break;
        
        default:
            perror("Não foi possível processar dados!");
            fclose(arqv);
            return;
    }

    if (fputs(linha, arqv) == EOF) {
        perror("Erro ao escrever no arquivo");
    }
    free(linha);
    fclose(arqv);
}