#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

int main() {
    setlocale(LC_ALL, "PORTUGUESE");
    SetConsoleOutputCP (28591); // leitura da tabela Latina (escrita) 
    SetConsoleCP(28591); // Acentuação para funções (leitura) funções na bib windows

    
    
    return 0;
}