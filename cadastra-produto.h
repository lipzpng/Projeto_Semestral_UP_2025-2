#ifndef CADASTRA_PRODUTO_H
#define CADASTRA_PRODUTO_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_PRODUTOS 50

typedef struct {
 int id;
 char nome[100];
 float preco;
}
Produto;
Produto produtos[MAX_PRODUTOS];
int totalProdutos = 0;

void listaProdutos(){
  system("cls");
  printf("---Lista de Produtos---\n");
  if (totalProdutos == 0){
    printf("Nenhum produto cadastrado.\n");
} else {
    printf("ID | Nome\t\t\t|Preco\n");
printf("---------------------\n");
  for (int k = 0; k < totalProdutos; k++){
    printf("%-2d | %-20s | R$ %.2f\n", produtos[k].preco);
  }
}
printf("\n\nPrecione Enter para continuar...");

int c;
while((c = getchar()) != '\n' && c != EOF);
getchar();
}


void cadastraProduto(){
  system("cls");
  printf("---Cadastrar novo Produto---\n");

if (totalProdutos >= MAX_PRODUTOS){
  printf("Limite maximo de produtos atingido!\n");
  sleep(2);
  return;
}

produtos[totalProdutos].id = totalProdutos;

printf("Digite o nome do produto: ");
scanf(" %99[^\n]",
  produtos[totalProdutos].nome);

printf("Digite o preco do produto(ex:99.90): ");
scanf("%f",&produtos[totalProdutos.preco);

totalProdutos++;

printf("\nProduto cadastrado com sucesso!\n");
sleep(2);
}
#endif



