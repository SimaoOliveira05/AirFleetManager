#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
FUNÇÕES AUXILIARES PARA ABRIR E FECHAR FICHEIROS
*/

FILE *abrir_ficheiro(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) { // Não encontrou nenhum ficheiro com esse nome
        printf("Erro ao abrir o ficheiro\n");
        return NULL;
    }
    return file;
}

void fechar_ficheiro(FILE *file) {
    fclose(file);
}


/*
FUNÇÕES SOBRE MANUSEAMENTO DE AERONAVES
*/


typedef struct aeronave{
    int numero_cauda;
    int esquadra;
    char fabricante_Modelo[50];
    int horas_inicial;
} aeronave;

aeronave aeronaves[500]; // nunca irão existir mais do que 500 aeronaves por isso limitamos o tamanho para 500
int total_aeronaves = 0; //Esta variável serve para saber quantas aeronaves há no sistema

void importar_aeronaves(const char *filename) {
//Importa o txt de aeronaves
    
    FILE *file = abrir_ficheiro(filename, "r");
    if (file == NULL){
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


/*
FUNÇÕES SOBRE MANUSEAMENTO DE VOOS
*/


typedef struct {
    char data[11];
    int numero_cauda;
    int duracao; // duração em minutos
} Voo;


Voo voos[1000];
int total_voos = 0;


void importar_voos(const char *filename) {
//Importa o txt de voos
    FILE *file = abrir_ficheiro(filename, "r");
    if (file == NULL){
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


/*
FUNÇÕES DE ESTATÍSTICAS
*/

int compararEsquadra(const void *a, const void *b) {
/*qsort ordena uma lista  se lhe dermos a lista o numero de elementos da mesma, o tamanho da struct e uma funçao de comparação
que neste caso é a compararEsquadra
(const void é uma variável genérica)
*/

    aeronave *aeronaveA = (aeronave *)a;
    aeronave *aeronaveB = (aeronave *)b;

    if (aeronaveA->esquadra < aeronaveB->esquadra)
        return -1;
    else if (aeronaveA->esquadra > aeronaveB->esquadra)
        return 1;
    else
        return 0;
}

void ordenar_aeronaves_por_esquadra(aeronave porOrdenar[]) {
//Ordena as aeronaves por ordem crescente de nº de esquadra

    for(int i = 0; i < total_aeronaves; i++) {
        porOrdenar[i] = aeronaves[i];
    }
    qsort(porOrdenar, total_aeronaves, sizeof(aeronave), compararEsquadra);
}

void calculaMaiorHora (aeronave ordenado[]){
/*Dado uma lista de aeronaves ordenada por esquadra, vê qual é a esquadra com mais horas de voo*/
    int countAtual = ordenado[0].horas_inicial;
    int melhorCount = ordenado[0].horas_inicial;
    int melhorEsquadra = ordenado[0].esquadra;

    for (int i = 1; i < total_aeronaves; i++){
        if (ordenado[i].esquadra == ordenado[i-1].esquadra)
            countAtual += ordenado[i].horas_inicial;
        else{
            if (countAtual > melhorCount){
                melhorCount = countAtual;
                melhorEsquadra = ordenado[i-1].esquadra;
            }
            countAtual = ordenado[i].horas_inicial;
        }
    }

    if (countAtual > melhorCount){
        melhorCount = countAtual;
        melhorEsquadra = ordenado[total_aeronaves-1].esquadra;
    }

    printf("A esquadra nº %d tem o maior o maior número de horas de voo com um total de %d horas.\n\n\n",melhorEsquadra,melhorCount);
}

void adicionaHoras (aeronave ordenado[]){
/*Dado uma lista de aeronaves, percorre a lista de voos e adiciona o tempo de voo(arredonadado)
 á respetiva aeronave , efetivamente dando o total de horas que essa mesmo aeronave já esteve no ar*/
    for (int i = 0; i < total_voos; i++){
        for (int j = 0; j < total_aeronaves; j++){
            if (voos[i].numero_cauda == ordenado[j].numero_cauda)
                ordenado[j].horas_inicial += voos[i].duracao / 60;
        }
    }
}


void maisHoras (){
// Verifica qual a esquadra com o maior numero de horas
    if (total_aeronaves == 0){
        printf("Não é possivel realizar essa operação.\n\n\n");
        return;
    }
    aeronave ordenado[total_aeronaves]; // Cria um array auxiliar
    ordenar_aeronaves_por_esquadra(ordenado); // Ordena esse mesmo array por nº de esquadra
    adicionaHoras (ordenado); // Adiciona as respetivas horas de voo ás horas iniciais de cada aeronave
    calculaMaiorHora (ordenado); // Calcula qual a esquadra com o maior nº de horas
}


int compararHoras(const void *a, const void *b) {
// Função auxiliar de comparação de horas para dar como input a qsort 
    aeronave *aeronaveA = (aeronave *)a;
    aeronave *aeronaveB = (aeronave *)b;

    if (aeronaveA->horas_inicial < aeronaveB->horas_inicial)
        return -1;
    else if (aeronaveA->horas_inicial > aeronaveB->horas_inicial)
        return 1;
    else
        return 0;
}

void ordenar_aeronaves_por_horas(aeronave porOrdenar[]){
//Ordena a lista de aeronaves por numero crescente de horas
    for(int i = 0; i < total_aeronaves; i++) {
        porOrdenar[i] = aeronaves[i];
    }
    qsort(porOrdenar, total_aeronaves, sizeof(aeronave), compararHoras);
}

void maioresHoras (){
//Dá as 5 aeronaves com o maior número de horas (que são as ultimas 5 da lista de aeronaves ordenada por hora)
    aeronave ordenado[total_aeronaves];
    ordenar_aeronaves_por_horas(ordenado);
    adicionaHoras (ordenado);
    int count = 1;
    int i;
    printf ("As 5 aeronaves com mais horas de voo são:\n\n");
    for (i = total_aeronaves - 1; i > total_aeronaves - 6 && i >= 0; i--){
        printf("%d - %d com %d horas de voo\n\n",count,ordenado[i].numero_cauda,ordenado[i].horas_inicial);
        count++;
    }
    printf("\n\n");
} 


/*
MAIN
*/

void menu() {

//Menu para facilitar a utilização do programa
    printf("Menu:\n");
    printf("1. Importar dados de aeronaves\n");
    printf("2. Importar dados de voos\n");
    printf("3. Listar todas as aeronaves\n");
    printf("4. Listar todas as aeronaves de uma esquadra\n");
    printf("5. Listar todos os voos\n");
    printf("6. Listar todos os voos de uma aeronave\n");
    printf("7. Listar todos os voos entre duas datas\n");
    printf("8. Mostrar estatísticas\n");
    printf("0. Sair\n");
}

int main() {
    int opcao, esquadra, nCauda;
    char resposta[4];
    char filename[100];
    char data_maior[11],data_menor[11];

    while (1) {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        printf("\n\n");
        switch (opcao) {
            case 1:
                printf("Digite o nome do ficheiro de aeronaves: ");
                scanf("%s", filename);
                importar_aeronaves(filename);
                break;
            
            case 2:
                printf("Digite o nome do ficheiro de voos: ");
                scanf("%s", filename);
                importar_voos(filename);
                break;
            case 3:
                if (total_aeronaves == 0)
                    printf("O nosso sistema não possui qualquer aeronave registada.\n\n\n");
                else{
                    listaTodasAeronaves();
                    printf("Deseja exportar esta lista para um ficheiro?(S/N): ");
                    scanf("%s",resposta);
                    if (strcmp(resposta,"S") == 0){
                        printf("\nIntroduza o nome do ficheiro para o qual deseja exportar: ");
                        scanf("%s",filename);
                        exportar_todas_aeronaves(filename);
                    }
                    else 
                        printf("\n\n\n");
                }
                break;
            case 4:
                printf("Digite o número da esquadra: ");
                scanf("%d", &esquadra);
                listaAeronavesEsquadra(esquadra);
                printf("Deseja exportar esta lista para um ficheiro?(S/N): ");
                    scanf("%s",resposta);
                    if (strcmp(resposta,"S") == 0){
                        printf("\nIntroduza o nome do ficheiro para o qual deseja exportar: ");
                        scanf("%s",filename);
                        exportar_aeronaves_esquadra(filename,esquadra);
                    }
                    else 
                        printf("\n\n\n");
                break;
            case 5:
                if (total_voos == 0)
                    printf("O nosso sistema não possui qualquer voo registado.\n\n\n");
                else{
                    listaTodosVoos();
                    printf("Deseja exportar esta lista para um ficheiro?(S/N): ");
                    scanf("%s",resposta);
                    if (strcmp(resposta,"S") == 0){
                        printf("\nIntroduza o nome do ficheiro para o qual deseja exportar: ");
                        scanf("%s",filename);
                        exportar_todos_voos(filename);
                    }
                    else 
                        printf("\n\n\n");
                }
                break;
            case 6:
                printf("Digite o número de cauda da aeronave: ");
                scanf("%d", &nCauda);
                listaVoosCauda(nCauda);
                printf("Deseja exportar esta lista para um ficheiro?(S/N): ");
                    scanf("%s",resposta);
                    if (strcmp(resposta,"S") == 0){
                        printf("\nIntroduza o nome do ficheiro para o qual deseja exportar: ");
                        scanf("%s",filename);
                        exportar_listaVoosCauda(filename,nCauda);
                    }
                    else 
                        printf("\n\n\n");
                break;
            case 7:
                printf("Digite entre quais datas pretende procurar: ");
                scanf("%s %s",data_menor,data_maior);
                printf("\n\n\n");
                listaVoosData(data_menor,data_maior);
                printf("Deseja exportar esta lista para um ficheiro?(S/N): ");
                    scanf("%s",resposta);
                    if (strcmp(resposta,"S") == 0){
                        printf("\nIntroduza o nome do ficheiro para o qual deseja exportar: ");
                        scanf("%s",filename);
                        exportar_listaVoosData(data_menor,data_maior,filename);
                    }
                    else 
                        printf("\n\n\n");
                break;
            case 8:
                maioresHoras();
                maisHoras();
                break;
            case 0:
                return 0;
        }
    }
    return 0;
}