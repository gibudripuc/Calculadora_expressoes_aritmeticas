#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

int ler_expressao(char *expressao) {
    printf("Digite uma expressao aritmetica: ");
    fgets(expressao, MAX_EXPRESSAO, stdin);
    expressao[strcspn(expressao, "\n")] = '\0';
    return 0;
}

int remover_espacos(char *dest, const char *orig) {
    dest[0] = '\0'; //destino
    int j = 0; // Índice para o array de destino

    for (int i = 0; orig[i] != '\0'; i++) {
        if (!isspace((unsigned char)orig[i])) {
            dest[j++] = orig[i];
        } else { // Current character is a space
            // Look ahead to find the next non-space character
            int k = i + 1;
            while (orig[k] != '\0' && isspace((unsigned char)orig[k])) {
                k++;
            }
            // orig[k] is now the first non-space character after the current block of spaces, or '\0'

            // If we have a non-space char before the space, and a non-space char after the spaces
            // And if both are digits, then it's an error.
            if (j > 0 && orig[k] != '\0') {
                char prev_char_in_dest = dest[j-1]; // Last char added to dest (which was non-space)
                char next_char_after_spaces = orig[k];

                if (isdigit((unsigned char)prev_char_in_dest) && isdigit((unsigned char)next_char_after_spaces)) {
                    printf("Erro: expressao invalida pois contem espacos entre numeros sem operadores!\n\n");
                    return 1;
                }
            }
            // Skip all spaces (including the current one)
            i = k - 1; // The loop will increment i, so k-1 ensures we process orig[k] next iteration
        }
    }
    dest[j] = '\0'; // Termina a string resultante
    return 0;
}

int quebrar_em_tokens(const char *expr, Fila *filaEntrada) {
    int pos = 0, contadorParenteses = 0;
    char ultimoToken[50] = "";
    unsigned char erro = 0;

    while (expr[pos] != '\0') {
        char *tok = NULL;

        // Detectar números negativos ou o sinal de menos unário
        if (expr[pos] == '-' && (pos == 0 || expr[pos-1] == '(' || strchr("+-*/^", expr[pos-1]))) {
            int start = pos;
            pos++; // Pula o '-'
            int ponto = 0;
            while (isdigit((unsigned char)expr[pos]) || (expr[pos] == '.' && !ponto)) {
                if (expr[pos] == '.') ponto = 1;
                pos++;
            }
            int len = pos - start;
            tok = malloc(len + 1);
            strncpy(tok, expr + start, len);
            tok[len] = '\0';
        }
        else if (strchr("+-*/^()", expr[pos])) {
            tok = malloc(2);
            tok[0] = expr[pos];
            tok[1] = '\0';

            if (tok[0] == '(') contadorParenteses++;
            else if (tok[0] == ')') {
                contadorParenteses--;
                if (contadorParenteses < 0) {
                    printf("Erro: parenteses desbalanceados!\n\n");
                    erro = 1;
                    free(tok);
                    break;
                }
            }

            pos++;
        }
        else if (isdigit((unsigned char)expr[pos]) || expr[pos] == '.') {
            int start = pos;
            int ponto = 0;
            while (isdigit((unsigned char)expr[pos]) || (expr[pos] == '.' && !ponto)) {
                if (expr[pos] == '.') ponto = 1;
                pos++;
            }
            int len = pos - start;
            tok = malloc(len + 1);
            strncpy(tok, expr + start, len);
            tok[len] = '\0';

            if (ultimoToken[0] == '/' && atof(tok) == 0.0) {
                printf("Erro: divisao por zero!\n\n");
                erro = 1;
                free(tok);
                break;
            }
        }
        else {
            printf("Erro: simbolo invalido '%c'!\n\n", expr[pos]);
            erro = 1;
            break;
        }

        if (tok) {
            enfileire(filaEntrada, tok);
            strncpy(ultimoToken, tok, sizeof(ultimoToken));
            free(tok); // Liberar a memória alocada para 'tok'
        }
    }

    if (contadorParenteses != 0) {
        printf("Erro: parenteses desbalanceados!\n\n");
        erro = 1;
    }

    return erro;
}

void mostrar_fila(Fila *fila) {
    while (!fila_vazia(*fila)) {
        char *item;
        desenfileire(fila, &item);
        printf("%s\n", item);
        free(item);
    }
}
