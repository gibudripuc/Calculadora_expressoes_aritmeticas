#include <stdlib.h>
#include <string.h>
#include "fila.h"

// Cria uma fila
bool nova_fila(Fila* f, unsigned int capacidade) {
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
bool enfileire(Fila* f, ElementoDeFila e)
{
    if (f->qtd_atual==f->capacidade) return false;

    f->vetor[f->final]=strdup(e); // Duplicar a string de entrada
    if (f->vetor[f->final] == NULL) return false; // Erro na alocação
    f->qtd_atual++;

    if (f->final==f->capacidade-1)
        f->final=0;
    else
        f->final++;
    
    return true;
}

// Remove elemento do início da fila
bool desenfileire(Fila* f, ElementoDeFila* e)
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

bool fila_vazia (Fila f)
{
    return f.qtd_atual == 0;
}

// Libera memória da fila
bool free_fila (Fila* f)
{
    if (f->vetor==NULL) return false;

    // Libera cada elemento restante na fila
    while (!fila_vazia(*f))
    {
        ElementoDeFila e;
        desenfileire(f, &e); // Remove o elemento
        free(e);             // Libera a string
    }

    // Libera o vetor da fila
    free(f->vetor);
    f->vetor=NULL;
    f->capacidade = 0;
    f->qtd_atual = 0;
    f->inicio = 0;
    f->final = 0;

    return true;
}