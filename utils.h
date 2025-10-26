//Arquivo que declara as funções auxiliares que você vai usar na main.
#ifndef UTILS_H
#define UTILS_H

#define MAX_EXPRESSAO 100

#include "fila.h"

// Protótipos das funções auxiliares
int ler_expressao(char *expressao);
int remover_espacos(char *dest, const char *orig);
int quebrar_em_tokens(const char *expr, Fila *filaEntrada);
void mostrar_fila(Fila *fila);

#endif
