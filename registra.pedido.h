#ifndef REGISTRA_PEDIDO_H
#define REGISTRA_PEDIDO_H

#include <stdio.h>
#include "cadastra-cliente.h"
#include "cadastra-produto.h"

#define MAX_PEDIDOS 100

typedef enum {
  PENDENTE,
  PAGO,
  ENVIADO,
  CONCLUIDO,
  CANCELADO
} StatusPedido;

typedef struct {
  int id; 
  int clienteIndex;
  int produtoInex;
  int quantidade;
  float valorTotal;
  statusPedido status;
} Pedido;
