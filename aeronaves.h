#ifndef Aeronaves
#define Aeronaves

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aeronave{
    int numero_cauda;
    int esquadra;
    char fabricante_Modelo[50];
    int horas_inicial;
} aeronave;

extern aeronave aeronaves[500];
extern int total_aeronaves;

void importar_aeronaves(const char *filename);

void listaTodasAeronaves();

void listaAeronavesEsquadra (int esquadra);

void exportar_todas_aeronaves(const char *filename);

void exportar_aeronaves_esquadra(const char *filename,int esquadra);




#endif