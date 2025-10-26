#include <stdlib.h>
#include <string.h>
#include "fila.h"

// Cria uma fila com capacidade especificada
boolean nova_fila(Fila* f, unsigned int capacidade) {
    if (capacidade == 0) return false;

    f->vetor = (ElementoDeFila*)malloc(capacidade * sizeof(ElementoDeFila));
    if (!f->vetor) return false;

    f->capacidade = capacidade;
    f->qtd_atual = 0;
    f->inicio = 0;
    f->final = 0;

    return true;
}

// Adiciona elemento ao final da fila
boolean enfileire(Fila* f, ElementoDeFila e)
{
    if (f->qtd_atual==f->capacidade) return false;

    f->vetor[f->final]=e;
    f->qtd_atual++;

    if (f->final==f->capacidade-1)
        f->final=0;
    else
        f->final++;
    
    return true;
}

// Remove elemento do início da fila
boolean desenfileire(Fila* f, ElementoDeFila* e)
{
    if (f->qtd_atual == 0) return false;

    *e = f->vetor[f->inicio];  // retorna o elemento removido

    if (f->inicio == f->capacidade - 1)
        f->inicio = 0;
    else
        f->inicio++;

    f->qtd_atual--;

    return true;
}

boolean fila_vazia (Fila f)
{
    
    if (f.qtd_atual==0)
        return true;
    else
        return false;
    
    return f.qtd_atual==0;
}

// Libera memória da fila
boolean free_fila (Fila* f)
{
    if (f->vetor==NULL) return false;

    for (int i=0; i<f->qtd_atual; i++)
    {
        f->qtd_atual--;
        free(f->vetor[f->qtd_atual]);
    }

    free(f->vetor);
    f->vetor=NULL;

    return true;
}