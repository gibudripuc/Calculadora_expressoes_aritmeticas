#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fila.h"
#include "utils.h" // Funções de validação

#define MAX_EXPRESSAO 100

int ler_expressao(char *expressao);
int remover_espacos(char *dest, const char *orig);
int quebrar_em_tokens(const char *expr, Fila *filaEntrada);
void mostrar_fila(Fila *fila);

int main() {
    char expressao[MAX_EXPRESSAO];
    char semEspacos[MAX_EXPRESSAO];
    unsigned char erro;

    do {
        erro = 0;

        if (ler_expressao(expressao)) continue;

        if (remover_espacos(semEspacos, expressao)) {
            erro = 1;
            continue;
        }

        if (strlen(semEspacos) == 0) {
            printf("Erro: expressao vazia!\n\n");
            erro = 1;
            continue;
        }

        Fila filaEntrada;
        if (!nova_fila(&filaEntrada, MAX_EXPRESSAO)) {
            printf("Erro ao criar fila!\n");
            return 1;
        }

        if (quebrar_em_tokens(semEspacos, &filaEntrada)) {
            erro = 1;
            free_fila(&filaEntrada);
            continue;
        }

        printf("\nFila de entrada:\n");
        mostrar_fila(&filaEntrada);

        free_fila(&filaEntrada);

    } while (erro);

    return 0;
}
