#ifndef POLONESA_H
#define POLONESA_H

#include "fila.h"
#include "basics.h"

// Etapa 2: Converte infixa para posfixa [cite: 58]
// Retorna 'true' em sucesso, 'false' se expressão for malformada [cite: 28]
boolean converter_infixa_para_posfixa(Fila *filaEntrada, Fila *filaSaida);

// Etapa 3: Calcula o resultado da expressão posfixa 
// Retorna 'true' em sucesso, 'false' se malformada (div/0, etc) [cite: 387]
boolean calcular_posfixa(Fila *filaPosfixa, double *resultado);

// Função auxiliar para verificar se um token é número
boolean is_numero(const char *token);

#endif