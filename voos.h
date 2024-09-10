#ifndef Voos
#define Voos


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char data[11];
    int numero_cauda;
    int duracao; // duração em minutos
} Voo;

extern Voo voos[1000];
extern int total_voos;


void importar_voos(const char *filename);

void listaTodosVoos ();

void listaVoosCauda (int nCauda);

int comparaDatas (char* datamenor, char* datamaior, char* data);

void listaVoosData (char* datamenor, char* datamaior);

void exportar_todos_voos(const char *filename);

void exportar_listaVoosCauda (const char *filename,int nCauda);

void exportar_listaVoosData (char* datamenor, char* datamaior,const char *filename);


#endif