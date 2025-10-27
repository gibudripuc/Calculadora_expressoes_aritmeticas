#ifndef PILHA_RES_H
#define PILHA_RES_H

#include "basics.h"

typedef double ElementoDePilhaRes; // Tipo para resultados numéricos 

typedef struct {
    ElementoDePilhaRes *vetor;
    unsigned int capacidade;
    int topo; 
} PilhaRes;

boolean nova_pilha_res(PilhaRes *p, unsigned int capacidade);
boolean empilhe_res(PilhaRes *p, ElementoDePilhaRes e);
boolean desempilhe_res(PilhaRes *p, ElementoDePilhaRes *e);
boolean pilha_res_vazia(PilhaRes p);
// Função para verificar a qtd de elementos no final [cite: 385]
unsigned int pilha_res_qtd(PilhaRes p); 
boolean free_pilha_res(PilhaRes *p);

#endif