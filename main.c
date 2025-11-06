#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include "menu.h"

int main() {
    setlocale(LC_ALL, "PORTUGUESE");
    SetConsoleOutputCP (28591); // leitura da tabela Latina (escrita) 
    SetConsoleCP(28591); // Acentuação para funções (leitura) funções na bib windows

    menu();
    
    return 0;
}
