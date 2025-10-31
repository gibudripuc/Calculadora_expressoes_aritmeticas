#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fila.h"
#include "utils.h"
#include "polonesa.h" // Inclui as funções de conversão e cálculo

int main() {
    char expressao[MAX_EXPRESSAO];
    char semEspacos[MAX_EXPRESSAO];

    printf("=== Calculadora de Expressoes Aritmeticas ===\n");
    printf("Digite 'fim' para sair.\n\n");

    while (1) { // Loop para permitir múltiplos cálculos
        
        if (ler_expressao(expressao)) continue;
        if (strcmp(expressao, "fim") == 0) break; // Condição de saída

        if (remover_espacos(semEspacos, expressao)) {
            continue; // Erro já foi impresso
        }

        if (strlen(semEspacos) == 0) {
            printf("Erro: expressao vazia!\n\n");
            continue;
        }

        //Etapa 1
        Fila filaEntrada;
        if (!nova_fila(&filaEntrada, MAX_EXPRESSAO)) {
            printf("Erro ao criar fila de entrada!\n");
            return 1;
        }

        if (quebrar_em_tokens(semEspacos, &filaEntrada)) { // [cite: 50]
            free_fila(&filaEntrada); // Libera o que foi alocado até o erro
            continue; // Erro já foi impresso
        }

        //Etapa 2: Conversão Infixa -> Pós-fixa
        Fila filaSaida; // Fila para a notação pós-fixa 
        if (!nova_fila(&filaSaida, MAX_EXPRESSAO)) {
            printf("Erro ao criar fila de saida!\n");
            free_fila(&filaEntrada);
            return 1;
        }

        // A filaEntrada é esvaziada pela conversão
        if (!converter_infixa_para_posfixa(&filaEntrada, &filaSaida)) {
            // Erro de conversão (ex: parênteses desbalanceados)
            // filaEntrada já é liberada internamente pela função converter_infixa_para_posfixa
            free_fila(&filaSaida);   // Libera o que foi gerado até o erro
            continue;
        }

        //Etapa 3: Cálculo da Expressão Pós-fixa
        double resultado;
        
        // A filaSaida é esvaziada pelo cálculo
        if (!calcular_posfixa(&filaSaida, &resultado)) {
            // Erro de cálculo
            // filaSaida já é liberada internamente pela função calcular_posfixa
            continue;
        }

        //Sucesso
        printf("Entrada: %s\n", expressao);
        // %g formata o double de forma inteligente (ex: 23 em vez de 23.000)
        printf("Saida: %g\n\n", resultado);

        // As filas já foram liberadas pelas funções de conversão e cálculo
        // free_fila(&filaEntrada); 
        // free_fila(&filaSaida); 
    }

    printf("Calculadora encerrada.\n");
    return 0;
}
