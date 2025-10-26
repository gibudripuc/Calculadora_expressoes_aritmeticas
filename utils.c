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
    dest[0] = '\0';
    for (int i = 0; orig[i] != '\0'; i++) {
        if (isspace((unsigned char)orig[i])) {
            if (i > 0 && orig[i + 1] != '\0' &&
                isdigit((unsigned char)orig[i - 1]) &&
                isdigit((unsigned char)orig[i + 1])) {
                printf("Erro: numeros com mais de um digito escritos com espacos!\n\n");
                return 1;
            }
            continue;
        }
        strncat(dest, &orig[i], 1);
    }
    return 0;
}

int quebrar_em_tokens(const char *expr, Fila *filaEntrada) {
    int pos = 0, contadorParenteses = 0;
    char ultimoToken[50] = "";
    unsigned char erro = 0;

    while (expr[pos] != '\0') {
        char *tok = NULL;

        if (strchr("+-*/^()", expr[pos])) {
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
