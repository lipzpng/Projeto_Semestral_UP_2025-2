#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para salvar dados em um arquivo usando ponteiros e alocação dinâmica
void salvarDados(const char *caminhoArquivo, const char *entrada) {
    // Ponteiro para o arquivo
    FILE *arquivo;

    // Abre o arquivo em modo append (cria se não existir)
    arquivo = fopen(caminhoArquivo, "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Alocação dinâmica para armazenar uma cópia dos dados
    char *dados = (char *) malloc((strlen(entrada) + 1) * sizeof(char));
    if (dados == NULL) {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        return;
    }

    // Copia a string de entrada para a memória alocada
    strcpy(dados, entrada);

    // Escreve os dados no arquivo
    if (fputs(dados, arquivo) == EOF) {
        perror("Erro ao escrever no arquivo");
    } else {
        printf("Dados salvos com sucesso em '%s'\n", caminhoArquivo);
    }

    // Libera a memória alocada
    free(dados);

    // Fecha o arquivo
    fclose(arquivo);
}

// Exemplo de uso
int main() {
    char *arquivo = "dados.txt";

    // Cria dinamicamente o conteúdo
    char *conteudo = (char *) malloc(100 * sizeof(char));
    if (conteudo == NULL) {
        perror("Erro ao alocar memória para o conteúdo");
        return 1;
    }

    // Lê dados do usuário
    printf("Digite o texto que deseja salvar: ");
    fgets(conteudo, 100, stdin); // lê até 99 caracteres (reserva 1 para '\0')

    // Chama a função para salvar
    salvarDados(arquivo, conteudo);

    // Libera a memória usada
    free(conteudo);

    return 0;
}
''