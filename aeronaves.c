#include "aeronaves.h"
#include "utils.h"


aeronave aeronaves[500]; // nunca irão existir mais do que 500 aeronaves por isso limitamos o tamanho para 500
int total_aeronaves = 0; //Esta variável serve para saber quantas aeronaves há no sistema

void importar_aeronaves(const char *filename) {
//Importa o txt de aeronaves
    
    FILE *file = abrir_ficheiro(filename, "r");
    if (!file){
        printf("Esse ficheiro não se encontra na diretoria.\n\n\n");
        return;
    }

    while (fscanf(file, "%d %d %s %d\n",
                  &aeronaves[total_aeronaves].numero_cauda,
                  &aeronaves[total_aeronaves].esquadra,
                  aeronaves[total_aeronaves].fabricante_Modelo,
                  &aeronaves[total_aeronaves].horas_inicial) != EOF) {
        total_aeronaves++;
    }

    fechar_ficheiro(file);

    printf("Ficheiro importado com sucesso!\n\n\n");
}


void listaTodasAeronaves() {
//Lista todas as aeronaves
    for (int i = 0; i < total_aeronaves; i++) {
        printf("Número de Cauda: %d\n", aeronaves[i].numero_cauda);
        printf("Esquadra: %d\n", aeronaves[i].esquadra);
        printf("Fabricante e Modelo: %s\n", aeronaves[i].fabricante_Modelo);
        printf("Horas Iniciais: %d\n\n\n", aeronaves[i].horas_inicial);
    }
}


void listaAeronavesEsquadra (int esquadra){
//Lista todas as aeronaves de uma determinada esquadra
    int flag = 0;
    for (int i = 0; i < total_aeronaves; i++){

        if (aeronaves[i].esquadra == esquadra){
            if (flag == 0)
                printf("A esquadra %d contêm as seguintes aeronaves\n\n",esquadra);
            flag = 1;
            printf("Número de Cauda: %d\n", aeronaves[i].numero_cauda);
            printf("Esquadra: %d\n", aeronaves[i].esquadra);
            printf("Fabricante e Modelo: %s\n", aeronaves[i].fabricante_Modelo);
            printf("Horas Inicias: %d\n\n\n", aeronaves[i].horas_inicial);
        }
    }
    if (flag == 0)
        printf("Esta esquadra não possui qualquer aeronave resgistada.\n\n\n");
}


void exportar_todas_aeronaves(const char *filename) {
//Exporta a lista de todas as aeronaves para um ficheiro dado pelo utilizador
    FILE *file = abrir_ficheiro(filename, "w");
    for (int i = 0; i < total_aeronaves; i++) {
        fprintf(file, "%d %d %s %d\n",
                aeronaves[i].numero_cauda,
                aeronaves[i].esquadra,
                aeronaves[i].fabricante_Modelo,
                aeronaves[i].horas_inicial);
    }

    fechar_ficheiro(file);
    printf("Ficheiro Exportado com sucesso para %s!\n\n\n",filename);
}

void exportar_aeronaves_esquadra(const char *filename,int esquadra){
//Exporta a lista de todas as aeronaves de uma determinada esquadra 

    FILE *file = abrir_ficheiro(filename, "w");

    fprintf(file,"A esquadra nº %d contêm as seguintes aeronaves\n\n",esquadra);

    for (int i = 0; i < total_aeronaves; i++) {
        if (aeronaves[i].esquadra == esquadra)
            fprintf(file, "%d %s %d\n",
                aeronaves[i].numero_cauda,
                aeronaves[i].fabricante_Modelo,
                aeronaves[i].horas_inicial);
    }
    fechar_ficheiro(file);
    printf("Ficheiro Exportado com sucesso para %s!\n\n\n",filename);
}

