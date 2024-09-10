#include "estatisticas.h"

/*
FUNÇOES DE ESTATISTICAS
*/

int compararEsquadra(const void *a, const void *b) {
/*qsort ordena uma lista, 
se lhe dermos a lista, o numero de elementos da mesma, o tamanho da struct e uma funçao de comparação
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
    for(int i = 0; i < total_aeronaves; i++) {
        porOrdenar[i] = aeronaves[i];
    }
    qsort(porOrdenar, total_aeronaves, sizeof(aeronave), compararHoras);
}

void maioresHoras (){
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