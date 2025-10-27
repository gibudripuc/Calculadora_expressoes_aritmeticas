#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h> // Para a função pow() da exponenciação [cite: 35]

#include "polonesa.h"
#include "pilha.h"       // Pilha de char* (operadores) 
#include "pilha_res.h"   // Pilha de double (resultados) 
#include "fila.h"
#include "tabela.h"      // Tabela de precedência [cite: 45]

// Função auxiliar para verificar se um token é um número [cite: 61]
boolean is_numero(const char *token) {
    if (!token) return false;
    // Um token é número se começa com um dígito ou ponto decimal
    return isdigit((unsigned char)token[0]) || token[0] == '.';
}

/**
 * ETAPA 2: Conversão de Infixa para Pós-fixa [cite: 58]
 * Consome a filaEntrada e preenche a filaSaida.
 */
boolean converter_infixa_para_posfixa(Fila *filaEntrada, Fila *filaSaida) {
    Pilha pilhaOps; // Pilha de Operadores 
    if (!nova_pilha(&pilhaOps, filaEntrada->capacidade)) return false;

    while (!fila_vazia(*filaEntrada)) {
        char *token;
        desenfileire(filaEntrada, &token);

        if (is_numero(token)) {
            // Regra: Números vão direto para a fila de saída [cite: 61]
            enfileire(filaSaida, token);
        } 
        else if (token[0] == '(') {
            // Regra: Parêntese aberto é empilhado [cite: 62, 64]
            empilhe(&pilhaOps, token);
        } 
        else if (token[0] == ')') {
            // Regra: Parêntese fechado [cite: 63]
            boolean achouParenteseAberto = false;
            while (!pilha_vazia(pilhaOps)) {
                char *opTopo;
                topo(pilhaOps, &opTopo);

                if (opTopo[0] == '(') {
                    // Achou o '('. Remove da pilha e descarta [cite: 66, 228]
                    desempilhe(&pilhaOps, &opTopo);
                    free(opTopo); // Descarta o '('
                    achouParenteseAberto = true;
                    break;
                } else {
                    // Transfere o operador da pilha para a fila de saída [cite: 65, 213]
                    desempilhe(&pilhaOps, &opTopo);
                    enfileire(filaSaida, opTopo);
                }
            }
            
            if (!achouParenteseAberto) {
                // Se não achou '(', a expressão está malformada [cite: 28]
                printf("Erro: Parenteses desbalanceados (faltando '(').\n\n");
                free_pilha(&pilhaOps);
                free(token); // Descarta o ')'
                return false; 
            }
            free(token); // Descarta o ')' [cite: 228]
        } 
        else { 
            // É um operador: + - * / ^ [cite: 67]
            int indiceEntrada = get_indice_operador(token[0]);
            
            // Desempilha operadores de maior ou igual precedência [cite: 67, 45]
            while (!pilha_vazia(pilhaOps)) {
                char *opTopo;
                topo(pilhaOps, &opTopo);
                int indiceTopo = get_indice_operador(opTopo[0]);

                if (indiceTopo == -1) break; // '(', por exemplo, não é desempilhado

                // Consulta a tabela[cite: 45]: se T(true), desempilha
                if (tabela[indiceTopo][indiceEntrada] == true) {
                    desempilhe(&pilhaOps, &opTopo);
                    enfileire(filaSaida, opTopo);
                } else {
                    // F(false), para de desempilhar [cite: 107]
                    break;
                }
            }
            // Empilha o operador atual
            empilhe(&pilhaOps, token);
        }
    }

    // Fila de entrada vazia. Esvazia a pilha na fila de saída [cite: 325, 329]
    while (!pilha_vazia(pilhaOps)) {
        char *opTopo;
        desempilhe(&pilhaOps, &opTopo);
        if (opTopo[0] == '(') { // Sobrou '(' na pilha
            printf("Erro: Parenteses desbalanceados (sobrando '(').\n\n");
            free(opTopo);
            free_pilha(&pilhaOps);
            return false; // Expressão malformada [cite: 28]
        }
        enfileire(filaSaida, opTopo); // [cite: 326, 330]
    }

    free_pilha(&pilhaOps); // Libera o vetor da pilha (conteúdo já foi movido)
    return true;
}

/**
 * ETAPA 3: Cálculo da expressão Pós-fixa 
 * Consome a filaPosfixa e retorna o resultado.
 */
boolean calcular_posfixa(Fila *filaPosfixa, double *resultado) {
    PilhaRes pilhaRes; // Pilha de Resultados (armazena doubles) 
    if (!nova_pilha_res(&pilhaRes, filaPosfixa->capacidade)) return false;

    while (!fila_vazia(*filaPosfixa)) {
        char *token;
        desenfileire(filaPosfixa, &token);

        if (is_numero(token)) {
            // Número: converte para double e empilha [cite: 335]
            empilhe_res(&pilhaRes, atof(token));
            free(token); // Libera o token (string)
        } 
        else { // Operador
            double op2, op1, res;

            // Desempilha 2 operandos [cite: 341]
            if (!desempilhe_res(&pilhaRes, &op2)) {
                printf("Erro: Expressao malformada (faltam operandos para '%s').\n\n", token);
                free(token);
                free_pilha_res(&pilhaRes);
                return false; // [cite: 386]
            }
            if (!desempilhe_res(&pilhaRes, &op1)) {
                printf("Erro: Expressao malformada (falta 1 operando para '%s').\n\n", token);
                free(token);
                free_pilha_res(&pilhaRes);
                return false; // [cite: 386]
            }

            // Ordem: "RESPECTIVAMENTE o 4 e o 6... cálculo, 6-4" [cite: 348]
            // Logo, op2=4, op1=6. Cálculo é op1 - op2.
            
            switch (token[0]) {
                case '+': res = op1 + op2; break; // [cite: 367]
                case '-': res = op1 - op2; break; // [cite: 348]
                case '*': res = op1 * op2; break; // [cite: 341]
                case '/':
                    if (op2 == 0.0) {
                        printf("Erro: Divisao por zero!\n\n"); // [cite: 387]
                        free(token);
                        free_pilha_res(&pilhaRes);
                        return false;
                    }
                    res = op1 / op2; break; // [cite: 365]
                case '^': res = pow(op1, op2); break; // [cite: 354, 357]
            }
            
            empilhe_res(&pilhaRes, res); // Empilha o resultado [cite: 344]
            free(token); // Libera o token (string)
        }
    }

    // No final, a pilha deve ter exatamente 1 elemento [cite: 385]
    if (pilha_res_qtd(pilhaRes) != 1) {
        printf("Erro: Expressao malformada (operandos em excesso).\n\n");
        free_pilha_res(&pilhaRes);
        return false; // [cite: 386]
    }

    desempilhe_res(&pilhaRes, resultado); // Pega o resultado final
    free_pilha_res(&pilhaRes); // Libera o vetor da pilha
    return true; 
}