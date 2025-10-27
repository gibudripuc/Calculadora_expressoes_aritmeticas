#include "pilha.h"
#include <stdlib.h>

// Cria uma nova pilha vazia
boolean nova_pilha(Pilha* p, unsigned int capacidade) {
    if (capacidade == 0) return false;

    p->vetor = (ElementoDePilha*)malloc(capacidade * sizeof(ElementoDePilha));
    if (!p->vetor) return false;

    p->capacidade = capacidade;
    p->topo = -1; // -1 indica pilha vazia
    return true;
}

// Adiciona (empilha) um elemento no topo
boolean empilhe(Pilha* p, ElementoDePilha e) {
    if (p->topo + 1 == p->capacidade) return false; // Pilha cheia

    p->topo++;
    p->vetor[p->topo] = e;
    return true;
}

// Remove (desempilha) um elemento do topo
boolean desempilhe(Pilha* p, ElementoDePilha* e) {
    if (p->topo == -1) return false; // Pilha vazia

    *e = p->vetor[p->topo];
    p->topo--;
    return true;
}

// Apenas consulta o elemento do topo, sem remover
boolean topo(Pilha p, ElementoDePilha* e) {
    if (p.topo == -1) return false; // Pilha vazia
    
    *e = p.vetor[p.topo];
    return true;
}

// Verifica se a pilha está vazia
boolean pilha_vazia(Pilha p) {
    return p.topo == -1;
}

// Libera a memória da pilha e de todos os tokens (strings) nela
boolean free_pilha(Pilha* p) {
    if (p->vetor == NULL) return false;

    // Libera cada string (token) que ainda está na pilha
    while (!pilha_vazia(*p)) {
        ElementoDePilha e;
        desempilhe(p, &e);
        free(e); // Libera a string
    }

    // Libera o vetor da pilha
    free(p->vetor);
    p->vetor = NULL;
    return true;
}