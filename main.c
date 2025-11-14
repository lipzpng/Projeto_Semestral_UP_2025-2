#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include "funcoes/menu.h"

int main() {
    setlocale(LC_ALL, "PORTUGUESE");
    SetConsoleOutputCP (28591); // leitura da tabela Latina (escrita) 
    SetConsoleCP(28591); // Acentua��o para fun��es (leitura) fun��es na bib windows

    menu();
    
    return 0;
}
