#ifndef estatisticas
#define estatisticas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voos.h"
#include "aeronaves.h"


int compararEsquadra(const void *a, const void *b);

void ordenar_aeronaves_por_esquadra(aeronave porOrdenar[]);

void calculaMaiorHora (aeronave ordenado[]);

void adicionaHoras (aeronave ordenado[]);

void maisHoras ();

int compararHoras(const void *a, const void *b);

void ordenar_aeronaves_por_horas(aeronave porOrdenar[]);

void maioresHoras ();



#endif