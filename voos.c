#include "voos.h"
#include "utils.h"

Voo voos[1000];
int total_voos = 0;


void importar_voos(const char *filename) {
//Importa o txt de voos
    FILE *file = abrir_ficheiro(filename, "r");
    if (!file){
        printf("Esse ficheiro não se encontra na diretoria.\n\n\n");
        return;
    }

    while (fscanf(file, "%10s\n%d\n%d\n= = = = =\n",
                  voos[total_voos].data,
                  &voos[total_voos].numero_cauda,
                  &voos[total_voos].duracao) != EOF) {
        total_voos++;
    }

    fechar_ficheiro(file);
    printf("Ficheiro importado com sucesso!\n\n\n");
}


void listaTodosVoos () {
//Faz a lista de todos os Voos
    for (int i = 0; i < total_voos; i++){
        printf("Data do voo: %s\n", voos[i].data);
        printf("Número de Cauda: %d\n", voos[i].numero_cauda);
        printf("Duração do voo: %d minutos\n\n\n", voos[i].duracao);
    }
}


void listaVoosCauda (int nCauda) {
//Faz a lista de todos os Voos de um numero de cauda dado pelo utilizador
    printf("\n");
    int flag = 0;
    int count = 0;
    for (int i = 0; i < total_voos; i++){
        if (voos[i].numero_cauda == nCauda){
            flag = 1;
            printf("Data de voo: %s\n",voos[i].data);
            printf("Duração de voo: %d minutos\n\n\n",voos[i].duracao);
        }
    }
    if (flag == 0)
        printf("Esta aeronave não possui qualquer voo registado.\n\n\n");
}


int comparaDatas (char* datamenor, char* datamaior, char* data){
/* Função auxiliar, que dado uma data minima, data maxima e uma data, vê se essa mesma data está
    entre esses dois limites*/
    if (strcmp (datamenor,data) <= 0 && strcmp (datamaior,data) >= 0)
        return 1;

    else 
        return 0;
}


void listaVoosData (char* datamenor, char* datamaior){
//Lista todos os voos entre 2 datas dadas pelo utilizador
    int flag = 0;
    for (int i = 0; i < total_voos; i++){
        if (comparaDatas (datamenor, datamaior, voos[i].data) == 1){
            flag = 1;
            printf("Data do voo: %s\n", voos[i].data);
            printf("Número de Cauda: %d\n", voos[i].numero_cauda);
            printf("Duração do voo: %d minutos\n\n\n", voos[i].duracao);
        }
    }
    if (flag == 0)
        printf("Não existe nenhum voo entre essas datas na nossa base de dados.\n\n\n");
}


void exportar_todos_voos(const char *filename) {
//Exporta a lista de todos os voos para um ficheiro de texto dado pelo utilizador
    FILE *file = abrir_ficheiro(filename, "w");
    
    for (int i = 0; i < total_voos; i++){
        fprintf(file, "%s\n%d\n%d\n",
                voos[i].data,
                voos[i].numero_cauda,
                voos[i].duracao);
        fprintf(file, "= = = = =\n");
    }
    fechar_ficheiro(file);
    printf("Ficheiro Exportado com sucesso para %s!\n\n\n",filename);
}

void exportar_listaVoosCauda (const char *filename,int nCauda) {
//Exporta a lista de todos os voos de um determinado numero de cauda para um ficheiro de texto dado pelo utilizador
    FILE *file = abrir_ficheiro(filename, "w");
    fprintf(file,"A aeronave com o nº de cauda %d possui os seguintes voos registrados:\n\n",nCauda);
    
    for (int i = 0; i < total_voos; i++){
        if (voos[i].numero_cauda == nCauda){
            fprintf(file,"Data de voo: %s\n",voos[i].data);
            fprintf(file,"Duração de voo: %d minutos\n\n",voos[i].duracao);
        }
    }
    fechar_ficheiro(file);
    printf("Ficheiro Exportado com sucesso para %s!\n\n\n",filename);
}


void exportar_listaVoosData (char* datamenor, char* datamaior,const char *filename){
//Exporta a lista de todos os voos entre um determinado intervalo de tempo para um ficheiro de texto dado pelo utilizador
    FILE *file = abrir_ficheiro(filename, "w");
    fprintf(file,"Os voos registrados entre %s e %s são:\n\n",datamenor,datamaior);

    for (int i = 0; i < total_voos; i++){
        if (comparaDatas (datamenor, datamaior, voos[i].data) == 1){
            fprintf(file,"Data do voo: %s\n", voos[i].data);
            fprintf(file,"Número de Cauda: %d\n", voos[i].numero_cauda);
            fprintf(file,"Duração do voo: %d minutos\n\n", voos[i].duracao);
        }
    }
    fechar_ficheiro(file);
    printf("Ficheiro Exportado com sucesso para %s!\n\n\n",filename);
}