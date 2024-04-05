# Heap

## Descrição

Uma heap é um tipo especial de árvore binária completa ou quase completa que segue a regra de que o valor dos seus nós devem ser maiores/iguais ou menores/iguais ao valor do seu nó pai dependo da sua implementação ser máxima ou mínima.

No algoritimo de Dijkstra, se é utilizado uma fila de prioridade com ```heap mínima``, de forma com que a raiz da árvore sempre seja o menor valor. Como no mesmo utilizamos tanto a extração do menor valor e o relachamento das arestas, que podem ser realizados em tempos constante e logarítimico, respectivamente, pela estrutura de dados, não se pode negar que a estrutura caí como uma luva na implementação do algoritmo.

Exemplo: 

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int data[1000];
} Heap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap *heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;

    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

void init(Heap** heap) {
    Heap* min_heap = (Heap*)malloc(sizeof(Heap));
    min_heap->size = 0;
    *heap = min_heap;
}

void insert(Heap *heap, int newNum) {
    int i = heap->size;
    heap->data[i] = newNum;
    heap->size++;

    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void delete(Heap *heap) {
    if (heap->size == 0) {
        printf("Fila vazia\n");
        return;
    }
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
}

int getMin(Heap *heap) {
    if (heap->size == 0) {
        printf("Fila vazia\n");
        return -1;
    }
    return heap->data[0];
}