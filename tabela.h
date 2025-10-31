#ifndef TABELA_H
#define TABELA_H

#include "basics.h"

// Matriz de precedência
// Linhas: Topo da Pilha
// Colunas: Fila de Entrada
// Índices: 0=(, 1=^, 2=*, 3=/, 4=+, 5=-, 6=)
extern bool tabela[7][7];

/**
 * Função para mapear token de operador para índice da tabela
 * ( = 0
 * ^ = 1
 * * = 2
 * / = 3
 * + = 4
 * - = 5
 * ) = 6
 */
int get_indice_operador(char op);

#endif