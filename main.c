#include <stdio.h>
#include <stdlib.h>
#include <time.h> //clock(), CLOCKS_PER_SEC e clock_t

#define TAM 10000 //constante para tamanho do vetor
#define TESTES 5

void resetVetor(int *vet1, int *vet2);
void bubbleSort (int v[TAM]);
void quick_sort(int *a, int left, int right);
void mergesort(int *v, int n);
void sort(int *v, int *c, int i, int f);
void merge(int *v, int *c, int i, int m, int f);

int main(){
	clock_t t; //vari�vel para armazenar tempo
 	int vetor[TAM]; //vetor com N posi��es
 	int vetAux[TAM];
 	double vetTimes[3][TESTES];
 	int a;



  //gera��o aleat�ria dos valores do vetor
 	for(a = 0; a < TAM; a++){
		vetor[a] = rand() % 100;
		vetAux[a] = vetor[a];
 	}

 
  // armazenamento dos tempos de execu�ao
  // de cada ordena�ao dos vetors
  
  // bubbleSort
	for( a = 0; a < TESTES; a++){
		t = clock();
		
 		bubbleSort(vetor);
 		
 		vetTimes[0][a] = ((double)(clock() - t)/((CLOCKS_PER_SEC/1000)));//convers�o para double e armazenamento
 		
 		resetVetor(vetor, vetAux);//resetando vetor ao estado original
	}
	
  //quickSort
  
  	for( a = 0; a < TESTES; a++){
		t = clock();

		quick_sort(vetor, 0, TAM - 1);

 		vetTimes[1][a] = ((double)(clock() - t)/((CLOCKS_PER_SEC/1000)));//convers�o para double e armazenamento

 		resetVetor(vetor, vetAux);//resetando vetor ao estado original
	}
  
  //mergeSort
 	
	for( a = 0; a < TESTES; a++){
		t = clock();

 		mergesort(vetor, TAM);

 		vetTimes[2][a] = ((double)(clock() - t)/((CLOCKS_PER_SEC/1000)));//convers�o para double e armazenamento

 		resetVetor(vetor, vetAux);//resetando vetor ao estado original
	}
	
 		
  //imprime os tempos na tela
	system("color f4");
	printf("|----------------------------------------|\n");
 	printf("|  Tempos de execucoes em millisegundos  |\n");
 	printf("|----------------------------------------|\n");
 	printf("| Bubble Sort | Quick Sort | Merge Sort  |\n");
 	printf("|----------------------------------------|\n");
	for(a = 0; a < TESTES; a++ ){
		printf("|  %f  |  %f  |  %f  | \n", vetTimes[0][a], vetTimes[1][a], vetTimes[2][a]);
	}
	printf("|----------------------------------------|");
}



void resetVetor(int vet1[TAM], int vet2[TAM]){
		int a;
		for(a = 0; a < TAM; a++){
			vet1[a] = vet2[a];
		}
}



void bubbleSort (int v[TAM]) {
    int a, b, aux;
    for (a=TAM-1; a>=1; a--) {
        for (b=0; b<a; b++) {
            if (v[b]>v[b+1]) {
                aux = v[b];
                v[b] = v[b+1];
                v[b+1] = aux;
            }
        }
    }
}



void quick_sort(int *a, int left, int right) {
    int i, j, x, y;

    i = left;
    j = right;
    x = a[(left + right) / 2];

    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}

void mergesort(int *v, int n) {
  int *c = malloc(sizeof(int) * n);
  sort(v, c, 0, n - 1);
  free(c);
}


void sort(int *v, int *c, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(v, c, i, m);
  sort(v, c, m + 1, f);


  if (v[m] <= v[m + 1]) return;

  merge(v, c, i, m, f);
}



void merge(int *v, int *c, int i, int m, int f) {
  int z,
      iv = i, ic = m + 1;

  for (z = i; z <= f; z++) c[z] = v[z];

  z = i;

  while (iv <= m && ic <= f) {
    

    if (c[iv] <= c[ic]) v[z++] = c[iv++];
    else v[z++] = c[ic++];
  }

  while (iv <= m) v[z++] = c[iv++];

  while (ic <= f) v[z++] = c[ic++];
}
