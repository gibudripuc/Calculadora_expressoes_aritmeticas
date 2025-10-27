#include "tabela.h" // Inclui o header
#include "basics.h"

// 'static' REMOVIDO para que a tabela seja visível externamente [cite: 45]
boolean tabela[7][7] = {
    //Colunas (Fila de Entrada):
    //(    ^      * /      +      -      )
    {false, false, false, false, false, false, true},   // ( no topo da pilha
    {false, false, true,  true,  true,  true,  true},   // ^ no topo da pilha
    {false, false, true,  true,  true,  true,  true},   // * no topo da pilha
    {false, false, true,  true,  true,  true,  true},   // / no topo da pilha
    {false, false, false, false, true,  true,  true},   // + no topo da pilha
    {false, false, false, false, true,  true,  true},   // - no topo da pilha
    {false, false, false, false, false, false, false}   // ) no topo da pilha (linha de segurança)
};

// Mapeia o caractere do operador para seu índice na tabela
int get_indice_operador(char op) {
    switch (op) {
        case '(': return 0;
        case '^': return 1;
        case '*': return 2;
        case '/': return 3;
        case '+': return 4;
        case '-': return 5;
        case ')': return 6;
        default:  return -1; // Não é um operador
    }
}