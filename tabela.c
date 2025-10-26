#include "basics.h"

static boolean tabela[7][7] = {
    {false, false, false, false, false, false, true},   // ( no topo da pilha
    {false, false, true,  true,  true,  true,  true},   // ^ no topo da pilha
    {false, false, true,  true,  true,  true,  true},   // * no topo da pilha
    {false, false, true,  true,  true,  true,  true},   // / no topo da pilha
    {false, false, false, false, true,  true,  true},   // + no topo da pilha
    {false, false, false, false, true,  true,  true},   // - no topo da pilha
    {false, false, false, false, false, false, false}   // ) no topo da pilha
};
