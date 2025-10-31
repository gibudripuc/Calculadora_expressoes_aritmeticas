#include "pilha_res.h"
#include <stdlib.h>

bool nova_pilha_res(PilhaRes* p, unsigned int capacidade) {
    if (capacidade == 0) return false;

    p->vetor = (ElementoDePilhaRes*)malloc(capacidade * sizeof(ElementoDePilhaRes));
    if (!p->vetor) return false;

    p->capacidade = capacidade;
    p->topo = -1;
    return true;
}

bool empilhe_res(PilhaRes* p, ElementoDePilhaRes e) {
    if (p->topo + 1 == p->capacidade) return false; // Cheia
    
    p->topo++;
    p->vetor[p->topo] = e;
    return true;
}

bool desempilhe_res(PilhaRes* p, ElementoDePilhaRes* e) {
    if (p->topo == -1) return false; // Vazia
    
    *e = p->vetor[p->topo];
    p->topo--;
    return true;
}

bool pilha_res_vazia(PilhaRes p) {
    return p.topo == -1;
}

// Retorna a quantidade de elementos na pilha
unsigned int pilha_res_qtd(PilhaRes p) {
    return p.topo + 1;
}

// Libera a memória da pilha (elementos são doubles, não precisam de free individual)
bool free_pilha_res(PilhaRes* p) {
    if (p->vetor == NULL) return false;
    
    free(p->vetor);
    p->vetor = NULL;
    return true;
}