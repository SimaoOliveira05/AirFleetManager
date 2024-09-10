#include "utils.h"

/*Funções auxiliares para abrir e fechar ficheiros*/

FILE *abrir_ficheiro(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (!file) { // Não encontrou nenhum ficheiro com esse nome
        printf("Erro ao abrir o ficheiro\n");
        return NULL;
    }
    return file;
}

void fechar_ficheiro(FILE *file) {
    fclose(file);
}
