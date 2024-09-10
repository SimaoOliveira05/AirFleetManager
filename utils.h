#ifndef utilitarios
#define utilitarios

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *abrir_ficheiro(const char *filename, const char *mode);

void fechar_ficheiro(FILE *file);


#endif