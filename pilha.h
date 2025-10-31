#ifndef PILHA_H
#define PILHA_H

#include "basics.h"

// ElementoDePilha é char*, consistente com ElementoDeFila 
typedef char* ElementoDePilha; 

typedef struct {
    ElementoDePilha *vetor;
    unsigned int capacidade;
    int topo; //-1 indica pilha vazia
} Pilha;

// Protótipos das funções da pilha
bool nova_pilha(Pilha *p, unsigned int capacidade);
bool empilhe(Pilha *p, ElementoDePilha e);
bool desempilhe(Pilha *p, ElementoDePilha *e); // Retorna o valor
bool topo(Pilha p, ElementoDePilha *e); // Apenas consulta o topo
bool pilha_vazia(Pilha p);
bool free_pilha(Pilha *p); // Libera a pilha e seus conteúdos

#endif