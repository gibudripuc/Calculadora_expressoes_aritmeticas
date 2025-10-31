#ifndef PILHA_RES_H
#define PILHA_RES_H

#include "basics.h"

typedef double ElementoDePilhaRes; // Tipo para resultados numéricos 

typedef struct {
    ElementoDePilhaRes *vetor;
    unsigned int capacidade;
    int topo; 
} PilhaRes;

bool nova_pilha_res(PilhaRes *p, unsigned int capacidade);
bool empilhe_res(PilhaRes *p, ElementoDePilhaRes e);
bool desempilhe_res(PilhaRes *p, ElementoDePilhaRes *e);
bool pilha_res_vazia(PilhaRes p);
// Função para verificar a qtd de elementos no final
unsigned int pilha_res_qtd(PilhaRes p); 
bool free_pilha_res(PilhaRes *p);

#endif