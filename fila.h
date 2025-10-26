#ifndef FILA_H
#define FILA_H

#include <stdlib.h>
#include "basics.h"

typedef char* ElementoDeFila;

typedef struct {
    ElementoDeFila *vetor;
    unsigned int capacidade;
    unsigned int qtd_atual;
    unsigned int inicio;
    unsigned int final;
} Fila;

boolean nova_fila(Fila *f, unsigned int capacidade);
boolean enfileire(Fila *f, ElementoDeFila e);
boolean desenfileire(Fila *f, ElementoDeFila *e); //Quando quer usar o valor retirado
boolean fila_vazia (Fila f);
boolean free_fila(Fila *f);

#endif
// Fila parada com vetor dinâmico
