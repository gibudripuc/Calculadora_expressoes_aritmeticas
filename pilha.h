#ifndef PILHA_H
#define PILHA_H

#include "basics.h"

// ElementoDePilha é char*, consistente com ElementoDeFila 
typedef char* ElementoDePilha; 

typedef struct {
    ElementoDePilha *vetor;
    unsigned int capacidade;
    int topo; // Usaremos -1 para indicar pilha vazia
} Pilha;

// Protótipos das funções da pilha
boolean nova_pilha(Pilha *p, unsigned int capacidade);
boolean empilhe(Pilha *p, ElementoDePilha e);
boolean desempilhe(Pilha *p, ElementoDePilha *e); // Retorna o valor
boolean topo(Pilha p, ElementoDePilha *e); // Apenas consulta o topo
boolean pilha_vazia(Pilha p);
boolean free_pilha(Pilha *p); // Libera a pilha e seus conteúdos

#endif